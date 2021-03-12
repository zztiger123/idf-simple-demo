// Copyright 2020 Espressif Systems (Shanghai) PTE LTD
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at

//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef _IOT_BLUFI_H_
#define _IOT_BLUFI_H_

#include "string.h"
#include "stdio.h"
#include "esp_log.h"
 
#ifdef __cplusplus
extern "C"
{
#endif

/**
 * @brief   blufi set name.
 *
 * @param   name  Pointer to the blufi name.
 * 
 * @return
 *     - ESP_OK Success
 *     - ESP_FAIL Fail
 */
esp_err_t blufi_set_name(char *name);

/**
 * @brief   blufi netconfig init.
 *
 * @return
 *     - ESP_OK Success
 *     - ESP_FAIL Fail
 */
esp_err_t blufi_netconfig_init(void);

/**
 * @brief   blufi netconfig deinit.
 *
 * @return
 *     - ESP_OK Success
 *     - ESP_FAIL Fail
 */
esp_err_t blufi_netconfig_deinit(void);

/**
 * @brief   blufi sand scan ap info.
 *
 * @return
 *     - ESP_OK Success
 *     - ESP_FAIL Fail
 */
esp_err_t blufi_send_scan_ap_info(void);

/**
 * @brief   blufi sand ap connect info.
 *
 * @return
 *     - ESP_OK Success
 *     - ESP_FAIL Fail
 */
esp_err_t blufi_send_ap_connect_info(void);

/**
 * @brief   blufi sand ap connect status.
 *
 * @return
 *     - ESP_OK Success
 *     - ESP_FAIL Fail
 */
esp_err_t blufi_send_ap_connect_stratus(void);

/**
 * @brief   blufi set sta status.
 *
 * @param   status Data of sta connect ap status.
 * 
 * @return
 *     - ESP_OK Success
 *     - ESP_FAIL Fail
 */
esp_err_t blufi_set_sta_status(bool status);

/**
 * @brief   blufi set sta bassid.
 *
 * @param   bssid Data of sta connect ap bssid.
 * 
 * @return
 *     - ESP_OK Success
 *     - ESP_FAIL Fail
 */
esp_err_t blufi_set_sta_bssid(uint8_t bssid[6]);

/**
 * @brief   blufi set sta ssid.
 *
 * @param   bssid Data of sta connect ap ssid.
 * 
 * @return
 *     - ESP_OK Success
 *     - ESP_FAIL Fail
 */
esp_err_t blufi_set_sta_ssid(char *ssid, int ssid_len);

/**
 * @brief   blufi clr sta info.
 * 
 * @return
 *     - ESP_OK Success
 *     - ESP_FAIL Fail
 */
esp_err_t blufi_clr_sta_info(void);

#ifdef __cplusplus
}
#endif
#endif