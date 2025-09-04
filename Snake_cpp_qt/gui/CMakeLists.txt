add_library(
    gui dialog_highscore.cpp
    dialog_highscore.ui
    dialog_new_highscore.cpp 
    dialog_new_highscore.ui
    dialog_settings.cpp 
    dialog_settings.ui)

target_link_libraries(gui PRIVATE helper model Qt6::Widgets Qt6::Gui)

target_include_directories(gui
          INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
          )