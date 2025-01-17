#include "levels_3.h"
#include"resources_manager.h"
#include"sound_manager.h"

Levels_3::Levels_3(QWidget *parentr)
    :Levels_Base(parentr) {
    background=Resources_manager::instance()->find_image("background2");
    background_music=Sound_manager::instance()->find_background_music("game3");
    FLOOR_Y=615;
}
