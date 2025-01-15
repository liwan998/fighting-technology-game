#include "bullet_boby_skill.h"
#include"resources_manager.h"
#include"character_manager.h"
#include<QDebug>

Bullet_Boby_skill::Bullet_Boby_skill(QObject *parent)
    : Bullet{parent}
{
    bullet_img=Resources_manager::instance()->find_image("knife");
    bullet_animation.add_fram(Resources_manager::instance()->find_atlas("boby_skill"));
    bullet_box->set_size({30,120});
}

void Bullet_Boby_skill::on_enter(Character::Player_select player_select)
{
    Bullet::on_enter(player_select);
    bullet_box->set_on_collide([&]{
        if(impactTarget==Player::Player_select::left)
            Character_Manager::instance()->get_player()->decrease_hp(7);
        else
            Character_Manager::instance()->get_player2()->decrease_hp(7);

        bullet_collision=true;
        bullet_box->set_enabled(false);
        velocity=QPointF(0,0);
    });
    qDebug()<<"生成成功";
}
