
add_library(libJPEG2000 STATIC # Add file below when creating new file
    matrix.h
    matrix.cpp
    wavelet.h
    wavelet.cpp

)
target_include_directories(libJPEG2000 INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})