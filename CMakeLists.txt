cmake_minimum_required(VERSION 3.16)

project(Halfway_Across VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Multimedia)
include_directories(${Qt5Core_INCLUDE_DIRS} ${Qt5Gui_INCLUDE_DIRS} ${Qt5Multimedia_INCLUDE_DIRS})

set(PROJECT_SOURCES
        src/main.cpp
        src/mainwindow.cpp
        include/mainwindow.h
        src/mainwindow.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(Halfway_Across
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        include/audio.h
        include/characters.h
        include/fishing.h
        include/handling.h
        include/hunting.h
        include/inventory.h
        include/item.h
        include/locations.h
        include/player.h
        include/journal.h
        include/recipe.h
        include/world.h
        resources/resources.qrc
        src/audio.cpp
        src/characters.cpp
        src/fishing.cpp
        src/handling.cpp
        src/hunting.cpp
        src/inventory.cpp
        src/item.cpp
        src/journal.cpp
        src/locations.cpp
        src/player.cpp
        src/recipe.cpp
        src/world.cpp
        src/verbs/ask.cpp
        src/verbs/begin.cpp
        src/verbs/cook.cpp
        src/verbs/craft.cpp
        src/verbs/cry.cpp
        src/verbs/drink.cpp
        src/verbs/eat.cpp
        src/verbs/examine.cpp
        src/verbs/fill.cpp
        src/verbs/help.cpp
        src/verbs/hunt.cpp
        src/verbs/load.cpp
        src/verbs/look.cpp
        src/verbs/move.cpp
        src/verbs/put.cpp
        src/verbs/read.cpp
        src/verbs/remove.cpp
        src/verbs/script.cpp
        src/verbs/shoot.cpp
        src/verbs/sit.cpp
        src/verbs/skin.cpp
        src/verbs/sleep.cpp
        src/verbs/stand.cpp
        src/verbs/take.cpp
        src/verbs/tell.cpp
        src/verbs/use.cpp
        src/verbs/version.cpp
        src/verbs/wait.cpp
        src/verbs/wear.cpp
        src/verbs/yell.cpp
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET Halfway_Across APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(Halfway_Across SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(Halfway_Across
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(Halfway_Across PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt6::Multimedia)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.Halfway_Across)
endif()
set_target_properties(Halfway_Across PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS Halfway_Across
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(Halfway_Across)
endif()
