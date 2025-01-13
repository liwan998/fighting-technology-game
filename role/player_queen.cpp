#include "player_queen.h"
#include "character_manager.h"
#include "queen_player_state_machine.h"
#include "bullet_manager.h"
#include "sound_manager.h"
#include <QDebug>

Player_queen::Player_queen(Player_select player_select, QObject *parent)
    : Player{parent}
{
    this->player_selects = player_select; // 保存 player_select

    position = (player_select == Player_select::left) ? QPointF{0, 100} : QPointF{800, 100};
    is_facing_left = (player_select == Player_select::right);

    position_foot = {295, 370};
    logic_heigth = 160;

    auto sound_manager = Sound_manager::instance();
    attack_effect = sound_manager->find_sound_effect("queen_attack");
    skill_effect = sound_manager->find_sound_effect("queen_skill");
    dead_effect = sound_manager->find_sound_effect("queen_dead");

    load_collision_box(player_select);

    hit_attack_box->set_size({320, 160});
    hit_skill_box->set_size({20, 20});
    hurt_box->set_size({20, 80});

    timer_attack_hit.set_wait_time(0.38f); // 攻击持续时间大约攻击5次左右
    timer_attack_hit.set_one_shot(true);
    timer_attack_hit.set_on_timeout([&]() {
        is_attack_hit = true;
    });

    timer_skill_hit.set_wait_time(1.47f);
    timer_skill_hit.set_one_shot(true);
    timer_skill_hit.set_on_timeout([&]() {
        is_skill_hit = true;
    });

    hit_attack_box->set_on_collide([&]() {
        if (!is_attack_hit) return;
        is_attack_hit = false;
        timer_attack_hit.restart();
        if (player_selects == Player::Player_select::left) {
            Character_Manager::instance()->get_player2()->decrease_hp(attack_single_damage);
        } else {
            Character_Manager::instance()->get_player()->decrease_hp(attack_single_damage);
        }
    });

    hit_skill_box->set_on_collide([&]() {
        if (!is_skill_hit) return;
        is_skill_hit = false;
        timer_skill_hit.restart();
        if (player_selects == Player::Player_select::left) {
            Character_Manager::instance()->get_player2()->decrease_hp(skill_single_damage);
        } else {
            Character_Manager::instance()->get_player()->decrease_hp(skill_single_damage);
        }
    });

    timer_attack.set_wait_time(CD_attack);
    timer_attack.set_one_shot(true);
    timer_attack.set_on_timeout([&]() {
        is_attack_cd = false;
    });

    timer_skill.set_wait_time(CD_skill);
    timer_skill.set_one_shot(true);
    timer_skill.set_on_timeout([&]() {
        is_skill_cd = false;
    });

    load_image_resource("queen");

    // 状态机初始化
    state_machine.register_state("attack", new Queen_Player_Attack_State(player_select));
    state_machine.register_state("skill", new Queen_Player_Skill_State(player_select));
    state_machine.register_state("dead", new Queen_Player_Dead_State(player_select));
    state_machine.register_state("fall", new Queen_Player_Fall_State(player_select));
    state_machine.register_state("idle", new Queen_Player_Idle_State(player_select));
    state_machine.register_state("jump", new Queen_Player_Jump_State(player_select));
    state_machine.register_state("roll", new Queen_Player_Roll_State(player_select));
    state_machine.register_state("run", new Queen_Player_Run_State(player_select));
    state_machine.set_entry("idle");
}

void Player_queen::on_skill()
{
    Bullet_Manager::instance()->create_bullet(Bullet_Manager::Bullet_kind::queen_big, is_facing_left,
                                              get_logic_center() - QPointF(0, 20), player_selects);
    Bullet_Manager::instance()->create_bullet(Bullet_Manager::Bullet_kind::queen_small, is_facing_left,
                                              get_logic_center(), player_selects);

    Player::on_skill();
    skill_effect->play();
}
