#include "player2_queen_state_machine.h"
#include"player.h"
#include"character_manager.h"

Player2_Queen_Attack_State::Player2_Queen_Attack_State()
{
    timer.set_wait_time(1.89f);
    timer.set_one_shot(true);
    timer.set_on_timeout(
        [&]() {
            Player* player = (Player*)Character_Manager::instance()->get_player2();
            player->setIs_attack(false);
        }
        );
}

void Player2_Queen_Attack_State::on_enter()
{
    Character_Manager::instance()->get_player2()->set_animation("player2_queen_attack");
    Player* player = (Player*)Character_Manager::instance()->get_player2();
    player->get_hit_attack_box()->set_enabled(true);
    player->setIs_attack(true);
    player->setIs_key_control(false);
    update_hit_box_position();
    player->on_attack();
    timer.restart();
}

void Player2_Queen_Attack_State::on_update(float delta)
{
    timer.on_update(delta);
    update_hit_box_position();

    Player* player = (Player*)Character_Manager::instance()->get_player2();
    if (player->get_hp() <= 0) {
        player->switch_state("player2_queen_dead");
    }else if (!player->getIs_attack()) {
        if (player->get_velocity().y() > 0)
            player->switch_state("player2_queen_fall");
        else if (player->get_move_axis() == 0)
            player->switch_state("player2_queen_idle");
        else if (player->is_on_floor() && player->get_move_axis() != 0)
            player->switch_state("player2_queen_run");
    }
}

void Player2_Queen_Attack_State::on_exit()
{
    Player* player = (Player*)Character_Manager::instance()->get_player2();
    player->setIs_attack(false);
    player->get_hit_attack_box()->set_enabled(false);
    player->setIs_key_control(true);
}

void Player2_Queen_Attack_State::update_hit_box_position()
{
    Player* player = (Player*)Character_Manager::instance()->get_player2();
    QPointF pos_center = player->get_logic_center();
    player->get_hit_attack_box()->set_position(pos_center);
}

Player2_Queen_Skill_State::Player2_Queen_Skill_State()
{
    timer.set_wait_time(1.54f);
    timer.set_one_shot(true);
    timer.set_on_timeout(
        [&]() {
            Player* player = (Player*)Character_Manager::instance()->get_player2();
            player->setIs_skill(false);
        }
        );
}

void Player2_Queen_Skill_State::on_enter()
{
    Character_Manager::instance()->get_player2()->set_animation("player2_queen_skill");
    Player* player = (Player*)Character_Manager::instance()->get_player2();
    player->get_hit_skill_box()->set_enabled(true);
    player->setIs_skill(true);
    player->setIs_key_control(false);
    update_hit_box_position();
    player->on_skill();
    timer.restart();
}

void Player2_Queen_Skill_State::on_update(float delta)
{
    timer.on_update(delta);
    update_hit_box_position();

    Player* player = (Player*)Character_Manager::instance()->get_player2();
    if (player->get_hp() <= 0) {
        player->switch_state("player2_queen_dead");
    }
    else if (!player->getIs_skill()) {
        if (player->get_velocity().y() > 0){
            player->switch_state("player2_queen_fall");
        }else if (player->get_move_axis() == 0){
            player->switch_state("player2_queen_idle");
        }
    }
}

void Player2_Queen_Skill_State::on_exit()
{
    Player* player = (Player*)Character_Manager::instance()->get_player2();
    player->setIs_skill(false);
    player->get_hit_skill_box()->set_enabled(false);
    player->setIs_key_control(true);
}

void Player2_Queen_Skill_State::update_hit_box_position()
{
    Player* player = (Player*)Character_Manager::instance()->get_player2();
    QPointF pos_center = player->get_logic_center();
    Collision_box* hit_box = player->get_hit_skill_box();
    const QPointF& size_hit_box = hit_box->get_size();
    QPointF pos_hit_box;
    if(player->getIs_facing_left()){
        pos_hit_box = { pos_center.x() - size_hit_box.x() / 2,pos_center.y() };
    }else{
        pos_hit_box = { pos_center.x() + size_hit_box.x() / 2,pos_center.y() };
    }
    hit_box->set_position(pos_hit_box);
}

Player2_Queen_Dead_State::Player2_Queen_Dead_State()
{
}

void Player2_Queen_Dead_State::on_enter()
{
    Character_Manager::instance()->get_player2()->set_animation("player2_queen_dead");
    Character_Manager::instance()->get_player2()->on_dead();
}

void Player2_Queen_Dead_State::on_update(float delta)
{
}

Player2_Queen_Fall_State::Player2_Queen_Fall_State()
{

}

void Player2_Queen_Fall_State::on_enter()
{
    Character_Manager::instance()->get_player2()->set_animation("player2_queen_fall");
}

void Player2_Queen_Fall_State::on_update(float delta)
{
    Player* player = (Player*)Character_Manager::instance()->get_player2();
    if (player->get_hp() <= 0) {
        player->switch_state("player2_queen_dead");
    }
    else if (player->is_on_floor()) {
        player->switch_state("player2_queen_idle");
    }
    else if (player->can_attack()) {
        player->switch_state("player2_queen_attack");
    }else if(player->can_skill()){
        player->switch_state("player2_queen_skill");
    }
}

Player2_Queen_Idle_State::Player2_Queen_Idle_State()
{

}

void Player2_Queen_Idle_State::on_enter()
{
    Character_Manager::instance()->get_player2()->set_animation("player2_queen_idle");
}

void Player2_Queen_Idle_State::on_update(float delta)
{
    Player* player = (Player*)Character_Manager::instance()->get_player2();
    if (player->get_hp() <= 0) {
        player->switch_state("player2_queen_dead");
    }else if (player->can_attack()) {
        player->switch_state("player2_queen_attack");
    }else if(player->can_skill()){
        player->switch_state("player2_queen_skill");
    }else if (player->get_velocity().y() > 0) {
        player->switch_state("player2_queen_fall");
    }else if (player->can_jump()) {
        player->switch_state("player2_queen_jump");
    }else if (player->can_roll()) {
        player->switch_state("player2_queen_roll");
    }else if (player->is_on_floor() && player->get_move_axis() != 0) {
        player->switch_state("player2_queen_run");
    }
}

Player2_Queen_Jump_State::Player2_Queen_Jump_State()
{

}

void Player2_Queen_Jump_State::on_enter()
{
    Character_Manager::instance()->get_player2()->set_animation("player2_queen_jump");
    Player* player = (Player*)Character_Manager::instance()->get_player2();
    player->on_jump();
}

void Player2_Queen_Jump_State::on_update(float delta)
{
    Player* player = (Player*)Character_Manager::instance()->get_player2();
    if (player->get_hp() <= 0) {
        player->switch_state("player2_queen_dead");
    }
    else if (player->is_on_floor()) {
        player->switch_state("player2_queen_idle");
    }
    else if (player->can_attack()) {
        player->switch_state("player2_queen_attack");
    }else if(player->can_skill()){
        player->switch_state("player2_queen_skill");
    }
}

Player2_Queen_Roll_State::Player2_Queen_Roll_State()
{
    timer.set_wait_time(0.5f);
    timer.set_one_shot(true);
    timer.set_on_timeout(
        [&]() {
            Player* player = (Player*)Character_Manager::instance()->get_player2();
            player->setIs_roll(false);
        }
        );
}

void Player2_Queen_Roll_State::on_enter()
{
    Character_Manager::instance()->get_player2()->set_animation("player2_queen_roll");
    Player* player = (Player*)Character_Manager::instance()->get_player2();
    player->get_hurt_box()->set_enabled(false);
    player->setIs_roll(true);
    player->on_roll();
    timer.restart();
}

void Player2_Queen_Roll_State::on_update(float delta)
{
    timer.on_update(delta);
    Player* player = (Player*)Character_Manager::instance()->get_player2();
    if (!player->getIs_roll()) {
        if (player->get_move_axis() != 0) {
            player->switch_state("player2_queen_run");
        }
        else if (player->can_jump()) {
            player->switch_state("player2_queen_jump");
        }
        else {
            player->switch_state("player2_queen_idle");
        }
    }
}

void Player2_Queen_Roll_State::on_exit()
{
    Character_Manager::instance()->get_player2()->get_hurt_box()->set_enabled(true);
}

Player2_Queen_Run_State::Player2_Queen_Run_State()
{

}

void Player2_Queen_Run_State::on_enter()
{
    Character_Manager::instance()->get_player2()->set_animation("player2_queen_run");
}

void Player2_Queen_Run_State::on_update(float delta)
{
    Player* player = (Player*)Character_Manager::instance()->get_player2();
    if (player->get_hp() <= 0) {
        player->switch_state("player2_queen_dead");
    }
    else if (player->get_move_axis() == 0) {
        player->switch_state("player2_queen_idle");
    }
    else if(player->can_jump()) {
        player->switch_state("player2_queen_jump");
    }
    else if (player->can_attack()) {
        player->switch_state("player2_queen_attack");
    }else if(player->can_skill()){
        player->switch_state("player2_queen_skill");
    }else if (player->can_roll()) {
        player->switch_state("player2_queen_roll");
    }
}

void Player2_Queen_Run_State::on_exit(){}
