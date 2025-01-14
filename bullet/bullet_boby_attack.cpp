#include "bullet_boby_attack.h"
#include"resources_manager.h"
#include"character_manager.h"

Bullet_Boby_attack::Bullet_Boby_attack(bool is_left,QObject *parent)
    : Bullet{parent}
{
    if(is_left){
        bullet_img=Resources_manager::instance()->find_atlas("fire_bomb_left")->get_image(0);
        bullet_animation.add_fram(Resources_manager::instance()->find_atlas("fire_bomb_left"));
    }else{
        bullet_img=Resources_manager::instance()->find_atlas("fire_bomb_right")->get_image(0);
        bullet_animation.add_fram(Resources_manager::instance()->find_atlas("fire_bomb_right"));
    }
    bullet_box->set_size({80,50});
    animation_offset={-24,-34};
}

void Bullet_Boby_attack::on_enter(Character::Player_select player_select)
{
    Bullet::on_enter(player_select);
    bullet_box->set_on_collide([&]{
        if(impactTarget==Player::Player_select::left)
            Character_Manager::instance()->get_player()->decrease_hp(6);
        else
            Character_Manager::instance()->get_player2()->decrease_hp(6);

        bullet_collision=true;
        bullet_box->set_enabled(false);
        velocity=QPointF(0,0);
    });
}
