#include "enemy_idle_state.h"
#include"character_manager.h"

Enemy_Idle_State::Enemy_Idle_State(QObject *parent)
    : State_Node{parent}
{
    timer.set_one_shot(true);
    timer.set_on_timeout([&]{
        is_idle=false;
    });
    is_idle=true;
}

void Enemy_Idle_State::on_enter()
{
    Character_Manager::instance()->get_player2()->set_animation("idle");
    timer.restart();
    is_idle=true;
}

void Enemy_Idle_State::on_update(float delta)
{
    timer.on_update(delta);
}

void Enemy_Idle_State::on_exit()
{}
