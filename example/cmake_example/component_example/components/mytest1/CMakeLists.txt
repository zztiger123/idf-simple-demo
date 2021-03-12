idf_component_register(SRCS "test1.c"
                       INCLUDE_DIRS "." "include"
                       REQUIRES esp_adc_cal nvs_flash mytest2)
