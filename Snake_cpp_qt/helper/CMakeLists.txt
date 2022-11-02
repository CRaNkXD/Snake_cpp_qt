add_library(helper helper.cpp)

target_link_libraries(helper PRIVATE model constants)

target_include_directories(helper
          INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
          )