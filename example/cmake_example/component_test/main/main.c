
#include <stdio.h>
#include <stdlib.h>
#include "test.h"

extern void user_get(void);
extern void user_set(uint32_t data);


void app_main()
{
    uint32_t test_data = 3;

    user_set(test_data);
    user_get();
}  