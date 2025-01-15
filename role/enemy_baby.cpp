#include "enemy_baby.h"
#include"bullet_manager.h"
#include"rand_number.h"
#include<character_manager.h>

Enemy_Baby::Enemy_Baby(QObject *parent)
    : Enemy{parent}
{
    position={1000,400};
    is_facing_left=true;

    position_foot = {156, 239};
    logic_heigth = 142;

    load_effect("pirate",false);
    load_collision_box(Player_select::right);

    hit_attack_box->set_size({20, 20});
    hit_skill_box->set_size({20, 20});
    hurt_box->set_size({20, 80});

    timer_call_interval.set_one_shot(false);
    timer_call_interval.set_wait_time(0.5f);
    timer_call_interval.set_on_timeout([&]{
        timer_call_interval.restart();
        Bullet_Manager::instance()->create_bullet(Bullet_Manager::Bullet_kind::boby_skill, is_facing_left,
                                                  QPointF(random_position_x(),-150), Player_select::right);
    });

    load_hit_interval(attackDuration+0.5,skillDuration+0.5);
    load_hit_box(attack_single_damage,skill_single_damage);
    load_image_resource("baby");
    load_state_node(attackDuration,skillDuration);
}


void Enemy_Baby::on_attack()
{
    Bullet_Manager::instance()->create_bullet(Bullet_Manager::Bullet_kind::boby_attack, is_facing_left,
                                              get_logic_center() - QPointF(0,30), Player_select::right);

    Character::on_attack();
}

void Enemy_Baby::on_skill()
{
    Bullet_Manager::instance()->create_bullet(Bullet_Manager::Bullet_kind::boby_skill, is_facing_left,
                                              QPointF(random_position_x(),-150), Player_select::right);
    timer_call_interval.restart();
    Character::on_skill();
}

void Enemy_Baby::on_update(float delta)
{
    if(is_skill){
        timer_call_interval.on_update(delta);
    }
    Character::on_update(delta);
}

int Enemy_Baby::random_position_x()
{
    int x;
    Character *player=Character_Manager::instance()->get_player();
    x=player->get_position().x();
    x+=player->getPosition_foot().x();
    x+=Rand_number::instance()->randomInt(-50,50);
    return x;
}
