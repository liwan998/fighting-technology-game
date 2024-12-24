#include "enemy_pirate.h"
#include"resources_manager.h"
#include"character_manager.h"
#include"sound_manager.h"
#include"enemy_pirate_state_machine.h"

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

    hit_attack_box->set_layer_src(Collision_layer::None);
    hit_attack_box->set_layer_dst(Collision_layer::Player);
    hit_skill_box->set_layer_src(Collision_layer::None);
    hit_skill_box->set_layer_dst(Collision_layer::Player);

    hurt_box->set_layer_src(Collision_layer::Enemy);
    hurt_box->set_layer_dst(Collision_layer::None);

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
        Character_Manager::instance()->get_player()->decrease_hp(8);
    });
    hit_skill_box->set_on_collide([&](){
        if(!is_skill_hit)   return;
        is_skill_hit=false;
        timer_skill_hit.restart();
        Character_Manager::instance()->get_player()->decrease_hp(5);
    });

    Animation_Group &animation_attack=animation_pool["enemy_pirate_attack"];

    Animation& animation_attack_left = animation_attack.left;
    animation_attack_left.set_interval(0.07f);
    animation_attack_left.set_is_loop(false);
    animation_attack_left.add_fram(Resources_manager::instance()->find_atlas("pirate_attack_left"));

    Animation& animation_attack_right = animation_attack.right;
    animation_attack_right.set_interval(0.07f);
    animation_attack_right.set_is_loop(false);
    animation_attack_right.add_fram(Resources_manager::instance()->find_atlas("pirate_attack_right"));

    Animation_Group &animation_dead=animation_pool["enemy_pirate_dead"];

    Animation& animation_dead_left = animation_dead.left;
    animation_dead_left.set_interval(0.07f);
    animation_dead_left.set_is_loop(true);
    animation_dead_left.add_fram(Resources_manager::instance()->find_atlas("pirate_dead_left"));

    Animation& animation_dead_right = animation_dead.right;
    animation_dead_right.set_interval(0.07f);
    animation_dead_right.set_is_loop(true);
    animation_dead_right.add_fram(Resources_manager::instance()->find_atlas("pirate_dead_right"));

    Animation_Group &animation_fall=animation_pool["enemy_pirate_fall"];

    Animation& animation_fall_left = animation_fall.left;
    animation_fall_left.set_interval(0.1f);
    animation_fall_left.set_is_loop(false);
    animation_fall_left.add_fram(Resources_manager::instance()->find_atlas("pirate_fall_left"));

    Animation& animation_fall_right = animation_fall.right;
    animation_fall_right.set_interval(0.1f);
    animation_fall_right.set_is_loop(false);
    animation_fall_right.add_fram(Resources_manager::instance()->find_atlas("pirate_fall_right"));

    Animation_Group &animation_idle=animation_pool["enemy_pirate_idle"];

    Animation& animation_idle_left = animation_idle.left;
    animation_idle_left.set_interval(0.05f);
    animation_idle_left.set_is_loop(true);
    animation_idle_left.add_fram(Resources_manager::instance()->find_atlas("pirate_idle_left"));

    Animation& animation_idle_right = animation_idle.right;
    animation_idle_right.set_interval(0.05f);
    animation_idle_right.set_is_loop(true);
    animation_idle_right.add_fram(Resources_manager::instance()->find_atlas("pirate_idle_right"));

    Animation_Group &animation_jump=animation_pool["enemy_pirate_jump"];

    Animation& animation_jump_left = animation_jump.left;
    animation_jump_left.set_interval(0.1f);
    animation_jump_left.set_is_loop(false);
    animation_jump_left.add_fram(Resources_manager::instance()->find_atlas("pirate_jump_left"));

    Animation& animation_jump_right = animation_jump.right;
    animation_jump_right.set_interval(0.1f);
    animation_jump_right.set_is_loop(false);
    animation_jump_right.add_fram(Resources_manager::instance()->find_atlas("pirate_jump_right"));

    Animation_Group &animation_run=animation_pool["enemy_pirate_run"];

    Animation& animation_run_left = animation_run.left;
    animation_run_left.set_interval(0.07f);
    animation_run_left.set_is_loop(true);
    animation_run_left.add_fram(Resources_manager::instance()->find_atlas("pirate_run_left"));

    Animation& animation_run_right = animation_run.right;
    animation_run_right.set_interval(0.07f);
    animation_run_right.set_is_loop(true);
    animation_run_right.add_fram(Resources_manager::instance()->find_atlas("pirate_run_right"));

    Animation_Group &animation_skill=animation_pool["enemy_pirate_skill"];

    Animation& animation_skill_left = animation_skill.left;
    animation_skill_left.set_interval(0.07f);
    animation_skill_left.set_is_loop(false);
    animation_skill_left.add_fram(Resources_manager::instance()->find_atlas("pirate_skill_left"));

    Animation& animation_skill_right = animation_skill.right;
    animation_skill_right.set_interval(0.07f);
    animation_skill_right.set_is_loop(false);
    animation_skill_right.add_fram(Resources_manager::instance()->find_atlas("pirate_skill_right"));

    //状态机初始化
    state_machine.register_state("enemy_pirate_attack",	new Enemy_Pirate_Attack_State());
    state_machine.register_state("enemy_pirate_skill",    new Enemy_Pirate_Skill_State());
    state_machine.register_state("enemy_pirate_dead",     new Enemy_Pirate_Dead_State());
    state_machine.register_state("enemy_pirate_fall",     new Enemy_Pirate_Fall_State());
    state_machine.register_state("enemy_pirate_idle",     new Enemy_Pirate_Idle_State());
    state_machine.register_state("enemy_pirate_jump",     new Enemy_Pirate_Jump_State());
    state_machine.register_state("enemy_pirate_run",		new Enemy_Pirate_Run_State());
    state_machine.set_entry("enemy_pirate_idle");
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
    timer_attack_hit.on_update(delta);
    timer_skill_hit.on_update(delta);
    Character::on_update(delta);
}

void Enemy_pirate::on_render(QPainter &painter)
{
    Character::on_render(painter);
}

void Enemy_pirate::on_attack()
{
    Character::on_attack();
    attack_effect->play();
}

void Enemy_pirate::on_skill()
{
    Character::on_skill();
    skill_effect->play();
}

void Enemy_pirate::on_dead()
{
    Character::on_dead();
    dead_effect->play();
}
