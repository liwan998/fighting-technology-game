cmake_minimum_required(VERSION 3.5)
# 在发布版本中禁用 qDebug 输出
if (CMAKE_BUILD_TYPE STREQUAL "Release")
    add_definitions(-DQT_NO_DEBUG_OUTPUT)
endif()

project(fistfight VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Multimedia)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Multimedia)

# 定义源文件
set(PROJECT_SOURCES
    main.cpp
)

# 定义头文件和源文件
set(BASE_CLASS_SOURCES
    base_class/atlas.h base_class/atlas.cpp
    base_class/animation.h base_class/animation.cpp
    base_class/timer.h base_class/timer.cpp
    base_class/resources_manager.h base_class/resources_manager.cpp
    base_class/sound_manager.h base_class/sound_manager.cpp
    base_class/thread_pool.h base_class/thread_pool.cpp
    base_class/rand_number.h base_class/rand_number.cpp
)

set(BOX_SOURCES
    box/collision_box.h box/collision_box.cpp
    box/collision_manager.h box/collision_manager.cpp
)

set(FLOATING_TEXT_SOURCES
    floating_text/floating_text.h floating_text/floating_text.cpp
    floating_text/floating_text_manager.h floating_text/floating_text_manager.cpp
)

set(ROLE_SOURCES
    role/character.h role/character.cpp
    role/character_manager.h role/character_manager.cpp

    role/player.h role/player.cpp
    role/player_pirate.h role/player_pirate.cpp
    role/player_jinbei.h role/player_jinbei.cpp
    role/player_queen.h role/player_queen.cpp
    role/player_baby.h role/player_baby.cpp

    role/enemy.h role/enemy.cpp
    role/enemy_pirate.h role/enemy_pirate.cpp
    role/enemy_queen.h role/enemy_queen.cpp
    role/enemy_jinbei.h role/enemy_jinbei.cpp
    role/enemy_baby.h role/enemy_baby.cpp
)

set(STATE_SOURCES
    state/State_Node.h
    state/player_attack_state.h state/player_attack_state.cpp
    state/player_skill_state.h state/player_skill_state.cpp
    state/player_dead_state.h state/player_dead_state.cpp
    state/player_fall_state.h state/player_fall_state.cpp
    state/player_idle_state.h state/player_idle_state.cpp
    state/player_jump_state.h state/player_jump_state.cpp
    state/player_roll_state.h state/player_roll_state.cpp
    state/player_run_state.h state/player_run_state.cpp
    state/enemy_attack_state.h state/enemy_attack_state.cpp
    state/enemy_skill_state.h state/enemy_skill_state.cpp
    state/enemy_dead_state.h state/enemy_dead_state.cpp
    state/enemy_fall_state.h state/enemy_fall_state.cpp
    state/enemy_idle_state.h state/enemy_idle_state.cpp
    state/enemy_jump_state.h state/enemy_jump_state.cpp
    state/enemy_run_state.h state/enemy_run_state.cpp
    state/state_machine.h state/state_machine.cpp
)

set(ROLE_STATE_SOURCES
    role_state/enemy_state_machine.h role_state/enemy_state_machine.cpp
    role_state/queen_player_state_machine.h role_state/queen_player_state_machine.cpp
    role_state/queen_enemy_state_machine.h role_state/queen_enemy_state_machine.cpp
)

set(INTERFACE_SOURCES
    interface/screen.h interface/screen.cpp
    interface/interface_manager.h interface/interface_manager.cpp
    interface/start.h interface/start.cpp interface/start.ui
    interface/select.h interface/select.cpp interface/select.ui
    interface/game.cpp interface/game.h interface/game.ui
    interface/select_venture.h interface/select_venture.cpp interface/select_venture.ui
    interface/levels_base.h interface/levels_base.cpp
    interface/levels_1.h interface/levels_1.cpp
    interface/levels_2.h interface/levels_2.cpp
    interface/levels_3.h interface/levels_3.cpp
    interface/levels_4.h interface/levels_4.cpp
)

set(BULLET_SOURCES
    bullet/bullet.h bullet/bullet.cpp
    bullet/bullet_manager.h bullet/bullet_manager.cpp
    bullet/bullet_queen_small.h bullet/bullet_queen_small.cpp
    bullet/bullet_queen_big.h bullet/bullet_queen_big.cpp
    bullet/bullet_boby_attack.h bullet/bullet_boby_attack.cpp
    bullet/bullet_boby_skill.h bullet/bullet_boby_skill.cpp
)

set(RESOURCES
    icon.qrc
)

# 创建可执行文件
if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(fistfight MANUAL_FINALIZATION

       )
else()
    if(ANDROID)
        add_library(fistfight SHARED)
    else()
        add_executable(fistfight)
    endif()
endif()

# 添加源文件到目标
target_sources(fistfight PRIVATE
    ${PROJECT_SOURCES}
    ${BASE_CLASS_SOURCES}
    ${BOX_SOURCES}
    ${FLOATING_TEXT_SOURCES}
    ${ROLE_SOURCES}
    ${STATE_SOURCES}
    ${ROLE_STATE_SOURCES}
    ${INTERFACE_SOURCES}
    ${BULLET_SOURCES}
    ${RESOURCES}
)

# 设置包含目录
target_include_directories(fistfight PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/base_class
    ${CMAKE_CURRENT_SOURCE_DIR}/role
    ${CMAKE_CURRENT_SOURCE_DIR}/role_state
    ${CMAKE_CURRENT_SOURCE_DIR}/state
    ${CMAKE_CURRENT_SOURCE_DIR}/box
    ${CMAKE_CURRENT_SOURCE_DIR}/floating_text
    ${CMAKE_CURRENT_SOURCE_DIR}/bullet
    ${CMAKE_CURRENT_SOURCE_DIR}/interface
)

# 链接 Qt 库
target_link_libraries(fistfight PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Multimedia)

# 设置目标属性
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

# 安装目标
include(GNUInstallDirs)
install(TARGETS fistfight
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# 如果是 Qt6，执行最终化操作
if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(fistfight)
endif()
