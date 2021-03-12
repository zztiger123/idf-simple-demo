// Copyright 2018-2019 Espressif Systems (Shanghai) PTE LTD
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef _BEURER_ALGORITHM_H
#define _BEURER_ALGORITHM_H

#include "stdint.h"


#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    unsigned char age;
    unsigned char height;
    unsigned char ac_l;
    unsigned int  weight;
    unsigned int  imp;
    unsigned char sex;
} weighing_scale_config_t;

unsigned int beurer_algorithm_Mus(unsigned char age, unsigned char height,unsigned char AC_L, \
                                  unsigned int weight, unsigned int IMP, unsigned char sex);

//sex: 0-男；1-女

#ifdef __cplusplus
}
#endif

#endif /* _MY_SDK_H */
