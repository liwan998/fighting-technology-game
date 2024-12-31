#include "enemy_dead_state.h"
#include"character_manager.h"

Enemy_Dead_State::Enemy_Dead_State(QObject *parent)
    : State_Node{parent}
{}

void Enemy_Dead_State::on_enter()
{
    Character_Manager::instance()->get_player2()->set_animation("dead");
    Character_Manager::instance()->get_player2()->on_dead();
}

void Enemy_Dead_State::on_update(float delta)
{}

void Enemy_Dead_State::on_exit()
{}
