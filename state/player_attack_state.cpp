#include "player_attack_state.h"
#include"character_manager.h"

Player_Attack_State::Player_Attack_State(Player::Player_select player_select,QObject *parent)
    : State_Node{parent}
{
    this->player_select=player_select;

    timer.set_one_shot(true);
    timer.set_on_timeout(
        [=]() {
            if(player_select==Player::Player_select::left){
                Player* player = static_cast<Player*>(Character_Manager::instance()->get_player());
                player->setIs_attack(false);
            }else{
                Player* player = static_cast<Player*>(Character_Manager::instance()->get_player2());
                player->setIs_attack(false);
            }
        }
    );
}


void Player_Attack_State::on_enter()
{
    Player* player=nullptr;
    if(player_select==Player::Player_select::left){
        player = static_cast<Player*>(Character_Manager::instance()->get_player());
    }else{
        player = static_cast<Player*>(Character_Manager::instance()->get_player2());
    }
    player->set_animation("attack");
    player->get_hit_attack_box()->set_enabled(true);
    player->setIs_attack(true);
    player->setIs_key_control(false);
    update_hit_box_position();
    player->on_attack();
    timer.restart();
}

void Player_Attack_State::on_update(float delta)
{
    timer.on_update(delta);
    update_hit_box_position();

    Player* player=nullptr;
    if(player_select==Player::Player_select::left){
        player = static_cast<Player*>(Character_Manager::instance()->get_player());
    }else{
        player = static_cast<Player*>(Character_Manager::instance()->get_player2());
    }
    if (player->get_hp() <= 0) {
        player->switch_state("dead");
    }else if (!player->getIs_attack()) {
        if (player->get_velocity().y() > 0)
            player->switch_state("fall");
        else if (player->get_move_axis() == 0)
            player->switch_state("idle");
        else if (player->is_on_floor() && player->get_move_axis() != 0)
            player->switch_state("run");
    }
}

void Player_Attack_State::on_exit()
{
    Player* player=nullptr;
    if(player_select==Player::Player_select::left){
        player = static_cast<Player*>(Character_Manager::instance()->get_player());
    }else{
        player = static_cast<Player*>(Character_Manager::instance()->get_player2());
    }

    player->setIs_attack(false);
    player->get_hit_attack_box()->set_enabled(false);
    player->setIs_key_control(true);
}

void Player_Attack_State::setTimerWaitTime(float time)
{
    timer.set_wait_time(time);
}

void Player_Attack_State::update_hit_box_position()
{
    Player* player=nullptr;
    if(player_select==Player::Player_select::left){
        player = static_cast<Player*>(Character_Manager::instance()->get_player());
    }else{
        player = static_cast<Player*>(Character_Manager::instance()->get_player2());
    }

    QPointF pos_center = player->get_logic_center();
    Collision_box* hit_box = player->get_hit_attack_box();
    const QPointF& size_hit_box = hit_box->get_size();
    QPointF pos_hit_box;
    if(player->getIs_facing_left()){
        pos_hit_box = { pos_center.x() - size_hit_box.x() / 2,pos_center.y() };
    }else{
        pos_hit_box = { pos_center.x() + size_hit_box.x() / 2,pos_center.y() };
    }
    hit_box->set_position(pos_hit_box);
}
