add_library(model food.cpp snake.cpp)

target_link_libraries(model PUBLIC constants)

target_include_directories(model
          INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
          )