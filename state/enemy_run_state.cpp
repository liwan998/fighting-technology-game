#include "enemy_run_state.h"
#include"character_manager.h"

Enemy_Run_State::Enemy_Run_State(QObject *parent)
    : State_Node{parent}
{}


void Enemy_Run_State::on_enter()
{
    Character_Manager::instance()->get_player2()->set_animation("run");
}

void Enemy_Run_State::on_update(float delta)
{}

void Enemy_Run_State::on_exit()
{}
