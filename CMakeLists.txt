cmake_minimum_required(VERSION 3.24.0)
project(Snake_cpp_qt VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# set(CPACK_PROJECT_NAME ${PROJECT_NAME})
# set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
# include(CPack)

# Let's nicely support folders in IDE's
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

include(CTest)
enable_testing()

include(FetchContent)

find_package(Qt6 COMPONENTS Core Gui Widgets REQUIRED)


add_subdirectory(Snake_cpp_qt)

add_subdirectory(Test)

