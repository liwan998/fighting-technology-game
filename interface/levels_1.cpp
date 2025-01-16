#include "levels_1.h"
#include"resources_manager.h"
#include"sound_manager.h"

Levels_1::Levels_1(QWidget *parentr)
    :Levels_Base(parentr) {
    background=Resources_manager::instance()->find_image("background0");
    background_music=Sound_manager::instance()->find_background_music("game");
    FLOOR_Y=710;
}
