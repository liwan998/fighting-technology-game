#include "enemy_state_machine.h"
#include"character_manager.h"
#include"rand_number.h"

Ordinary_Enemy_Attack_State::Ordinary_Enemy_Attack_State(QObject *parent)
{}

void Ordinary_Enemy_Attack_State::on_update(float delta)
{
    Enemy_Attack_State::on_update(delta);
    auto* enemy = Character_Manager::instance()->get_player2();

    if(enemy->get_hp()<0){
        enemy->switch_state("dead");
    }else if(!enemy->getIs_attack()){
        int ran = Rand_number::instance()->randomInt(1,100);
        if(ran>=60){
            enemy->switch_state("idle");
        }else if(ran>=20){
            enemy->switch_state("run");
        }else if(ran>=10){
            enemy->switch_state("skill");
        }else{
            enemy->switch_state("jump");
        }
    }
}

Ordinary_Enemy_Dead_State::Ordinary_Enemy_Dead_State(QObject *parent)
{}

Ordinary_Enemy_Fall_State::Ordinary_Enemy_Fall_State(QObject *parent)
{}

void Ordinary_Enemy_Fall_State::on_update(float delta)
{
    auto enemy=Character_Manager::instance()->get_player2();
    if(enemy->get_hp()<=0){
        enemy->switch_state("dead");
    }else if(enemy->is_on_floor()){
        int ran = Rand_number::instance()->randomInt(1,100);
        if(ran>=80){
            enemy->switch_state("attack");
        }else if(ran>=60){
            enemy->switch_state("skill");
        }else if(ran>=20){
            enemy->switch_state("run");
        }else{
            enemy->switch_state("idle");
        }
    }
}

Ordinary_Enemy_Idle_State::Ordinary_Enemy_Idle_State(QObject *parent)
{}

void Ordinary_Enemy_Idle_State::on_update(float delta)
{
    Enemy_Idle_State::on_update(delta);

    auto enemy=Character_Manager::instance()->get_player2();
    if(enemy->get_hp()<0){
        enemy->switch_state("dead");
    }else if(!is_idle){
        int ran = Rand_number::instance()->randomInt(1,100);
        if(ran>=70){
            enemy->switch_state("attack");
        }else if(ran>=40){
            enemy->switch_state("skill");
        }else if(ran>=20){
            enemy->switch_state("run");
        }else{
            enemy->switch_state("jump");
        }
    }
}

Ordinary_Enemy_Jump_State::Ordinary_Enemy_Jump_State(QObject *parent)
{}

void Ordinary_Enemy_Jump_State::on_update(float delta)
{
    auto enemy=Character_Manager::instance()->get_player2();
    if(enemy->get_hp()<0){
        enemy->switch_state("dead");
    }else if(enemy->is_on_floor()){
        int ran = Rand_number::instance()->randomInt(1,100);
        if(ran>=80){
            enemy->switch_state("attack");
        }else if(ran>=60){
            enemy->switch_state("skill");
        }else if(ran>=20){
            enemy->switch_state("run");
        }else{
            enemy->switch_state("idle");
        }
    }
}

Ordinary_Enemy_Run_State::Ordinary_Enemy_Run_State(QObject *parent)
{}

void Ordinary_Enemy_Run_State::on_update(float delta)
{
    auto player=Character_Manager::instance()->get_player();
    auto enemy=Character_Manager::instance()->get_player2();
    float distance=player->get_position().x()-enemy->get_position().x()+
                     player->getPosition_foot().x()-enemy->getPosition_foot().x();

    if(enemy->get_hp()<0){
        enemy->switch_state("dead");
    }else if(abs(distance)>80){
        enemy->set_position(enemy->get_position()+(distance>0?QPointF(4,0):QPointF(-4,0)));
    }else{
        int ran = Rand_number::instance()->randomInt(1,100);
        if(ran>=80){
            enemy->switch_state("idle");
        }else if(ran>=60){
            enemy->switch_state("attack");
        }else if(ran>=40){
            enemy->switch_state("skill");
        }else if(ran>=0){
            enemy->switch_state("jump");
        }
    }
}

Ordinary_Enemy_Skill_State::Ordinary_Enemy_Skill_State(QObject *parent)
{
    timer.set_wait_time(2.7f);
}

void Ordinary_Enemy_Skill_State::on_update(float delta)
{
    Enemy_Skill_State::on_update(delta);
    auto* enemy = Character_Manager::instance()->get_player2();

    if(enemy->get_hp()<0){
        enemy->switch_state("dead");
    }else if(!enemy->getIs_skill()){
        int ran = Rand_number::instance()->randomInt(1,100);
        if(ran>=60){
            enemy->switch_state("idle");
        }else if(ran>=10){
            enemy->switch_state("run");
        }else{
            enemy->switch_state("jump");
        }
    }
}
