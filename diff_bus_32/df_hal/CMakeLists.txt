add_subdirectory(tx)
add_subdirectory(rx)

file(GLOB DF_HAL_SOURCES "*.c")
add_library(df_hal STATIC ${DF_HAL_SOURCES})

target_include_directories(df_hal PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(df_hal INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/tx)
target_include_directories(df_hal INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/rx)

target_link_libraries(df_hal PUBLIC pico_stdlib tx rx)