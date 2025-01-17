#include "player_baby.h"
#include"bullet_manager.h"
#include"rand_number.h"
#include<character_manager.h>

Player_Baby::Player_Baby(Player_select player_select,QObject *parent)
    : Player{parent}
{
    this->player_selects = player_select;

    position = (player_select == Player_select::left) ? QPointF{0, 400} : QPointF{1000, 400};
    is_facing_left = (player_select == Player_select::right);

    position_foot = {156, 239};
    logic_heigth = 142;

    load_effect("baby",false);
    load_collision_box(player_select);

    hit_attack_box->set_size({20, 20});
    hit_skill_box->set_size({20, 20});
    hurt_box->set_size({20, 80});

    load_hit_interval(attackDuration+0.5,skillDuration+0.5);
    load_hit_box(player_selects,attack_single_damage,skill_single_damage);
    load_hit_CD(CD_attack,CD_skill);

    timer_call_interval.set_one_shot(false);
    timer_call_interval.set_wait_time(0.2f);
    timer_call_interval.set_on_timeout([&]{
        timer_call_interval.restart();
        Bullet_Manager::instance()->create_bullet(Bullet_Manager::Bullet_kind::boby_skill, is_facing_left,
                                                  QPointF(random_position_x(),-150), player_selects);
    });

    load_image_resource("baby");
    load_state_node(player_selects,attackDuration,skillDuration);
}


void Player_Baby::on_attack()
{
    Bullet_Manager::instance()->create_bullet(Bullet_Manager::Bullet_kind::boby_attack, is_facing_left,
                                              get_logic_center() - QPointF(0,30), player_selects);

    Player::on_attack();
}

void Player_Baby::on_skill()
{
    Bullet_Manager::instance()->create_bullet(Bullet_Manager::Bullet_kind::boby_skill, is_facing_left,
                                              QPointF(random_position_x(),-150), player_selects);
    timer_call_interval.restart();
    Player::on_skill();
}

void Player_Baby::on_update(float delta)
{
    if(is_skill){
        timer_call_interval.on_update(delta);
    }
    Player::on_update(delta);
}

int Player_Baby::random_position_x()
{
    int x;
    Character *player=nullptr;
    if(player_selects==Player::Player_select::left){
        player=Character_Manager::instance()->get_player2();
    }else{
        player=Character_Manager::instance()->get_player();
    }
    x=player->get_position().x();
    x+=player->getPosition_foot().x();
    x+=Rand_number::instance()->randomInt(-50,50);
    return x;
}
