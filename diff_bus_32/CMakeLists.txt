add_subdirectory(df_hal)

file(GLOB DF_BUS_SOURCES "*.c")
add_library(diff_bus_32 STATIC ${DF_BUS_SOURCES})

target_include_directories(diff_bus_32 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(diff_bus_32 INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/df_hal)

target_link_libraries(diff_bus_32 PUBLIC  pico_stdlib hardware_pio hardware_clocks hardware_dma df_hal hardware_structs)