#include "player_jinbei.h"
#include "character_manager.h"
#include "sound_manager.h"

Player_Jinbei::Player_Jinbei(Player_select player_select, QObject *parent)
    : Player{parent}
{
    this->player_selects = player_select;

    position = (player_select == Player_select::left) ? QPointF{0, 100} : QPointF{800, 100};
    is_facing_left = (player_select == Player_select::right);

    position_foot = {365, 450};
    logic_heigth = 160;

    auto sound_manager = Sound_manager::instance();
    attack_effect = sound_manager->find_sound_effect("pirate_attack");
    skill_effect = sound_manager->find_sound_effect("pirate_skill");
    dead_effect = sound_manager->find_sound_effect("pirate_dead");

    load_collision_box(player_select);

    hit_attack_box->set_size({130, 100});
    hit_skill_box->set_size({200, 150});
    hurt_box->set_size({70, 80});

    timer_attack_hit.set_wait_time(attackDuration+1);
    timer_attack_hit.set_one_shot(true);
    timer_attack_hit.set_on_timeout([&]() {
        is_attack_hit = true;
    });

    timer_skill_hit.set_wait_time(skillDuration/6);
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

    load_image_resource("Jinbei");
    load_state_node(player_select,attackDuration,skillDuration);
}
