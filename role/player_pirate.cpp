#include "player_pirate.h"

Player_pirate::Player_pirate(Player_select player_select, QObject *parent)
    : Player{parent}
{
    this->player_selects = player_select;

    position = (player_select == Player_select::left) ? QPointF{0, 400} : QPointF{1000, 400};
    is_facing_left = (player_select == Player_select::right);

    position_foot = {195, 150};
    logic_heigth = 130;

    load_effect("pirate",true);
    load_collision_box(player_select);

    hit_attack_box->set_size({200, 150});
    hit_skill_box->set_size({200, 150});
    hurt_box->set_size({20, 80});

    load_hit_interval(attackDuration+0.5,skillDuration/5);
    load_hit_box(player_selects,attack_single_damage,skill_single_damage);
    load_hit_CD(CD_attack,CD_skill);
    load_image_resource("pirate");
    load_state_node(player_selects,attackDuration,skillDuration);
}
