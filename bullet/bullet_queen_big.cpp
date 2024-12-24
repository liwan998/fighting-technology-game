#include "bullet_queen_big.h"
#include"resources_manager.h"
#include"character_manager.h"

Bullet_queen_big::Bullet_queen_big(QObject *parent)
    : Bullet{parent}
{
    bullet_img=Resources_manager::instance()->find_image("queen_big_bullet");
    bullet_animation.add_fram(Resources_manager::instance()->find_atlas("queen_big_bullet"));
    bullet_box->set_size({70,70});
    effects.add_fram(Resources_manager::instance()->find_atlas("a"));
    effects.set_is_loop(true);
    effects.set_interval(0.1f);
}

Bullet_queen_big::~Bullet_queen_big()
{

}

void Bullet_queen_big::on_enter(Player::Player_select player_select)
{
    Bullet::on_enter(player_select);
    bullet_box->set_on_collide([&]{
        if(impactTarget==Player::Player_select::left)
            Character_Manager::instance()->get_player()->decrease_hp(8);
        else
            Character_Manager::instance()->get_player2()->decrease_hp(8);

        bullet_collision=true;
        bullet_box->set_enabled(false);
        velocity=QPointF(0,0);
    });
}

void Bullet_queen_big::on_update(float delta)
{
    effects.set_position(position+QPointF(-30,-30));
    effects.on_update(delta);
    Bullet::on_update(delta);
}

void Bullet_queen_big::on_render(QPainter &painter)
{
    Bullet::on_render(painter);
    effects.on_render(painter);
}
