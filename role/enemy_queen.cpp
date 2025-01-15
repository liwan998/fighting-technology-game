#include "enemy_queen.h"
#include"bullet_manager.h"
#include"queen_enemy_state_machine.h"

Enemy_queen::Enemy_queen(QObject *parent)
    : Enemy{parent}
{
    position={800,100};
    is_facing_left=true;

    position_foot={295,370};
    logic_heigth=160;

    load_effect("queen",false);
    load_collision_box(Player_select::right);

    hit_attack_box->set_size({ 320,160 });
    hit_skill_box->set_size({20,20});
    hurt_box->set_size({ 20,80 });

    load_hit_interval(attackDuration/5,skillDuration+1);
    load_hit_box(attack_single_damage,skill_single_damage);
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

void Enemy_queen::on_skill()
{
    Bullet_Manager::instance()->create_bullet(Bullet_Manager::Bullet_kind::queen_big,is_facing_left,
                                              get_logic_center()-QPointF(0,20),Player::Player_select::right);
    Bullet_Manager::instance()->create_bullet(Bullet_Manager::Bullet_kind::queen_small,is_facing_left,
                                              get_logic_center(),Player::Player_select::right);

    Character::on_skill();
}
