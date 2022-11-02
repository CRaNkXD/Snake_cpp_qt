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

# Set path to our custom CMAKE scripts
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake")

# Include Qt deployment helper function
include(windeployqt)

windeployqt(${PROJECT_NAME})
