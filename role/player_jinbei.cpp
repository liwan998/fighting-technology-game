#include "player_jinbei.h"

Player_Jinbei::Player_Jinbei(Player_select player_select, QObject *parent)
    : Player{parent}
{
    this->player_selects = player_select;

    position = (player_select == Player_select::left) ? QPointF{0, 100} : QPointF{800, 100};
    is_facing_left = (player_select == Player_select::right);

    position_foot = {365, 450};
    logic_heigth = 160;

    load_effect("Jinbei",true);
    load_collision_box(player_select);

    hit_attack_box->set_size({130, 100});
    hit_skill_box->set_size({200, 150});
    hurt_box->set_size({70, 80});

    load_hit_interval(attackDuration+0.5,skillDuration/6);
    load_hit_box(player_selects,attack_single_damage,skill_single_damage);
    load_hit_CD(CD_attack,CD_skill);
    load_image_resource("Jinbei");
    load_state_node(player_selects,attackDuration,skillDuration);
}
