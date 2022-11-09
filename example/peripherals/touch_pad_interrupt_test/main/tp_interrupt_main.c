/*
 * SPDX-FileCopyrightText: 2021-2022 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: CC0-1.0
 */

#include <stdio.h>
#include <inttypes.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "esp_log.h"
#include "driver/touch_pad.h"
#include "soc/rtc_periph.h"
#include "soc/sens_periph.h"
#include "esp_sleep.h"
#include "driver/rtc_io.h"
#include "driver/gpio.h"
#include "soc/gpio_periph.h"
#include "hal/gpio_types.h"
#include "driver/gpio.h"

#include "rom/ets_sys.h"

#define GPIO_NUM_35 35
#define GPIO_NUM_34 34
#define GPIO_NUM_33 33

static const char *TAG = "Touch pad";

static QueueHandle_t que_touch = NULL;
typedef struct touch_msg
{
    touch_pad_intr_mask_t intr_mask;
    uint32_t pad_num;
    uint32_t pad_status;
    uint32_t pad_val;
} touch_event_t;

#define TOUCH_BUTTON_NUM 3
#define TOUCH_BUTTON_WATERPROOF_ENABLE 0
#define TOUCH_BUTTON_DENOISE_ENABLE 1
#define TOUCH_CHANGE_CONFIG 0

static const touch_pad_t button[TOUCH_BUTTON_NUM] = {

    TOUCH_PAD_NUM8,  // 'MENU' button.
    TOUCH_PAD_NUM10, // 'BACK' button.
    TOUCH_PAD_NUM12, // Guard ring for waterproof design.
    // If this pad be touched, other pads no response.
};

void led_init(void)

{

    gpio_config_t io_conf = {};
    // set as output mode
    io_conf.mode = GPIO_MODE_OUTPUT;
    // bit mask of the pins that you want to set,e.g.GPIO18/19
    io_conf.pin_bit_mask = ((1ULL << GPIO_NUM_33) | (1ULL << GPIO_NUM_34) | (1ULL << GPIO_NUM_35));
    io_conf.pull_down_en = 1;
    // disable pull-up mode
    io_conf.pull_up_en = 0;
    // disable pull-down mode

    // configure GPIO with the given settings
    gpio_config(&io_conf);

    //  gpio_init(GPIO_NUM_45);

    gpio_set_level(GPIO_NUM_33, 0);
    gpio_set_level(GPIO_NUM_34, 0);
    gpio_set_level(GPIO_NUM_35, 0);

    // zero-initialize the config structure.
}
/*
 * Touch threshold. The threshold determines the sensitivity of the touch.
 * This threshold is derived by testing changes in readings from different touch channels.
 * If (raw_data - benchmark) > benchmark * threshold, the pad be activated.
 * If (raw_data - benchmark) < benchmark * threshold, the pad be inactivated.
 */
static const float button_threshold[TOUCH_BUTTON_NUM] = {
    0.04, // 20%.
    0.04, // 20%.
    0.04, // 20%.

};

/*
  Handle an interrupt triggered when a pad is touched.
  Recognize what pad has been touched and save it in a table.
 */
static void touchsensor_interrupt_cb(void *arg)
{
    int task_awoken = pdFALSE;
    touch_event_t evt;

    evt.intr_mask = touch_pad_read_intr_status_mask();
    evt.pad_status = touch_pad_get_status();
    evt.pad_num = touch_pad_get_current_meas_channel();

    xQueueSendFromISR(que_touch, &evt, &task_awoken);
    if (task_awoken == pdTRUE)
    {
        portYIELD_FROM_ISR();
    }
}

static void tp_example_set_thresholds(void)
{
    uint32_t touch_value;
    for (int i = 0; i < TOUCH_BUTTON_NUM; i++)
    {
        // read benchmark value
        touch_pad_read_benchmark(button[i], &touch_value);
        // set interrupt threshold.
        touch_pad_set_thresh(button[i], touch_value * button_threshold[i]);
        ESP_LOGI(TAG, "touch pad [%d] base %" PRIu32 ", thresh %" PRIu32,
                 button[i], touch_value, (uint32_t)(touch_value * button_threshold[i]));
    }
}

static void touchsensor_filter_set(touch_filter_mode_t mode)
{
    /* Filter function */
    touch_filter_config_t filter_info = {
        .mode = mode,      // Test jitter and filter 1/4.
        .debounce_cnt = 1, // 1 time count.
        .noise_thr = 0,    // 50%
        .jitter_step = 4,  // use for jitter mode.
        .smh_lvl = TOUCH_PAD_SMOOTH_IIR_2,
    };
    touch_pad_filter_set_config(&filter_info);
    touch_pad_filter_enable();
    ESP_LOGI(TAG, "touch pad filter init");
}

static void tp_example_read_task(void *pvParameter)
{
    touch_event_t evt = {0};
    static uint8_t guard_mode_flag = 0;
    /* Wait touch sensor init done */
    vTaskDelay(50 / portTICK_PERIOD_MS);
    tp_example_set_thresholds();

    while (1)
    {
        int ret = xQueueReceive(que_touch, &evt, (TickType_t)portMAX_DELAY);
        if (ret != pdTRUE)
        {
            continue;
        }
        if (evt.intr_mask & TOUCH_PAD_INTR_MASK_ACTIVE)
        {

            if (evt.pad_num == button[2])
            {

                ESP_LOGW(TAG, "TouchSensor [%" PRIu32 "] be activated, enter guard mode", evt.pad_num);
                /* if guard pad be touched, other pads no response. */

                ESP_LOGI(TAG, "TouchSensor [%" PRIu32 "] be activated, status mask 0x%" PRIu32 "", evt.pad_num, evt.pad_status);

                printf("pad 12 anxia anxia anxia anxia\n");
                gpio_set_level(GPIO_NUM_35, 1);
            }

            if (evt.pad_num == button[1])
            {

                ESP_LOGW(TAG, "TouchSensor [%" PRIu32 "] be activated, enter guard mode", evt.pad_num);
                /* if guard pad be touched, other pads no response. */

                ESP_LOGI(TAG, "TouchSensor [%" PRIu32 "] be activated, status mask 0x%" PRIu32 "", evt.pad_num, evt.pad_status);

                printf("pad 10 anxia anxia anxia anxia \n");
                gpio_set_level(GPIO_NUM_34, 1);
            }

            if (evt.pad_num == button[0])
            {

                ESP_LOGW(TAG, "TouchSensor [%" PRIu32 "] be activated, enter guard mode", evt.pad_num);
                /* if guard pad be touched, other pads no response. */

                ESP_LOGI(TAG, "TouchSensor [%" PRIu32 "] be activated, status mask 0x%" PRIu32 "", evt.pad_num, evt.pad_status);

                printf("pad 88888888888888888888  anxia anxia anxia anxia\n");
                gpio_set_level(GPIO_NUM_33, 1);
            }
        }

        if (evt.intr_mask & TOUCH_PAD_INTR_MASK_INACTIVE)
        {
            /* if guard pad be touched, other pads no response. */

            if (evt.pad_num == button[2])
            {

                ESP_LOGI(TAG, "TouchSensor [%" PRIu32 "] be inactivated, status mask 0x%" PRIu32, evt.pad_num, evt.pad_status);
                printf("pad 12 pad 12 pad 12 songshou  songhsou songshou  songhsou songshou  songhson");

                gpio_set_level(GPIO_NUM_35, 0);
            }

            if (evt.pad_num == button[1])
            {

                ESP_LOGI(TAG, "TouchSensor [%" PRIu32 "] be inactivated, status mask 0x%" PRIu32, evt.pad_num, evt.pad_status);
                printf("pad 10 pad 10 pad 10 songshou  songshou songshou songshou  songshou songshou \n");
                gpio_set_level(GPIO_NUM_34, 0);
            }

            if (evt.pad_num == button[0])
            {

                ESP_LOGI(TAG, "TouchSensor [%" PRIu32 "] be inactivated, status mask 0x%" PRIu32, evt.pad_num, evt.pad_status);
                printf(" pad 88888888888888 songshou  songshou songshou songshou  songshou songshou\n");
                gpio_set_level(GPIO_NUM_33, 0);
            }
        }

        if (evt.intr_mask & TOUCH_PAD_INTR_MASK_SCAN_DONE)
        {
            ESP_LOGI(TAG, "The touch sensor group measurement is done [%" PRIu32 "].", evt.pad_num);
        }
        if (evt.intr_mask & TOUCH_PAD_INTR_MASK_TIMEOUT)
        {
            /* Add your exception handling in here. */
            ESP_LOGI(TAG, "Touch sensor channel %" PRIu32 " measure timeout. Skip this exception channel!!", evt.pad_num);
            touch_pad_timeout_resume(); // Point on the next channel to measure.
        }
    }
}

void app_main(void)
{

    led_init();

    if (que_touch == NULL)
    {
        que_touch = xQueueCreate(TOUCH_BUTTON_NUM, sizeof(touch_event_t));
    }
    // Initialize touch pad peripheral, it will start a timer to run a filter
    ESP_LOGI(TAG, "Initializing touch pad");
    /* Initialize touch pad peripheral. */
    touch_pad_init();
    for (int i = 0; i < TOUCH_BUTTON_NUM; i++)
    {
        touch_pad_config(button[i]);
    }

#if TOUCH_CHANGE_CONFIG
    /* If you want change the touch sensor default setting, please write here(after initialize). There are examples: */
    touch_pad_set_measurement_interval(TOUCH_PAD_SLEEP_CYCLE_DEFAULT);
    touch_pad_set_charge_discharge_times(TOUCH_PAD_MEASURE_CYCLE_DEFAULT);
    touch_pad_set_voltage(TOUCH_PAD_HIGH_VOLTAGE_THRESHOLD, TOUCH_PAD_LOW_VOLTAGE_THRESHOLD, TOUCH_PAD_ATTEN_VOLTAGE_THRESHOLD);
    touch_pad_set_idle_channel_connect(TOUCH_PAD_IDLE_CH_CONNECT_DEFAULT);
    for (int i = 0; i < TOUCH_BUTTON_NUM; i++)
    {
        touch_pad_set_cnt_mode(button[i], TOUCH_PAD_SLOPE_DEFAULT, TOUCH_PAD_TIE_OPT_DEFAULT);
    }
#endif

#if TOUCH_BUTTON_DENOISE_ENABLE
    /* Denoise setting at TouchSensor 0. */
    touch_pad_denoise_t denoise = {
        /* The bits to be cancelled are determined according to the noise level. */
        .grade = TOUCH_PAD_DENOISE_BIT4,
        /* By adjusting the parameters, the reading of T0 should be approximated to the reading of the measured channel. */
        .cap_level = TOUCH_PAD_DENOISE_CAP_L4,
    };
    touch_pad_denoise_set_config(&denoise);
    touch_pad_denoise_enable();
    ESP_LOGI(TAG, "Denoise function init");
#endif

#if TOUCH_BUTTON_WATERPROOF_ENABLE
    /* Waterproof function */
    touch_pad_waterproof_t waterproof = {
        .guard_ring_pad = button[2], // If no ring pad, set 0;
        /* It depends on the number of the parasitic capacitance of the shield pad.
           Based on the touch readings of T14 and T0, estimate the size of the parasitic capacitance on T14
           and set the parameters of the appropriate hardware. */
        .shield_driver = TOUCH_PAD_SHIELD_DRV_L2,
    };
    // touch_pad_waterproof_set_config(&waterproof);
    //  touch_pad_waterproof_enable();
    ESP_LOGI(TAG, "touch pad waterproof init");
#endif

    /* Filter setting */
    touchsensor_filter_set(TOUCH_PAD_FILTER_IIR_16);
    touch_pad_timeout_set(true, SOC_TOUCH_PAD_THRESHOLD_MAX);
    /* Register touch interrupt ISR, enable intr type. */
    touch_pad_isr_register(touchsensor_interrupt_cb, NULL, TOUCH_PAD_INTR_MASK_ALL);
    /* If you have other touch algorithm, you can get the measured value after the `TOUCH_PAD_INTR_MASK_SCAN_DONE` interrupt is generated. */
    touch_pad_intr_enable(TOUCH_PAD_INTR_MASK_ACTIVE | TOUCH_PAD_INTR_MASK_INACTIVE | TOUCH_PAD_INTR_MASK_TIMEOUT);

    /* Enable touch sensor clock. Work mode is "timer trigger". */
    touch_pad_set_fsm_mode(TOUCH_FSM_MODE_TIMER);
    touch_pad_fsm_start();

    // Start a task to show what pads have been touched
    xTaskCreate(&tp_example_read_task, "touch_pad_read_task", 4096, NULL, 5, NULL);
}
