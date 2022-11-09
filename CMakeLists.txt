cmake_minimum_required(VERSION 3.0.0)

project(JPEG2000 LANGUAGES CXX)
# ==== add compiler setting flag ================================== #
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
find_package(Threads REQUIRED)
# ================================================================= #
# ===== add executable ============================================ #
set(PROJECT_SOURCES
        main.cpp
)

add_executable(${PROJECT_NAME}
    ${PROJECT_SOURCES}
)
# ================================================================= #
# ===== add custom libraries ============================================ #
add_subdirectory(JPEG2000)
target_link_libraries(${PROJECT_NAME} PRIVATE JPEG2000lib)
# ================================================================= #
# ===== add install =====　The following script must only be executed at install time ======= #
# Omitting RUNTIME DESTINATION will install a non-bundle target to CMAKE_INSTALL_BINDIR,
# which coincides with the default value of QT_DEPLOY_BIN_DIR used above, './bin'.
# Installing macOS bundles always requires an explicit BUNDLE DESTINATION option.
set(deploy_script "${CMAKE_CURRENT_BINARY_DIR}/deploy_${PROJECT_NAME}.cmake")
install(TARGETS ${PROJECT_NAME} 
        BUNDLE  DESTINATION .    
)
# ================================================================= #