#include "enemy_queen.h"
#include"resources_manager.h"
#include"character_manager.h"
#include"sound_manager.h"
#include"bullet_manager.h"
#include"enemy_queen_state_machine.h"

Enemy_queen::Enemy_queen(QObject *parent)
    : Character{parent}
{
    position={800,100};
    is_facing_left=true;

    position_foot={295,370};
    logic_heigth=160;

    auto sound_manager=Sound_manager::instance();
    attack_effect=sound_manager->find_sound_effect("queen_attack");
    skill_effect=sound_manager->find_sound_effect("queen_skill");
    dead_effect=sound_manager->find_sound_effect("queen_dead");

    hit_attack_box->set_layer_src(Collision_layer::None);
    hit_attack_box->set_layer_dst(Collision_layer::Player);
    hit_skill_box->set_layer_src(Collision_layer::None);
    hit_skill_box->set_layer_dst(Collision_layer::Player);

    hurt_box->set_layer_src(Collision_layer::Enemy);
    hurt_box->set_layer_dst(Collision_layer::None);

    hit_attack_box->set_size({ 320,160 });
    hit_skill_box->set_size({50,160});
    hurt_box->set_size({ 20,80 });

    timer_attack_hit.set_wait_time(0.378f);//攻击持续时间大约攻击5次左右
    timer_attack_hit.set_one_shot(true);
    timer_attack_hit.set_on_timeout([&](){
        is_attack_hit=true;
    });

    timer_skill_hit.set_wait_time(1.47f);
    timer_skill_hit.set_one_shot(true);
    timer_skill_hit.set_on_timeout([&](){
        is_skill_hit=true;
    });

    hit_attack_box->set_on_collide([&](){
        if(!is_attack_hit)  return;
        is_attack_hit=false;
        timer_attack_hit.restart();
        Character_Manager::instance()->get_player()->decrease_hp(3);
    });
    hit_skill_box->set_on_collide([&](){
        if(!is_skill_hit)   return;
        is_skill_hit=false;
        timer_skill_hit.restart();
        Character_Manager::instance()->get_player()->decrease_hp(5);
    });

    Animation_Group &animation_attack=animation_pool["enemy_queen_attack"];

    Animation& animation_attack_left = animation_attack.left;
    animation_attack_left.set_interval(0.07f);
    animation_attack_left.set_is_loop(false);
    animation_attack_left.add_fram(Resources_manager::instance()->find_atlas("queen_attack_left"));

    Animation& animation_attack_right = animation_attack.right;
    animation_attack_right.set_interval(0.07f);
    animation_attack_right.set_is_loop(false);
    animation_attack_right.add_fram(Resources_manager::instance()->find_atlas("queen_attack_right"));

    Animation_Group &animation_dead=animation_pool["enemy_queen_dead"];

    Animation& animation_dead_left = animation_dead.left;
    animation_dead_left.set_interval(0.07f);
    animation_dead_left.set_is_loop(true);
    animation_dead_left.add_fram(Resources_manager::instance()->find_atlas("queen_dead_left"));

    Animation& animation_dead_right = animation_dead.right;
    animation_dead_right.set_interval(0.07f);
    animation_dead_right.set_is_loop(true);
    animation_dead_right.add_fram(Resources_manager::instance()->find_atlas("queen_dead_right"));

    Animation_Group &animation_fall=animation_pool["enemy_queen_fall"];

    Animation& animation_fall_left = animation_fall.left;
    animation_fall_left.set_interval(0.1f);
    animation_fall_left.set_is_loop(false);
    animation_fall_left.add_fram(Resources_manager::instance()->find_atlas("queen_fall_left"));

    Animation& animation_fall_right = animation_fall.right;
    animation_fall_right.set_interval(0.1f);
    animation_fall_right.set_is_loop(false);
    animation_fall_right.add_fram(Resources_manager::instance()->find_atlas("queen_fall_right"));

    Animation_Group &animation_idle=animation_pool["enemy_queen_idle"];

    Animation& animation_idle_left = animation_idle.left;
    animation_idle_left.set_interval(0.05f);
    animation_idle_left.set_is_loop(true);
    animation_idle_left.add_fram(Resources_manager::instance()->find_atlas("queen_idle_left"));

    Animation& animation_idle_right = animation_idle.right;
    animation_idle_right.set_interval(0.05f);
    animation_idle_right.set_is_loop(true);
    animation_idle_right.add_fram(Resources_manager::instance()->find_atlas("queen_idle_right"));

    Animation_Group &animation_jump=animation_pool["enemy_queen_jump"];

    Animation& animation_jump_left = animation_jump.left;
    animation_jump_left.set_interval(0.1f);
    animation_jump_left.set_is_loop(false);
    animation_jump_left.add_fram(Resources_manager::instance()->find_atlas("queen_jump_left"));

    Animation& animation_jump_right = animation_jump.right;
    animation_jump_right.set_interval(0.1f);
    animation_jump_right.set_is_loop(false);
    animation_jump_right.add_fram(Resources_manager::instance()->find_atlas("queen_jump_right"));

    Animation_Group &animation_roll=animation_pool["enemy_queen_roll"];

    Animation& animation_roll_left = animation_roll.left;
    animation_roll_left.set_interval(0.07f);
    animation_roll_left.set_is_loop(false);
    animation_roll_left.add_fram(Resources_manager::instance()->find_atlas("queen_roll_left"));

    Animation& animation_roll_right = animation_roll.right;
    animation_roll_right.set_interval(0.07f);
    animation_roll_right.set_is_loop(false);
    animation_roll_right.add_fram(Resources_manager::instance()->find_atlas("queen_roll_right"));

    Animation_Group &animation_run=animation_pool["enemy_queen_run"];

    Animation& animation_run_left = animation_run.left;
    animation_run_left.set_interval(0.07f);
    animation_run_left.set_is_loop(true);
    animation_run_left.add_fram(Resources_manager::instance()->find_atlas("queen_run_left"));

    Animation& animation_run_right = animation_run.right;
    animation_run_right.set_interval(0.07f);
    animation_run_right.set_is_loop(true);
    animation_run_right.add_fram(Resources_manager::instance()->find_atlas("queen_run_right"));

    Animation_Group &animation_skill=animation_pool["enemy_queen_skill"];

    Animation& animation_skill_left = animation_skill.left;
    animation_skill_left.set_interval(0.07f);
    animation_skill_left.set_is_loop(false);
    animation_skill_left.add_fram(Resources_manager::instance()->find_atlas("queen_skill_left"));

    Animation& animation_skill_right = animation_skill.right;
    animation_skill_right.set_interval(0.07f);
    animation_skill_right.set_is_loop(false);
    animation_skill_right.add_fram(Resources_manager::instance()->find_atlas("queen_skill_right"));

    //状态机初始化
    state_machine.register_state("enemy_queen_attack",	new Enemy_Queen_Attack_State());
    state_machine.register_state("enemy_queen_skill",    new Enemy_Queen_Skill_State());
    state_machine.register_state("enemy_queen_dead",     new Enemy_Queen_Dead_State());
    state_machine.register_state("enemy_queen_fall",     new Enemy_Queen_Fall_State());
    state_machine.register_state("enemy_queen_idle",     new Enemy_Queen_Idle_State());
    state_machine.register_state("enemy_queen_jump",     new Enemy_Queen_Jump_State());
    state_machine.register_state("enemy_queen_run",		new Enemy_Queen_Run_State());
    state_machine.set_entry("enemy_queen_idle");

}

Enemy_queen::~Enemy_queen()
{}

void Enemy_queen::on_update(float delta)
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

void Enemy_queen::on_render(QPainter &painter)
{
    Character::on_render(painter);
}

void Enemy_queen::on_attack()
{
    Character::on_attack();
    attack_effect->play();
}

void Enemy_queen::on_skill()
{
    Bullet_Manager::instance()->create_bullet(Bullet_Manager::Bullet_kind::queen_big,is_facing_left,
                                              get_logic_center()-QPointF(0,20),Player::Player_select::right);
    Bullet_Manager::instance()->create_bullet(Bullet_Manager::Bullet_kind::queen_small,is_facing_left,
                                              get_logic_center(),Player::Player_select::right);

    Character::on_skill();
    skill_effect->play();
}

void Enemy_queen::on_dead()
{
    Character::on_dead();
    dead_effect->play();
}