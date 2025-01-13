#include "baby_player_state_machine.h"

Baby_Player_Attack_State::Baby_Player_Attack_State(Player::Player_select player_select, QObject *parent)
    : Player_Attack_State{player_select,parent}
{
    timer.set_wait_time(1.6f);
}

Baby_Player_Dead_State::Baby_Player_Dead_State(Player::Player_select player_select, QObject *parent)
    : Player_Dead_State{player_select,parent}
{}

Baby_Player_Fall_State::Baby_Player_Fall_State(Player::Player_select player_select, QObject *parent)
    : Player_Fall_State{player_select,parent}
{}

Baby_Player_Idle_State::Baby_Player_Idle_State(Player::Player_select player_select, QObject *parent)
    : Player_Idle_State{player_select,parent}
{}

Baby_Player_Jump_State::Baby_Player_Jump_State(Player::Player_select player_select, QObject *parent)
    : Player_Jump_State{player_select,parent}
{}

Baby_Player_Roll_State::Baby_Player_Roll_State(Player::Player_select player_select, QObject *parent)
    : Player_Roll_State{player_select,parent}
{
    timer.set_wait_time(0.5f);
}

Baby_Player_Run_State::Baby_Player_Run_State(Player::Player_select player_select, QObject *parent)
    : Player_Run_State{player_select,parent}
{}

Baby_Player_Skill_State::Baby_Player_Skill_State(Player::Player_select player_select, QObject *parent)
    : Player_Skill_State{player_select,parent}
{
    timer.set_wait_time(4.0f);
}
