#include "player_roll_state.h"
#include"character_manager.h"

Player_Roll_State::Player_Roll_State(Player::Player_select player_select,QObject *parent)
    : State_Node{parent}
{
    this->player_select=player_select;

    timer.set_one_shot(true);
    timer.set_on_timeout(
        [&]() {
            if(player_select==Player::Player_select::left){
                Player* player = static_cast<Player*>(Character_Manager::instance()->get_player());
                player->setIs_roll(false);
            }else{
                Player* player = static_cast<Player*>(Character_Manager::instance()->get_player());
                player->setIs_roll(false);
            }
        }
        );
}


void Player_Roll_State::on_enter()
{
    Player* player=nullptr;
    if(player_select==Player::Player_select::left){
        player = static_cast<Player*>(Character_Manager::instance()->get_player());
    }else{
        player = static_cast<Player*>(Character_Manager::instance()->get_player2());
    }
    player->set_animation("roll");
    player->get_hurt_box()->set_enabled(false);
    player->setIs_roll(true);
    player->on_roll();
    timer.restart();
}

void Player_Roll_State::on_update(float delta)
{
    timer.on_update(delta);

    Player* player=nullptr;
    if(player_select==Player::Player_select::left){
        player = static_cast<Player*>(Character_Manager::instance()->get_player());
    }else{
        player = static_cast<Player*>(Character_Manager::instance()->get_player2());
    }

    if (!player->getIs_roll()) {
        if (player->get_move_axis() != 0) {
            player->switch_state("run");
        }
        else if (player->can_jump()) {
            player->switch_state("jump");
        }
        else {
            player->switch_state("idle");
        }
    }
}

void Player_Roll_State::on_exit()
{
    Player* player=nullptr;
    if(player_select==Player::Player_select::left){
        player = static_cast<Player*>(Character_Manager::instance()->get_player());
    }else{
        player = static_cast<Player*>(Character_Manager::instance()->get_player2());
    }
    player->get_hurt_box()->set_enabled(true);
}
