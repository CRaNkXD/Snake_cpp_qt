add_library(gui dialog_highscore.cpp dialog_highscore.ui dialog_new_highscore.cpp dialog_new_highscore.ui)

target_link_libraries(gui PRIVATE helper model Qt5::Widgets Qt5::Gui)

target_include_directories(gui
          INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
          )