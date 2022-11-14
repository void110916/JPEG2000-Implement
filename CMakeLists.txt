cmake_minimum_required(VERSION 3.0.0)

project(JPEG2000 LANGUAGES CXX)
# ==== add compiler setting flag ================================== #
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
find_package(Threads REQUIRED)
# ================================================================= #
# ===== add custom executables/libraries ============================================ #
include_directories(src/Bitmap)
add_subdirectory(test)
add_subdirectory(src/JPEG2000)


# ================================================================= #
