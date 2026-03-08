cmake_minimum_required(VERSION 3.16)

project(labPowersupplyGUI VERSION 0.1 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 23)  # Use 11, 14, 17, 20, or 23
set(CMAKE_CXX_STANDARD_REQUIRED ON)  # Force the standard, don't fall back
set(CMAKE_CXX_EXTENSIONS OFF)  # Use -std=c++17 instead of -std=gnu++17

find_package(Qt6 REQUIRED COMPONENTS Quick)
find_package(serial_cpp REQUIRED)

qt_standard_project_setup(REQUIRES 6.8)

qt_add_executable(applabPowersupplyGUI
    main.cpp
)

qt_add_executable(testCoreFunctionality
    corefuntionalitytests.cpp
)


qt_add_qml_module(applabPowersupplyGUI
    URI labPowersupplyGUI
    QML_FILES
        Main.qml
        SOURCES psu.h psu.cpp
        SOURCES utils.h utils.cpp
        RESOURCES LICENSE.txt
        RESOURCES README.md
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(applabPowersupplyGUI PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.applabPowersupplyGUI
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(applabPowersupplyGUI
    PRIVATE
    Qt6::Quick
    serial_cpp::serial_cpp
)

include(GNUInstallDirs)
install(TARGETS applabPowersupplyGUI
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
