#include "enemy_pirate_state_machine.h"
#include"character_manager.h"
#include<QRandomGenerator>

Enemy_Pirate_Attack_State::Enemy_Pirate_Attack_State()
{
    timer.set_wait_time(1.1f);
    timer.set_one_shot(true);
    timer.set_on_timeout(
        [&]() {
            auto* enemy =Character_Manager::instance()->get_player2();
            enemy->setIs_attack(false);
        }
        );
}

void Enemy_Pirate_Attack_State::on_enter()
{
    Character_Manager::instance()->get_player2()->set_animation("enemy_pirate_attack");
    auto* enemy = Character_Manager::instance()->get_player2();
    enemy->get_hit_attack_box()->set_enabled(true);
    enemy->setIs_attack(true);
    update_hit_box_position();
    enemy->on_attack();
    timer.restart();
}

void Enemy_Pirate_Attack_State::on_update(float delta)
{
    timer.on_update(delta);
    update_hit_box_position();

    auto* enemy = Character_Manager::instance()->get_player2();

    if(enemy->get_hp()<0){
        enemy->switch_state("enemy_pirate_dead");
    }else if(!enemy->getIs_attack()){
        int ran = QRandomGenerator::global()->bounded(100);
        if(ran>=60){
            enemy->switch_state("enemy_pirate_idle");
        }else if(ran>=20){
            enemy->switch_state("enemy_pirate_run");
        }else if(ran>=10){
            enemy->switch_state("enemy_pirate_skill");
        }else{
            enemy->switch_state("enemy_pirate_jump");
        }
    }
}

void Enemy_Pirate_Attack_State::on_exit()
{
    auto enemy = Character_Manager::instance()->get_player2();
    enemy->setIs_attack(false);
    enemy->get_hit_attack_box()->set_enabled(false);
}

void Enemy_Pirate_Attack_State::update_hit_box_position()
{
    auto* enemy = Character_Manager::instance()->get_player2();
    QPointF pos_center = enemy->get_logic_center();
    Collision_box* hit_box = enemy->get_hit_attack_box();
    const QPointF& size_hit_box = hit_box->get_size();
    QPointF pos_hit_box;
    if(enemy->getIs_facing_left()){
        pos_hit_box = { pos_center.x() - size_hit_box.x() / 2,pos_center.y() };
    }else{
        pos_hit_box = { pos_center.x() + size_hit_box.x() / 2,pos_center.y() };
    }
    hit_box->set_position(pos_hit_box);
}

Enemy_Pirate_Skill_State::Enemy_Pirate_Skill_State()
{
    timer.set_wait_time(2.7f);
    timer.set_one_shot(true);
    timer.set_on_timeout(
        [&]() {
            auto* enemy =Character_Manager::instance()->get_player2();
            enemy->setIs_skill(false);
        }
        );
}

void Enemy_Pirate_Skill_State::on_enter()
{
    Character_Manager::instance()->get_player2()->set_animation("enemy_pirate_skill");
    auto* enemy = Character_Manager::instance()->get_player2();
    enemy->get_hit_skill_box()->set_enabled(true);
    enemy->setIs_skill(true);
    update_hit_box_position();
    enemy->on_skill();
    timer.restart();
}

void Enemy_Pirate_Skill_State::on_update(float delta)
{
    timer.on_update(delta);
    update_hit_box_position();

    auto* enemy = Character_Manager::instance()->get_player2();

    if(enemy->get_hp()<0){
        enemy->switch_state("enemy_pirate_dead");
    }else if(!enemy->getIs_skill()){
        int ran = QRandomGenerator::global()->bounded(100);
        if(ran>=60){
            enemy->switch_state("enemy_pirate_idle");
        }else if(ran>=10){
            enemy->switch_state("enemy_pirate_run");
        }else{
            enemy->switch_state("enemy_pirate_jump");
        }
    }

}

void Enemy_Pirate_Skill_State::on_exit()
{
    auto enemy = Character_Manager::instance()->get_player2();
    enemy->setIs_skill(false);
    enemy->get_hit_skill_box()->set_enabled(false);
}

void Enemy_Pirate_Skill_State::update_hit_box_position()
{
    auto* enemy = Character_Manager::instance()->get_player2();
    QPointF pos_center = enemy->get_logic_center();
    Collision_box* hit_box = enemy->get_hit_skill_box();
    const QPointF& size_hit_box = hit_box->get_size();
    QPointF pos_hit_box;
    if(enemy->getIs_facing_left()){
        pos_hit_box = { pos_center.x() - size_hit_box.x() / 2,pos_center.y() };
    }else{
        pos_hit_box = { pos_center.x() + size_hit_box.x() / 2,pos_center.y() };
    }
    hit_box->set_position(pos_hit_box);
}

Enemy_Pirate_Dead_State::Enemy_Pirate_Dead_State()
{}

void Enemy_Pirate_Dead_State::on_enter()
{
    Character_Manager::instance()->get_player2()->set_animation("enemy_pirate_dead");
    Character_Manager::instance()->get_player2()->on_dead();
}

void Enemy_Pirate_Dead_State::on_update(float delta)
{}

Enemy_Pirate_Fall_State::Enemy_Pirate_Fall_State()
{}

void Enemy_Pirate_Fall_State::on_enter()
{
    Character_Manager::instance()->get_player2()->set_animation("enemy_pirate_fall");
}

void Enemy_Pirate_Fall_State::on_update(float delta)
{
    auto enemy=Character_Manager::instance()->get_player2();
    if(enemy->get_hp()<=0){
        enemy->switch_state("enemy_pirate_dead");
    }else if(enemy->is_on_floor()){
        int ran = QRandomGenerator::global()->bounded(100);
        if(ran>=80){
            enemy->switch_state("enemy_pirate_attack");
        }else if(ran>=60){
            enemy->switch_state("enemy_pirate_skill");
        }else if(ran>=20){
            enemy->switch_state("enemy_pirate_run");
        }else{
            enemy->switch_state("enemy_pirate_idle");
        }
    }
}

Enemy_Pirate_Idle_State::Enemy_Pirate_Idle_State()
{
    timer.set_wait_time(1.0f);
    timer.set_one_shot(true);
    timer.set_on_timeout([&]{
        is_idle=false;
    });
    is_idle=true;
}

void Enemy_Pirate_Idle_State::on_enter()
{
    Character_Manager::instance()->get_player2()->set_animation("enemy_pirate_idle");
    timer.restart();
    is_idle=true;
}

void Enemy_Pirate_Idle_State::on_update(float delta)
{
    timer.on_update(delta);
    auto enemy=Character_Manager::instance()->get_player2();
    if(enemy->get_hp()<0){
        enemy->switch_state("enemy_pirate_dead");
    }else if(!is_idle){
        int ran = QRandomGenerator::global()->bounded(100);
        if(ran>=70){
            enemy->switch_state("enemy_pirate_attack");
        }else if(ran>=40){
            enemy->switch_state("enemy_pirate_skill");
        }else if(ran>=20){
            enemy->switch_state("enemy_pirate_run");
        }else{
            enemy->switch_state("enemy_pirate_jump");
        }
    }
}

Enemy_Pirate_Jump_State::Enemy_Pirate_Jump_State()
{}

void Enemy_Pirate_Jump_State::on_enter()
{
    Character_Manager::instance()->get_player2()->set_animation("enemy_pirate_jump");
    Character_Manager::instance()->get_player2()->on_jump();
}

void Enemy_Pirate_Jump_State::on_update(float delta)
{
    auto enemy=Character_Manager::instance()->get_player2();
    if(enemy->get_hp()<0){
        enemy->switch_state("enemy_pirate_dead");
    }else if(enemy->is_on_floor()){
        int ran = QRandomGenerator::global()->bounded(100);
        if(ran>=80){
            enemy->switch_state("enemy_pirate_attack");
        }else if(ran>=60){
            enemy->switch_state("enemy_pirate_skill");
        }else if(ran>=20){
            enemy->switch_state("enemy_pirate_run");
        }else{
            enemy->switch_state("enemy_pirate_idle");
        }
    }
}

Enemy_Pirate_Run_State::Enemy_Pirate_Run_State()
{}

void Enemy_Pirate_Run_State::on_enter()
{
    Character_Manager::instance()->get_player2()->set_animation("enemy_pirate_run");
}

void Enemy_Pirate_Run_State::on_update(float delta)
{
    auto player=Character_Manager::instance()->get_player();
    auto enemy=Character_Manager::instance()->get_player2();
    float distance=player->get_position().x()-enemy->get_position().x()+
                     player->getPosition_foot().x()-enemy->getPosition_foot().x();
    if(enemy->get_hp()<0){
        enemy->switch_state("enemy_pirate_dead");
    }else if(abs(distance)>80){
        enemy->set_position(enemy->get_position()+(distance>0?QPointF(4,0):QPointF(-4,0)));
    }else{
        int ran = QRandomGenerator::global()->bounded(100);
        if(ran>=80){
            enemy->switch_state("enemy_pirate_idle");
        }else if(ran>=60){
            enemy->switch_state("enemy_pirate_attack");
        }else if(ran>=40){
            enemy->switch_state("enemy_pirate_skill");
        }else if(ran>=0){
            enemy->switch_state("enemy_pirate_jump");
        }
    }
}

void Enemy_Pirate_Run_State::on_exit()
{}
