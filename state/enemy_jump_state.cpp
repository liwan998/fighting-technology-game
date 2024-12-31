#include "enemy_jump_state.h"
#include"character_manager.h"

Enemy_Jump_State::Enemy_Jump_State(QObject *parent)
    : State_Node{parent}
{}


void Enemy_Jump_State::on_enter()
{
    Character_Manager::instance()->get_player2()->set_animation("jump");
    Character_Manager::instance()->get_player2()->on_jump();
}

void Enemy_Jump_State::on_update(float delta)
{}

void Enemy_Jump_State::on_exit()
{}
