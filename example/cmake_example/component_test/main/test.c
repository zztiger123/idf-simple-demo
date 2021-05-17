

#include "test.h"
#include "esp_log.h"
#include <stdio.h>

static uint32_t test_data = 0;

static const char *TAG = "test";

uint32_t get_test_data(void) 
{
    ESP_LOGI(TAG, "get data value : %d", test_data);
    return test_data;
}

void set_test_data(uint32_t data) 
{
    test_data = data;
    ESP_LOGI(TAG, "set data value : %d", test_data);
}

