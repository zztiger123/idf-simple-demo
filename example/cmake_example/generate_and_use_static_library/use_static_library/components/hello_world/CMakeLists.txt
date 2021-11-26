idf_component_register(INCLUDE_DIRS "./include")

target_link_libraries(${COMPONENT_LIB} INTERFACE "${CMAKE_CURRENT_LIST_DIR}/libhello_world.a")