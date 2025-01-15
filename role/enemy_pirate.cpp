#include "enemy_pirate.h"

Enemy_pirate::Enemy_pirate(QObject *parent)
    : Enemy{parent}
{
    position={1000,400};
    is_facing_left=true;

    position_foot={195,150};
    logic_heigth=130;

    load_effect("pirate",true);
    load_collision_box(Player_select::right);

    hit_attack_box->set_size({ 200,150 });
    hit_skill_box->set_size({200,150});
    hurt_box->set_size({ 20,80 });

    load_hit_interval(attackDuration+1,skillDuration/5);
    load_hit_box(attack_single_damage,skill_single_damage);
    load_image_resource("pirate");
    load_state_node(attackDuration,skillDuration);
}
