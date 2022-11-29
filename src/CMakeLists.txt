cmake_minimum_required(VERSION 3.0.0)

project(JPEG2000 LANGUAGES CXX)
# ==== add compiler setting flag ================================== #
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/Debug)
# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/Release)
# set(CMAKE_BUILD_TYPE "Release") # Debug, Release, RelWithDebInfo, MinSizeRel
find_package(Threads REQUIRED)
# ================================================================= #
# ==== add Ctest ================================== #

include(CTest)
enable_testing()

# ================================================== #
# ===== add custom executables/libraries ============================================ #
include_directories(lib/Bitmap)
add_subdirectory(lib/JPEG2000)
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/test)
# ================================================================= #
