#include "player_baby.h"
#include "character_manager.h"
#include "sound_manager.h"
#include"baby_player_state_machine.h"

Player_Baby::Player_Baby(Player_select player_select,QObject *parent)
    : Player{parent}
{
    this->player_selects = player_select;

    position = (player_select == Player_select::left) ? QPointF{0, 400} : QPointF{1000, 400};
    is_facing_left = (player_select == Player_select::right);

    position_foot = {156, 239};
    logic_heigth = 142;

    auto sound_manager = Sound_manager::instance();
    attack_effect = sound_manager->find_sound_effect("pirate_attack");
    skill_effect = sound_manager->find_sound_effect("pirate_skill");
    dead_effect = sound_manager->find_sound_effect("pirate_dead");

    load_collision_box(player_select);

    hit_attack_box->set_size({20, 20});
    hit_skill_box->set_size({20, 20});
    hurt_box->set_size({20, 80});

    timer_attack_hit.set_wait_time(1.6f);
    timer_attack_hit.set_one_shot(true);
    timer_attack_hit.set_on_timeout([&]() {
        is_attack_hit = true;
    });

    timer_skill_hit.set_wait_time(4.0f);
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

    load_image_resource("baby");

    // 状态机初始化
    state_machine.register_state("attack", new Baby_Player_Attack_State(player_select));
    state_machine.register_state("skill", new Baby_Player_Skill_State(player_select));
    state_machine.register_state("dead", new Baby_Player_Dead_State(player_select));
    state_machine.register_state("fall", new Baby_Player_Fall_State(player_select));
    state_machine.register_state("idle", new Baby_Player_Idle_State(player_select));
    state_machine.register_state("jump", new Baby_Player_Jump_State(player_select));
    state_machine.register_state("roll", new Baby_Player_Roll_State(player_select));
    state_machine.register_state("run", new Baby_Player_Run_State(player_select));
    state_machine.set_entry("idle");
}
