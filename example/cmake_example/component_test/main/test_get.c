

#include "test.h"
#include "esp_log.h"
#include <stdio.h>

static uint32_t test_data = 0;

static uint32_t *TAG = "test_get";

uint32_t user_get(void) 
{
    return get_test_data();
}
