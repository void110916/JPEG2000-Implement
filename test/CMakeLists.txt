function(add_test_executable fileName)
    # ===== add executable ============================================ #
    set(PROJECT_SOURCES
    ${fileName}.cpp ${ARGN}
    )

    add_executable(${fileName}
    ${PROJECT_SOURCES}
    )
    target_link_libraries(${fileName} PRIVATE JPEG2000lib)
    message(STATUS "Add executable ${fileName}.cpp")
    if(NOT ARGN STREQUAL "")
        message(STATUS "    With file ${ARGN}")
    endif()
    # ================================================================= #
    # ===== add install =====　The following script must only be executed at install time ======= #
    # Omitting RUNTIME DESTINATION will install a non-bundle target to CMAKE_INSTALL_BINDIR,
    # which coincides with the default value of QT_DEPLOY_BIN_DIR used above, './bin'.
    # Installing macOS bundles always requires an explicit BUNDLE DESTINATION option.
    set(deploy_script "${CMAKE_CURRENT_BINARY_DIR}/deploy_${fileName}.cmake")
    install(TARGETS ${fileName} 
            BUNDLE  DESTINATION .    
    )
    # ================================================================= #
endfunction(add_test_executable)

add_test_executable(matrix)
add_test_executable(matrix3D)
add_test_executable(bitmap)
add_test_executable(preprocessing)
set(IMAGE_SOURCE dinor.bmp Test_card.bmp test_colorbars_1920x1080.bmp test_gradation_640x480.bmp)
foreach(IMAGE ${IMAGE_SOURCE})
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/img/${IMAGE}
    ${CMAKE_CURRENT_BINARY_DIR}/${IMAGE} COPYONLY)
endforeach(IMAGE IMAGESOURCE)


