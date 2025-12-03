file(GLOB RX_SOURCES "*.c")
add_library(rx STATIC ${DF_HAL_SOURCES})

target_include_directories(rx PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(rx PUBLIC pico_stdlib hardware_pio hardware_clocks)