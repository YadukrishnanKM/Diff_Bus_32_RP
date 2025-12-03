cmake_minimum_required(VERSION 3.13)


# -------------------------------------------------------------------
# Import Pico SDK (local copy in same folder)
# -------------------------------------------------------------------

# Include the Pico SDK import file
include("$ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake")
include("$ENV{PICO_SDK_PATH}/tools/CMakeLists.txt")

# -------------------------------------------------------------------
# Project setup
# -------------------------------------------------------------------

project(diff_bus C CXX ASM)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

set(DF_BUS_ROOT ${CMAKE_CURRENT_SOURCE_DIR})


# Initialize the SDK
pico_sdk_init()

# -------------------------------------------------------------------
# Add your source files
# -------------------------------------------------------------------
add_executable(${PROJECT_NAME} main.cpp)

# -------------------------------------------------------------------
# Link with required SDK libraries
# -------------------------------------------------------------------

#pico_generate_pio_header(${PROJECT_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/lib/sxz_prog.pio)
add_subdirectory(diff_bus_32)

target_link_libraries(${PROJECT_NAME} pico_stdlib hardware_pio diff_bus_32 )
target_include_directories(${PROJECT_NAME} INTERFACE ${DF_BUS_ROOT}/diff_bus_32)

# -------------------------------------------------------------------
# Configure stdio
# -------------------------------------------------------------------
pico_enable_stdio_usb(${PROJECT_NAME} 1)
pico_enable_stdio_uart(${PROJECT_NAME} 0)

# -------------------------------------------------------------------
# Create .uf2, .bin, .hex after build
# -------------------------------------------------------------------
pico_add_extra_outputs(${PROJECT_NAME})
