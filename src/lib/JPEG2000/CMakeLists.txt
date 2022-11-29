
add_library(JPEG2000lib STATIC # Add file below when creating new file
    matrix.h
    preprocessing.h
    preprocessing.tpp
    wavelet.cpp
    wavelet.h
)
target_include_directories(JPEG2000lib INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})