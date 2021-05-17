idf_component_register(SRCS "mqtt_test.c" "station.c"
                    INCLUDE_DIRS "."
                    REQUIRES nvs_flash mqtt)