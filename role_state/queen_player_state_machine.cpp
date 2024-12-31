#include "queen_player_state_machine.h"
#include"character_manager.h"

Queen_Player_Attack_State::Queen_Player_Attack_State(Player::Player_select player_select, QObject *parent)
    : Player_Attack_State{player_select,parent}
{
    timer.set_wait_time(1.89f);
}

void Queen_Player_Attack_State::update_hit_box_position()
{
    Player* player=nullptr;
    if(player_select==Player::Player_select::left){
        player = static_cast<Player*>(Character_Manager::instance()->get_player());
    }else{
        player = static_cast<Player*>(Character_Manager::instance()->get_player2());
    }

    QPointF pos_center = player->get_logic_center();
    player->get_hit_attack_box()->set_position(pos_center);
}

Queen_Player_Dead_State::Queen_Player_Dead_State(Player::Player_select player_select, QObject *parent)
    : Player_Dead_State{player_select,parent}
{}

Queen_Player_Fall_State::Queen_Player_Fall_State(Player::Player_select player_select, QObject *parent)
    : Player_Fall_State{player_select,parent}
{}

Queen_Player_Idle_State::Queen_Player_Idle_State(Player::Player_select player_select, QObject *parent)
    : Player_Idle_State{player_select,parent}
{}

Queen_Player_Jump_State::Queen_Player_Jump_State(Player::Player_select player_select, QObject *parent)
    : Player_Jump_State{player_select,parent}
{}

Queen_Player_Roll_State::Queen_Player_Roll_State(Player::Player_select player_select, QObject *parent)
    : Player_Roll_State{player_select,parent}
{
    timer.set_wait_time(0.5f);
}

Queen_Player_Run_State::Queen_Player_Run_State(Player::Player_select player_select, QObject *parent)
    : Player_Run_State{player_select,parent}
{}

Queen_Player_Skill_State::Queen_Player_Skill_State(Player::Player_select player_select, QObject *parent)
    : Player_Skill_State{player_select,parent}
{
    timer.set_wait_time(1.54f);
}
