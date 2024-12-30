cmake_minimum_required(VERSION 3.5)

project(fistfight VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Multimedia)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Multimedia)

#add_definitions(-DQT_NO_DEBUG_OUTPUT)#定义QT_NO_DEBUG_OUTPUT宏，从而禁用所有qDebug()调用的输出。

set(PROJECT_SOURCES
        main.cpp
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(fistfight
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}

        base_class/atlas.h base_class/atlas.cpp
        base_class/animation.h base_class/animation.cpp
        base_class/timer.h base_class/timer.cpp
        base_class/resources_manager.h base_class/resources_manager.cpp
        base_class/sound_manager.h base_class/sound_manager.cpp
        base_class/thread_pool.h base_class/thread_pool.cpp

        box/collision_box.h box/collision_box.cpp
        box/collision_manager.h box/collision_manager.cpp

        role/character.h role/character.cpp
        role/character_manager.h role/character_manager.cpp

        role/player.h role/player.cpp
        role/player_pirate.h role/player_pirate.cpp
        role/player2_pirate.h role/player2_pirate.cpp
        role/player_queen.h role/player_queen.cpp
        role/player2_queen.h role/player2_queen.cpp

        role/enemy_pirate.h role/enemy_pirate.cpp
        role/enemy_queen.h role/enemy_queen.cpp

        state/State_Node.h
        state/player_attack_state.h state/player_attack_state.cpp
        state/player_skill_state.h state/player_skill_state.cpp
        state/player_dead_state.h state/player_dead_state.cpp
        state/player_fall_state.h state/player_fall_state.cpp
        state/player_idle_state.h state/player_idle_state.cpp
        state/player_jump_state.h state/player_jump_state.cpp
        state/player_roll_state.h state/player_roll_state.cpp
        state/player_run_state.h state/player_run_state.cpp
        state/state_machine.h state/state_machine.cpp

        role_state/pirate_player_state_machine.h role_state/pirate_player_state_machine.cpp
        role_state/queen_player_state_machine.h role_state/queen_player_state_machine.cpp

        state/player_queen_state_machine.h state/player_queen_state_machine.cpp
        state/player2_queen_state_machine.h state/player2_queen_state_machine.cpp

        state/enemy_pirate_state_machine.h state/enemy_pirate_state_machine.cpp
        state/enemy_queen_state_machine.h state/enemy_queen_state_machine.cpp

        interface/screen.h interface/screen.cpp
        interface/interface_manager.h interface/interface_manager.cpp
        interface/start.h interface/start.cpp interface/start.ui
        interface/select.h interface/select.cpp interface/select.ui
        interface/widget.cpp interface/widget.h interface/widget.ui
        
        bullet/bullet.h bullet/bullet.cpp
        bullet/bullet_queen_small.h bullet/bullet_queen_small.cpp
        bullet/bullet_queen_big.h bullet/bullet_queen_big.cpp
        bullet/bullet_manager.h bullet/bullet_manager.cpp

        icon.qrc
        interface/select_venture.h interface/select_venture.cpp interface/select_venture.ui


    )
    #设置目标的包含目录
    target_include_directories(fistfight PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}    #根目录
        ${CMAKE_CURRENT_SOURCE_DIR}/base_class
        ${CMAKE_CURRENT_SOURCE_DIR}/role
        ${CMAKE_CURRENT_SOURCE_DIR}/role_state
        ${CMAKE_CURRENT_SOURCE_DIR}/state
        ${CMAKE_CURRENT_SOURCE_DIR}/box
        ${CMAKE_CURRENT_SOURCE_DIR}/bullet
        ${CMAKE_CURRENT_SOURCE_DIR}/interface)

# Define target properties for Android with Qt 6 as:
#    set_property(TARGET fistfight APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(fistfight SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(fistfight
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(fistfight PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Multimedia)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.fistfight)
endif()
set_target_properties(fistfight PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS fistfight
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(fistfight)
endif()
