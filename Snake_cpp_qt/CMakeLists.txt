cmake_minimum_required(VERSION 3.18.2)
project(Snake_cpp_qt VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# set(CPACK_PROJECT_NAME ${PROJECT_NAME})
# set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
# include(CPack)

# include(CTest)
# enable_testing()

find_package(Qt5 COMPONENTS Core Gui Widgets REQUIRED)

# add_custom_command(TARGET ${PROJECT_NAME}  POST_BUILD
# COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt5::Core> $<TARGET_FILE_DIR:MyQtProj>
# COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt5::Gui> $<TARGET_FILE_DIR:MyQtProj>
# COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt5::Widgets> $<TARGET_FILE_DIR:MyQtProj>
# )

add_executable(${PROJECT_NAME} 
    main.cpp
    gamewindow.cpp
    gamewindow.ui
    resources/resources.qrc)

add_subdirectory(model)
add_subdirectory(helper)
add_subdirectory(gui)
add_subdirectory(constants)

target_link_libraries(${PROJECT_NAME} Qt5::Widgets model helper gui constants)

# target_include_directories(${PROJECT_NAME} PUBLIC
#                           "${PROJECT_BINARY_DIR}"
#                           )

# Set path to our custom CMAKE scripts
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake")

# Include Qt deployment helper function
include(windeployqt)

windeployqt(${PROJECT_NAME})