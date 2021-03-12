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

#ifndef _BLUFI_SECURITY_H_
#define _BLUFI_SECURITY_H_

#include "string.h"
#include "stdio.h"


#ifdef __cplusplus
extern "C"
{
#endif

void blufi_dh_negotiate_data_handler(uint8_t *data, int len, uint8_t **output_data, int *output_len, bool *need_free);

int blufi_aes_encrypt(uint8_t iv8, uint8_t *crypt_data, int crypt_len);

int blufi_aes_decrypt(uint8_t iv8, uint8_t *crypt_data, int crypt_len);

uint16_t blufi_crc_checksum(uint8_t iv8, uint8_t *data, int len);

int blufi_security_init(void);

int blufi_security_deinit(void);

#ifdef __cplusplus
}
#endif
#endif