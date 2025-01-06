#include "jinbei_player_state_machine.h"

Jinbei_Player_Attack_State::Jinbei_Player_Attack_State(Player::Player_select player_select, QObject *parent)
    : Player_Attack_State{player_select,parent}
{
    timer.set_wait_time(1.1f);
}

Jinbei_Player_Dead_State::Jinbei_Player_Dead_State(Player::Player_select player_select, QObject *parent)
    : Player_Dead_State{player_select,parent}
{}

Jinbei_Player_Fall_State::Jinbei_Player_Fall_State(Player::Player_select player_select, QObject *parent)
    : Player_Fall_State{player_select,parent}
{}

Jinbei_Player_Idle_State::Jinbei_Player_Idle_State(Player::Player_select player_select, QObject *parent)
    : Player_Idle_State{player_select,parent}
{}

Jinbei_Player_Jump_State::Jinbei_Player_Jump_State(Player::Player_select player_select, QObject *parent)
    : Player_Jump_State{player_select,parent}
{}

Jinbei_Player_Roll_State::Jinbei_Player_Roll_State(Player::Player_select player_select, QObject *parent)
    : Player_Roll_State{player_select,parent}
{
    timer.set_wait_time(0.5f);
}

Jinbei_Player_Run_State::Jinbei_Player_Run_State(Player::Player_select player_select, QObject *parent)
    : Player_Run_State{player_select,parent}
{}

Jinbei_Player_Skill_State::Jinbei_Player_Skill_State(Player::Player_select player_select, QObject *parent)
    : Player_Skill_State{player_select,parent}
{
    timer.set_wait_time(3.0f);
}
