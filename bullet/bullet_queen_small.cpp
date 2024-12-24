#include "bullet_queen_small.h"
#include"resources_manager.h"
#include"character_manager.h"

Bullet_queen_small::Bullet_queen_small(QObject *parent)
    : Bullet{parent}
{
    bullet_img=Resources_manager::instance()->find_image("queen_small_bullet");
    bullet_animation.add_fram(Resources_manager::instance()->find_atlas("queen_small_bullet"));
    bullet_box->set_size({30,30});
}

Bullet_queen_small::~Bullet_queen_small()
{

}

void Bullet_queen_small::on_update(float delta)
{
    if(!bullet_collision){
        transform+=delta;
        position_offset={0,50*sin(3.14*transform)};
    }

    Bullet::on_update(delta);
    if(transform>2){
        transform=0;
    }
}

void Bullet_queen_small::on_enter(Player::Player_select player_select)
{
    Bullet::on_enter(player_select);
    bullet_box->set_on_collide([&]{
        if(impactTarget==Player::Player_select::left)
            Character_Manager::instance()->get_player()->decrease_hp(5);
        else
            Character_Manager::instance()->get_player2()->decrease_hp(5);

        bullet_collision=true;
        bullet_box->set_enabled(false);
        velocity=QPointF(0,0);
    });
}
