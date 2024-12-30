#include "player_dead_state.h"
#include"character_manager.h"

Player_Dead_State::Player_Dead_State(Player::Player_select player_select,QObject *parent)
    : State_Node{parent}
{
    this->player_select=player_select;
}


void Player_Dead_State::on_enter()
{
    Player* player=nullptr;
    if(player_select==Player::Player_select::left){
        player = static_cast<Player*>(Character_Manager::instance()->get_player());
    }else{
        player = static_cast<Player*>(Character_Manager::instance()->get_player2());
    }
    player->set_animation("dead");
    player->on_dead();
}

void Player_Dead_State::on_update(float delta)
{
}

void Player_Dead_State::on_exit()
{
}
