#include "player_run_state.h"
#include"character_manager.h"

Player_Run_State::Player_Run_State(Player::Player_select player_select,QObject *parent)
    : State_Node{parent}
{
    this->player_select=player_select;
}

void Player_Run_State::on_enter()
{
    Player* player=nullptr;
    if(player_select==Player::Player_select::left){
        player = static_cast<Player*>(Character_Manager::instance()->get_player());
    }else{
        player = static_cast<Player*>(Character_Manager::instance()->get_player2());
    }
    player->set_animation("run");
}

void Player_Run_State::on_update(float delta)
{
    Player* player=nullptr;
    if(player_select==Player::Player_select::left){
        player = static_cast<Player*>(Character_Manager::instance()->get_player());
    }else{
        player = static_cast<Player*>(Character_Manager::instance()->get_player2());
    }

    if (player->get_hp() <= 0) {
        player->switch_state("dead");
    }
    else if (player->get_move_axis() == 0) {
        player->switch_state("idle");
    }
    else if(player->can_jump()) {
        player->switch_state("jump");
    }
    else if (player->can_attack()) {
        player->switch_state("attack");
    }else if(player->can_skill()){
        player->switch_state("skill");
    }else if (player->can_roll()) {
        player->switch_state("roll");
    }
}

void Player_Run_State::on_exit()
{
}
