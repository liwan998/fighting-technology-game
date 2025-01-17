#include "levels_4.h"
#include"resources_manager.h"
#include"sound_manager.h"

Levels_4::Levels_4(QWidget *parentr)
    :Levels_Base(parentr) {
    background=Resources_manager::instance()->find_image("background3");
    background_music=Sound_manager::instance()->find_background_music("game4");
    FLOOR_Y=630;
}
