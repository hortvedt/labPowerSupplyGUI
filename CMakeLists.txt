cmake_minimum_required(VERSION 3.16)

project(labPowersupplyGUI VERSION 0.1 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 23)  # Use 11, 14, 17, 20, or 23
set(CMAKE_CXX_STANDARD_REQUIRED ON)  # Force the standard, don't fall back
set(CMAKE_CXX_EXTENSIONS OFF)  # Use -std=c++17 instead of -std=gnu++17

find_package(Qt6 REQUIRED COMPONENTS Quick)
find_package(serial_cpp REQUIRED)
find_package(Boost REQUIRED COMPONENTS unit_test_framework CONFIG)
find_package(yaml-cpp REQUIRED )

qt_standard_project_setup(REQUIRES 6.8)

qt_add_executable(applabPowersupplyGUI
    main.cpp
)

qt_add_qml_module(applabPowersupplyGUI
    URI labPowersupplyGUI
    QML_FILES
        AppMenuBar.qml
        AppTabBar.qml
        AppToolBar.qml
        LedIndicator.qml
        Main.qml
        StandardTab.qml
        StatusLamp.qml
    SOURCES
        applicationcontroller.h applicationcontroller.cpp
        batterycharger.h batterycharger.cpp
        bccontroller.h bccontroller.cpp
        comboboxmodel.h comboboxmodel.cpp
        csvcontroller.h csvcontroller.cpp
        psu.h psu.cpp
        psucontroller.h psucontroller.cpp
        serialsetupcontroller.h serialsetupcontroller.cpp
        singletonclass.h singletonclass.cpp
        unitdefinitions.h
        utils.h utils.cpp
    RESOURCES
        LICENSE.txt
        README.md
        QML_FILES ConnectingTab.qml
        QML_FILES
        QML_FILES LabelComboBox.qml
        SOURCES connectioncontroller.h connectioncontroller.cpp

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
    yaml-cpp::yaml-cpp
)

# ============================================================
# Unit Tests
# ============================================================

# Create a library with the core functionality to be tested
# This avoids linking Qt and other dependencies if they're not needed for tests
add_library(core_functionality STATIC
    batterycharger.cpp
    psu.cpp
    utils.cpp
)

target_include_directories(core_functionality
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)
# If your core functionality doesn't need Qt, you can skip linking it
# But if it does, uncomment the next line:
# target_link_libraries(core_functionality PRIVATE Qt6::Core)

# Create test executable
add_executable(testCoreFunctionality
    corefuntionalitytests.cpp
)

target_include_directories(testCoreFunctionality
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)


# Link the test executable with Boost.Test and the core functionality library
target_link_libraries(testCoreFunctionality
    PRIVATE
    Boost::unit_test_framework
    core_functionality
    # If your tests need serial_cpp, uncomment the next line:
    # serial_cpp::serial_cpp
)

# Enable testing for CTest
enable_testing()

# Add the test to CTest
add_test(NAME CoreFunctionalityTest
    COMMAND testCoreFunctionality
)

# Optional: Add a custom target to run tests easily
add_custom_target(check
    COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure
    DEPENDS testCoreFunctionality
    COMMENT "Running unit tests..."
)


# ============================================================
# Installation
# ============================================================

include(GNUInstallDirs)
install(TARGETS applabPowersupplyGUI
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
