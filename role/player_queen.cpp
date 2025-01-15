#include "player_queen.h"
#include "queen_player_state_machine.h"
#include "bullet_manager.h"

Player_queen::Player_queen(Player_select player_select, QObject *parent)
    : Player{parent}
{
    this->player_selects = player_select; // 保存 player_select

    position = (player_select == Player_select::left) ? QPointF{0, 100} : QPointF{800, 100};
    is_facing_left = (player_select == Player_select::right);

    position_foot = {295, 370};
    logic_heigth = 160;

    load_effect("queen",false);
    load_collision_box(player_select);

    hit_attack_box->set_size({320, 160});
    hit_skill_box->set_size({20, 20});
    hurt_box->set_size({20, 80});

    load_hit_interval(attackDuration/5,skillDuration+0.5);
    load_hit_box(player_selects,attack_single_damage,skill_single_damage);
    load_hit_CD(CD_attack,CD_skill);
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
}
