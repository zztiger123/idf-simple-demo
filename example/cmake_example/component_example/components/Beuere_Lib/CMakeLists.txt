
idf_component_register(INCLUDE_DIRS "." "include")

add_library(beurerMUSalgorithm STATIC IMPORTED)
set_property(TARGET beurerMUSalgorithm PROPERTY IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/lib/libbeurerMUSalgorithm.a)
target_link_libraries(${COMPONENT_LIB} INTERFACE beurerMUSalgorithm)
set_property(TARGET beurerMUSalgorithm APPEND PROPERTY INTERFACE_LINK_LIBRARIES ${COMPONENT_LIB})

