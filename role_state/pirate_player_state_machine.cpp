#include "pirate_player_state_machine.h"

Pirate_Player_Attack_State::Pirate_Player_Attack_State(Player::Player_select player_select, QObject *parent)
    : Player_Attack_State{player_select,parent}
{
    timer.set_wait_time(1.1f);
}

Pirate_Player_Dead_State::Pirate_Player_Dead_State(Player::Player_select player_select, QObject *parent)
    : Player_Dead_State{player_select,parent}
{}

Pirate_Player_Fall_State::Pirate_Player_Fall_State(Player::Player_select player_select, QObject *parent)
    : Player_Fall_State{player_select,parent}
{}

Pirate_Player_Idle_State::Pirate_Player_Idle_State(Player::Player_select player_select, QObject *parent)
: Player_Idle_State{player_select,parent}
{}

Pirate_Player_Jump_State::Pirate_Player_Jump_State(Player::Player_select player_select, QObject *parent)
: Player_Jump_State{player_select,parent}
{}

Pirate_Player_Roll_State::Pirate_Player_Roll_State(Player::Player_select player_select, QObject *parent)
: Player_Roll_State{player_select,parent}
{
    timer.set_wait_time(0.5f);
}

Pirate_Player_Run_State::Pirate_Player_Run_State(Player::Player_select player_select, QObject *parent)
: Player_Run_State{player_select,parent}
{}

Pirate_Player_Skill_State::Pirate_Player_Skill_State(Player::Player_select player_select, QObject *parent)
: Player_Skill_State{player_select,parent}
{
    timer.set_wait_time(2.70f);
}
