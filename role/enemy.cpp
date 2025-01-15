#include "enemy.h"
#include"character_manager.h"
#include"enemy_state_machine.h"

Enemy::Enemy(QObject *parent)
    : Character{parent}
{}

void Enemy::on_update(float delta)
{
    auto player=Character_Manager::instance()->get_player();
    if(player->get_position().x()+player->getPosition_foot().x()>position.x()+position_foot.x()){
        is_facing_left=false;
    }else{
        is_facing_left=true;
    }
    Character::on_update(delta);
}

void Enemy::load_state_node(const float attackWaitTime, const float skillWaitTime)
{
    // 状态机初始化
    auto enemyAttackState=new Ordinary_Enemy_Attack_State();
    enemyAttackState->setTimerWaitTime(attackWaitTime);
    auto enemySkillState=new Ordinary_Enemy_Skill_State();
    enemySkillState->setTimerWaitTime(skillWaitTime);

    state_machine.register_state("attack", enemyAttackState);
    state_machine.register_state("skill", enemySkillState);
    state_machine.register_state("dead", new Ordinary_Enemy_Dead_State());
    state_machine.register_state("fall", new Ordinary_Enemy_Fall_State());
    state_machine.register_state("idle", new Ordinary_Enemy_Idle_State());
    state_machine.register_state("jump", new Ordinary_Enemy_Jump_State());
    state_machine.register_state("run", new Ordinary_Enemy_Run_State());
    state_machine.set_entry("idle");
}

void Enemy::load_hit_box(const int &attack_single_damage, const int &skill_single_damage)
{
    hit_attack_box->set_on_collide([&](){
        if(!is_attack_hit)  return;
        is_attack_hit=false;
        timer_attack_hit.restart();
        Character_Manager::instance()->get_player()->decrease_hp(attack_single_damage);
    });
    hit_skill_box->set_on_collide([&](){
        if(!is_skill_hit)   return;
        is_skill_hit=false;
        timer_skill_hit.restart();
        Character_Manager::instance()->get_player()->decrease_hp(skill_single_damage);
    });
}
