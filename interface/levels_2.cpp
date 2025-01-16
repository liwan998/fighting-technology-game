#include "levels_2.h"
#include"resources_manager.h"
#include"sound_manager.h"

Levels_2::Levels_2(QWidget *parentr)
    :Levels_Base(parentr) {
    background=Resources_manager::instance()->find_image("background1");
    background_music=Sound_manager::instance()->find_background_music("game");
    FLOOR_Y=690;
}
