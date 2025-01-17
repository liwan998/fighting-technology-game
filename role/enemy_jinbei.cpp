#include "enemy_jinbei.h"

Enemy_Jinbei::Enemy_Jinbei(QObject *parent)
    : Enemy{parent}
{
    position=QPointF{800, 100};
    is_facing_left=true;

    position_foot = {365, 450};
    logic_heigth = 160;

    load_effect("Jinbei",true);
    load_collision_box(Player_select::right);

    hit_attack_box->set_size({130, 100});
    hit_skill_box->set_size({200, 150});
    hurt_box->set_size({70, 80});

    load_hit_interval(attackDuration+0.5,skillDuration/6);
    load_hit_box(attack_single_damage,skill_single_damage);
    load_image_resource("Jinbei");
    load_state_node(attackDuration,skillDuration);
}
