
# componet standalone mode
if(NOT CONFIG_IOT_SOLUTION_EMBED)
    set(COMPONENT_ADD_INCLUDEDIRS "include")  
else()
    if(CONFIG_IOT_BIUFI_ENABLE)
        set(COMPONENT_ADD_INCLUDEDIRS "include")
        set(COMPONENT_PRIV_INCLUDEDIRS "include_bootloader")   
    else()
        set(COMPONENT_SRCS "")
        set(COMPONENT_ADD_INCLUDEDIRS "")
        message(STATUS "Building empty blufi component due to configuration")
    endif()
endif()

# requirements can't depend on config
set(COMPONENT_REQUIRES bt mbedtls)

register_component()

target_link_libraries(${COMPONENT_TARGET} INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/libblufi.a")