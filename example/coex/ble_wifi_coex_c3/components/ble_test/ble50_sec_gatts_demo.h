#ifndef _GATTC_DEMO_H
#define _GATTC_DEMO_H

#include <stdio.h>
#include "esp_log.h"

#ifdef __cplusplus
extern "C"
{
#endif


#include <stdlib.h>
#include <string.h>


/* Attributes State Machine */
enum
{
    IDX_SVC,
    IDX_CHAR_A,
    IDX_CHAR_VAL_A,
    IDX_CHAR_CFG_A,

    IDX_CHAR_B,
    IDX_CHAR_VAL_B,

    IDX_CHAR_C,
    IDX_CHAR_VAL_C,

    HRS_IDX_NB,
};


void ble_start(void);

#ifdef __cplusplus
}
#endif

#endif /* GATTC_DEMO_H */
