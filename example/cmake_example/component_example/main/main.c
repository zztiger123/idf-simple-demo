
#include <stdio.h>
#include <stdlib.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "driver/adc.h"
#include "esp_adc_cal.h"
#include "freertos/queue.h"
#include "test.h"

#include "beurer_algorithm.h"

weighing_scale_config_t test_man = {0};

void app_main()
{
    unsigned int result = 0;

    result = beurer_algorithm_Mus(test_man.age, test_man.height,test_man.ac_l, test_man.weight, test_man.imp, test_man.sex);
    printf("result = %d\r\n", result);
    printf("too fat, cry :(\r\n");
}  