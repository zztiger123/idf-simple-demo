

#include "test.h"
#include "esp_log.h"
#include <stdio.h>

static uint32_t test_data = 0;

static uint32_t *TAG = "test_set";


void user_set(uint32_t data) 
{
    set_test_data(data);
}

