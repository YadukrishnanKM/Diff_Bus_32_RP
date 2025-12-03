file(GLOB TX_SOURCES "*.c")
add_library(tx STATIC ${DF_HAL_SOURCES})

target_include_directories(tx PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(tx PUBLIC pico_stdlib hardware_pio hardware_clocks)