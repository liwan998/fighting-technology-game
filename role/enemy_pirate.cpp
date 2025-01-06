#include "enemy_pirate.h"
#include"character_manager.h"
#include"sound_manager.h"
#include"pirate_enemy_state_machine.h"

Enemy_pirate::Enemy_pirate(QObject *parent)
    : Character{parent}
{
    position={1000,400};
    is_facing_left=true;

    position_foot={195,150};
    logic_heigth=130;

    auto sound_manager=Sound_manager::instance();
    attack_effect=sound_manager->find_sound_effect("pirate_attack");
    skill_effect=sound_manager->find_sound_effect("pirate_skill");
    dead_effect=sound_manager->find_sound_effect("pirate_dead");

    load_collision_box(Player_select::right);

    hit_attack_box->set_size({ 200,150 });
    hit_skill_box->set_size({200,150});
    hurt_box->set_size({ 20,80 });

    timer_attack_hit.set_wait_time(1.47f);
    timer_attack_hit.set_one_shot(true);
    timer_attack_hit.set_on_timeout([&](){
        is_attack_hit=true;
    });

    timer_skill_hit.set_wait_time(0.56f);   //技能持续时间大约攻击5次左右
    timer_skill_hit.set_one_shot(true);
    timer_skill_hit.set_on_timeout([&](){
        is_skill_hit=true;
    });

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

    load_image_resource("pirate");

    //状态机初始化
    state_machine.register_state("attack",	new Pirate_Enemy_Attack_State());
    state_machine.register_state("skill",    new Pirate_Enemy_Skill_State());
    state_machine.register_state("dead",     new Pirate_Enemy_Dead_State());
    state_machine.register_state("fall",     new Pirate_Enemy_Fall_State());
    state_machine.register_state("idle",     new Pirate_Enemy_Idle_State());
    state_machine.register_state("jump",     new Pirate_Enemy_Jump_State());
    state_machine.register_state("run",		new Pirate_Enemy_Run_State());
    state_machine.set_entry("idle");
}

Enemy_pirate::~Enemy_pirate()
{}

void Enemy_pirate::on_update(float delta)
{
    auto player=Character_Manager::instance()->get_player();
    if(player->get_position().x()+player->getPosition_foot().x()>position.x()+position_foot.x()){
        is_facing_left=false;
    }else{
        is_facing_left=true;
    }
    Character::on_update(delta);
}
