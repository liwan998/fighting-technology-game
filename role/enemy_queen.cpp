#include "enemy_queen.h"
#include"character_manager.h"
#include"sound_manager.h"
#include"bullet_manager.h"
#include"queen_enemy_state_machine.h"

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

    load_collision_box(Player_select::right);

    hit_attack_box->set_size({ 320,160 });
    hit_skill_box->set_size({20,20});
    hurt_box->set_size({ 20,80 });

    timer_attack_hit.set_wait_time(0.38f);//攻击持续时间大约攻击5次左右
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
        Character_Manager::instance()->get_player()->decrease_hp(attack_single_damage);
    });
    hit_skill_box->set_on_collide([&](){
        if(!is_skill_hit)   return;
        is_skill_hit=false;
        timer_skill_hit.restart();
        Character_Manager::instance()->get_player()->decrease_hp(skill_single_damage);
    });

    load_image_resource("queen");

    //状态机初始化
    state_machine.register_state("attack",	new Queen_Enemy_Attack_State());
    state_machine.register_state("skill",    new Queen_Enemy_Skill_State());
    state_machine.register_state("dead",     new Queen_Enemy_Dead_State());
    state_machine.register_state("fall",     new Queen_Enemy_Fall_State());
    state_machine.register_state("idle",     new Queen_Enemy_Idle_State());
    state_machine.register_state("jump",     new Queen_Enemy_Jump_State());
    state_machine.register_state("run",		new Queen_Enemy_Run_State());
    state_machine.set_entry("idle");

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
    Character::on_update(delta);
}

void Enemy_queen::on_skill()
{
    Bullet_Manager::instance()->create_bullet(Bullet_Manager::Bullet_kind::queen_big,is_facing_left,
                                              get_logic_center()-QPointF(0,20),Player::Player_select::right);
    Bullet_Manager::instance()->create_bullet(Bullet_Manager::Bullet_kind::queen_small,is_facing_left,
                                              get_logic_center(),Player::Player_select::right);

    Character::on_skill();
}
