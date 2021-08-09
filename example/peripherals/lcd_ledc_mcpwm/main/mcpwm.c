
/* MCPWM BLDC control Test code

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/

/*
 * The following examples uses mcpwm module to control bldc motor vary its speed continiously
 * The BLDC motor used for testing this code had sequence of 6-->4-->5-->1-->3-->2-->6-->4--> and so on
 * IR2136 3-ph bridge driver is used for testing this example code
 * User needs to make changes according to the motor and gate driver ic used
 */

#include <stdio.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "esp_attr.h"
#include "soc/rtc.h"
#include "driver/mcpwm.h"
#include "soc/mcpwm_periph.h"

#define INITIAL_DUTY 10.0   //initial duty cycle is 10.0%
#define MCPWM_GPIO_INIT 0   //select which function to use to initialize gpio signals

#define GPIO_HALL_TEST_SIGNAL 0     //Make this 1 to enable generation of hall sensors test signal on GPIO13, 12, 14
#define CHANGE_DUTY_CONTINUOUSLY 1  //Make this 1 to change duty continuously

#define CAP_SIG_NUM 1   //three capture signals from HALL-A, HALL-B, HALL-C
#define CAP0_INT_EN BIT(27)  //Capture 0 interrupt bit


#define GPIO_PWM0A_OUT 26   //Set GPIO 15 as PWM0A
#define GPIO_PWM0B_OUT 27   //Set GPIO 02 as PWM0B
#define GPIO_CAP0_IN   00   //Set GPIO 25 as  CAP0

typedef struct {
    uint32_t capture_signal;
    mcpwm_capture_signal_t sel_cap_signal;
} capture;

static uint32_t hall_sensor_value = 0;
static uint32_t hall_sensor_previous = 0;

xQueueHandle cap_queue;

static mcpwm_dev_t *MCPWM[2] = {&MCPWM0, &MCPWM1};

static void mcpwm_example_gpio_initialize(void)
{
    printf("initializing mcpwm bldc control gpio...\n");
#if MCPWM_GPIO_INIT
    mcpwm_gpio_init(MCPWM_UNIT_0, MCPWM0A, GPIO_PWM0A_OUT);
    mcpwm_gpio_init(MCPWM_UNIT_0, MCPWM0B, GPIO_PWM0B_OUT);
    mcpwm_gpio_init(MCPWM_UNIT_0, MCPWM_CAP_0, GPIO_CAP0_IN);
#else
    mcpwm_pin_config_t pin_config = {
        .mcpwm0a_out_num = GPIO_PWM0A_OUT,
        .mcpwm0b_out_num = GPIO_PWM0B_OUT,
        .mcpwm_cap0_in_num   = GPIO_CAP0_IN,
        .mcpwm_sync0_in_num  = -1,  //Not used
        .mcpwm_fault0_in_num = -1,  //Not used
    };
    mcpwm_set_pin(MCPWM_UNIT_0, &pin_config);
#endif
    gpio_pulldown_en(GPIO_CAP0_IN);    //Enable pull down on CAP0   signal
}


/**
 * @brief When interrupt occurs, we receive the counter value and display the time between two rising edge
 */
static void disp_captured_signal(void *arg)
{
    uint32_t *current_cap_value = (uint32_t *)malloc(sizeof(CAP_SIG_NUM));
    uint32_t *previous_cap_value = (uint32_t *)malloc(sizeof(CAP_SIG_NUM));
    capture evt;
    while (1) {
        xQueueReceive(cap_queue, &evt, portMAX_DELAY);
        if (evt.sel_cap_signal == MCPWM_SELECT_CAP0) {
            current_cap_value[0] = evt.capture_signal - previous_cap_value[0];
            previous_cap_value[0] = evt.capture_signal;
            current_cap_value[0] = (current_cap_value[0] / 10000) * (10000000000 / rtc_clk_apb_freq_get());
            //printf("CAP0 : %d us\n", current_cap_value[0]);
        }
    }
}

/**
 * @brief this is ISR handler function, here we check for interrupt that triggers rising edge on CAP0 signal and according take action
 */
static void IRAM_ATTR isr_handler(void *arg)
{
    uint32_t mcpwm_intr_status;
    capture evt;
    mcpwm_intr_status = MCPWM[MCPWM_UNIT_0]->int_st.val; //Read interrupt status
    if (mcpwm_intr_status & CAP0_INT_EN) { //Check for interrupt on rising edge on CAP0 signal
        evt.capture_signal = mcpwm_capture_signal_get_value(MCPWM_UNIT_0, MCPWM_SELECT_CAP0); //get capture signal counter value
        evt.sel_cap_signal = MCPWM_SELECT_CAP0;
        xQueueSendFromISR(cap_queue, &evt, NULL);
    }
    MCPWM[MCPWM_UNIT_0]->int_clr.val = mcpwm_intr_status;
}

#if CHANGE_DUTY_CONTINUOUSLY
static void change_duty(void *arg)
{
    int j;
    while (1) {
        for (j = 0; j < 18; j++) {
            //printf("duty cycle: %d\n", (0 +j*50));
            mcpwm_set_duty(MCPWM_UNIT_0, MCPWM_TIMER_0, MCPWM_OPR_A, (INITIAL_DUTY + j * 5.0));
            mcpwm_set_duty(MCPWM_UNIT_0, MCPWM_TIMER_0, MCPWM_OPR_B, (INITIAL_DUTY + j * 5.0));
            vTaskDelay(100 / portTICK_RATE_MS);
        }
    }
}
#endif

/**
 * @brief Configure whole MCPWM module for bldc motor control
 */
static void mcpwm_example_bldc_control(void *arg)
{
    //1. mcpwm gpio initialization
    mcpwm_example_gpio_initialize();

    //2. initial mcpwm configuration
    printf("Configuring Initial Parameters of mcpwm bldc control...\n");
    mcpwm_config_t pwm_config;
    pwm_config.frequency = 1000;    //frequency = 1000Hz
    pwm_config.cmpr_a = 50.0;    //duty cycle of PWMxA = 50.0%
    pwm_config.cmpr_b = 50.0;    //duty cycle of PWMxb = 50.0%
    pwm_config.counter_mode = MCPWM_UP_COUNTER;
    pwm_config.duty_mode = MCPWM_DUTY_MODE_1;
    mcpwm_init(MCPWM_UNIT_0, MCPWM_TIMER_0, &pwm_config);    //Configure PWM0A & PWM0B with above settings


    //3. Capture configuration
    //configure CAP0, CAP1 and CAP2 signal to start capture counter on rising edge
    //we generate a gpio_test_signal of 20ms on GPIO 12 and connect it to one of the capture signal, the disp_captured_function displays the time between rising edge
    //In general practice you can connect Capture  to external signal, measure time between rising edge or falling edge and take action accordingly
    mcpwm_capture_enable(MCPWM_UNIT_0, MCPWM_SELECT_CAP0, MCPWM_POS_EDGE, 0);  //capture signal on rising edge, pulse num = 0 i.e. 800,000,000 counts is equal to one second
    //enable interrupt, so each this a rising edge occurs interrupt is triggered
    MCPWM[MCPWM_UNIT_0]->int_ena.val = (CAP0_INT_EN);  //Enable interrupt on  CAP0, CAP1 and CAP2 signal
    mcpwm_isr_register(MCPWM_UNIT_0, isr_handler, NULL, ESP_INTR_FLAG_IRAM, NULL);  //Set ISR Handler
    //According to the hall sensor input value take action on PWM0A/0B/1A/1B/2A/2B
    while (1) {
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}

void mcpwm_test(void)
{
    cap_queue = xQueueCreate(1, sizeof(capture)); //comment if you don't want to use capture module
    xTaskCreate(disp_captured_signal, "mcpwm_config", 4096, NULL, 2, NULL);  //comment if you don't want to use capture module
    xTaskCreate(mcpwm_example_bldc_control, "mcpwm_example_bldc_control", 4096, NULL, 2, NULL);

    printf("Testing MCPWM BLDC Control...\n");
#if CHANGE_DUTY_CONTINUOUSLY
    xTaskCreate(change_duty, "change_duty", 2048, NULL, 2, NULL);
#endif
}

