# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file LICENSE.rst or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION ${CMAKE_VERSION}) # this file comes with cmake

# If CMAKE_DISABLE_SOURCE_CHANGES is set to true and the source directory is an
# existing directory in our source tree, calling file(MAKE_DIRECTORY) on it
# would cause a fatal error, even though it would be a no-op.
if(NOT EXISTS "D:/ABCV/SDK_s/pico-sdk/tools/pioasm")
  file(MAKE_DIRECTORY "D:/ABCV/SDK_s/pico-sdk/tools/pioasm")
endif()
file(MAKE_DIRECTORY
  "D:/ABCV/Hard_ware/Rasbery pi programs/Major_Project/diff_bus_tst/rp_2040/diff_bus_32/build/pioasm"
  "D:/ABCV/Hard_ware/Rasbery pi programs/Major_Project/diff_bus_tst/rp_2040/diff_bus_32/build/pioasm-install"
  "D:/ABCV/Hard_ware/Rasbery pi programs/Major_Project/diff_bus_tst/rp_2040/diff_bus_32/build/pico-sdk/src/rp2_common/pico_cyw43_driver/pioasm/tmp"
  "D:/ABCV/Hard_ware/Rasbery pi programs/Major_Project/diff_bus_tst/rp_2040/diff_bus_32/build/pico-sdk/src/rp2_common/pico_cyw43_driver/pioasm/src/pioasmBuild-stamp"
  "D:/ABCV/Hard_ware/Rasbery pi programs/Major_Project/diff_bus_tst/rp_2040/diff_bus_32/build/pico-sdk/src/rp2_common/pico_cyw43_driver/pioasm/src"
  "D:/ABCV/Hard_ware/Rasbery pi programs/Major_Project/diff_bus_tst/rp_2040/diff_bus_32/build/pico-sdk/src/rp2_common/pico_cyw43_driver/pioasm/src/pioasmBuild-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "D:/ABCV/Hard_ware/Rasbery pi programs/Major_Project/diff_bus_tst/rp_2040/diff_bus_32/build/pico-sdk/src/rp2_common/pico_cyw43_driver/pioasm/src/pioasmBuild-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "D:/ABCV/Hard_ware/Rasbery pi programs/Major_Project/diff_bus_tst/rp_2040/diff_bus_32/build/pico-sdk/src/rp2_common/pico_cyw43_driver/pioasm/src/pioasmBuild-stamp${cfgdir}") # cfgdir has leading slash
endif()
