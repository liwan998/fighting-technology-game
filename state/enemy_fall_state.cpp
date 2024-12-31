#include "enemy_fall_state.h"
#include"character_manager.h"

Enemy_Fall_State::Enemy_Fall_State(QObject *parent)
    : State_Node{parent}
{}

void Enemy_Fall_State::on_enter()
{
    Character_Manager::instance()->get_player2()->set_animation("fall");
}

void Enemy_Fall_State::on_update(float delta)
{}

void Enemy_Fall_State::on_exit()
{}
