TEMPLATE = subdirs

# where to find the sub projects - give the folders
Snake_cpp_qt.subdir = Snake_cpp_qt
Test.subdir = Test

# what subproject depends on others
Test.depends = Snake_cpp_qt

SUBDIRS += \
    Snake_cpp_qt \
    Test
