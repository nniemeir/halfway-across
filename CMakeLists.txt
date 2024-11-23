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
        src/ui/mainwindow.cpp
        include/ui/mainwindow.h
        src/ui/mainwindow.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(Halfway_Across
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        include/core/audio.h
        include/core/handling/encounterhandler.h
        include/core/handling/inputhandler.h
        include/core/handling/msghandler.h
        include/core/handling/verbhandler.h
        include/core/world.h
        include/entities/characters.h
        include/entities/dialogue.h
        include/entities/locations.h
        include/entities/player.h
        include/items/inventory.h
        include/items/item.h
        include/items/recipe.h
        include/survival/fishing.h
        include/survival/hunting.h
        include/utils/script.h
        resources/resources.qrc
        src/core/audio.cpp
        src/core/handling/encounterhandler.cpp
        src/core/handling/inputhandler.cpp
        src/core/handling/msghandler.cpp
        src/core/handling/verbhandler.cpp
        src/core/world.cpp
        src/entities/characters.cpp
        src/entities/dialogue.cpp
        src/entities/encounters/amosE1.cpp
        src/entities/encounters/iraE1.cpp
        src/entities/locations.cpp
        src/entities/player.cpp
        src/items/inventory.cpp
        src/items/item.cpp
        src/items/recipe.cpp
        src/survival/fishing.cpp
        src/survival/hunting.cpp
        src/utils/script.cpp
        src/verbs/dialogue/goodbye.cpp
        src/verbs/dialogue/greet.cpp
        src/verbs/dialogue/talk.cpp
        src/verbs/items/cook.cpp
        src/verbs/items/craft.cpp
        src/verbs/items/drink.cpp
        src/verbs/items/eat.cpp
        src/verbs/items/examine.cpp
        src/verbs/items/fill.cpp
        src/verbs/items/load.cpp
        src/verbs/items/put.cpp
        src/verbs/items/read.cpp
        src/verbs/items/remove.cpp
        src/verbs/items/skin.cpp
        src/verbs/items/take.cpp
        src/verbs/items/use.cpp
        src/verbs/items/wear.cpp
        src/verbs/menu/begin.cpp
        src/verbs/navigation/look.cpp
        src/verbs/navigation/move.cpp
        src/verbs/navigation/sit.cpp
        src/verbs/navigation/stand.cpp
        src/verbs/survival/cry.cpp
        src/verbs/survival/hunt.cpp
        src/verbs/survival/shoot.cpp
        src/verbs/survival/yell.cpp
        src/verbs/time/sleep.cpp
        src/verbs/time/wait.cpp
        src/verbs/utils/diagnose.cpp
        src/verbs/utils/help.cpp
        src/verbs/utils/script.cpp
        src/verbs/utils/version.cpp
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
