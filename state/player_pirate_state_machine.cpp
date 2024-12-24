#include "player_pirate_state_machine.h"
#include"player.h"
#include"character_manager.h"

Player_Pirate_Attack_State::Player_Pirate_Attack_State()
{
    timer.set_wait_time(1.1f);
    timer.set_one_shot(true);
    timer.set_on_timeout(
        [&]() {
            Player* player = (Player*)Character_Manager::instance()->get_player();
            player->setIs_attack(false);
        }
        );
}

void Player_Pirate_Attack_State::on_enter()
{
    Character_Manager::instance()->get_player()->set_animation("player_pirate_attack");
    Player* player = (Player*)Character_Manager::instance()->get_player();
    player->get_hit_attack_box()->set_enabled(true);
    player->setIs_attack(true);
    player->setIs_key_control(false);
    update_hit_box_position();
    player->on_attack();
    timer.restart();
}

void Player_Pirate_Attack_State::on_update(float delta)
{
    timer.on_update(delta);
    update_hit_box_position();

    Player* player = (Player*)Character_Manager::instance()->get_player();
    if (player->get_hp() <= 0) {
        player->switch_state("player_pirate_dead");
    }else if (!player->getIs_attack()) {
        if (player->get_velocity().y() > 0)
            player->switch_state("player_pirate_fall");
        else if (player->get_move_axis() == 0)
            player->switch_state("player_pirate_idle");
        else if (player->is_on_floor() && player->get_move_axis() != 0)
            player->switch_state("player_pirate_run");
    }
}

void Player_Pirate_Attack_State::on_exit()
{
    Player* player = (Player*)Character_Manager::instance()->get_player();
    player->setIs_attack(false);
    player->get_hit_attack_box()->set_enabled(false);
    player->setIs_key_control(true);
}

void Player_Pirate_Attack_State::update_hit_box_position()
{
    Player* player = (Player*)Character_Manager::instance()->get_player();
    QPointF pos_center = player->get_logic_center();
    Collision_box* hit_box = player->get_hit_attack_box();
    const QPointF& size_hit_box = hit_box->get_size();
    QPointF pos_hit_box;
    if(player->getIs_facing_left()){
        pos_hit_box = { pos_center.x() - size_hit_box.x() / 2,pos_center.y() };
    }else{
        pos_hit_box = { pos_center.x() + size_hit_box.x() / 2,pos_center.y() };
    }
    hit_box->set_position(pos_hit_box);
}


Player_Pirate_Skill_State::Player_Pirate_Skill_State()
{
    timer.set_wait_time(2.70f);
    timer.set_one_shot(true);
    timer.set_on_timeout(
        [&]() {
            Player* player = (Player*)Character_Manager::instance()->get_player();
            player->setIs_skill(false);
        }
        );
}

void Player_Pirate_Skill_State::on_enter()
{
    Character_Manager::instance()->get_player()->set_animation("player_pirate_skill");
    Player* player = (Player*)Character_Manager::instance()->get_player();
    player->get_hit_skill_box()->set_enabled(true);
    player->setIs_skill(true);
    player->setIs_key_control(false);
    update_hit_box_position();
    player->on_skill();
    timer.restart();
}

void Player_Pirate_Skill_State::on_update(float delta)
{
    timer.on_update(delta);
    update_hit_box_position();

    Player* player = (Player*)Character_Manager::instance()->get_player();
    if (player->get_hp() <= 0) {
        player->switch_state("player_pirate_dead");
    }
    else if (!player->getIs_skill()) {
        if (player->get_velocity().y() > 0){
            player->switch_state("player_pirate_fall");
        }else if (player->get_move_axis() == 0){
            player->switch_state("player_pirate_idle");
        }
    }
}

void Player_Pirate_Skill_State::on_exit()
{
    Player* player = (Player*)Character_Manager::instance()->get_player();
    player->setIs_skill(false);
    player->get_hit_skill_box()->set_enabled(false);
    player->setIs_key_control(true);
}

void Player_Pirate_Skill_State::update_hit_box_position()
{
    Player* player = (Player*)Character_Manager::instance()->get_player();
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

Player_Pirate_Dead_State::Player_Pirate_Dead_State()
{
}

void Player_Pirate_Dead_State::on_enter()
{
    Character_Manager::instance()->get_player()->set_animation("player_pirate_dead");
    Character_Manager::instance()->get_player()->on_dead();
}

void Player_Pirate_Dead_State::on_update(float delta)
{
}

Player_Pirate_Fall_State::Player_Pirate_Fall_State()
{

}

void Player_Pirate_Fall_State::on_enter()
{
    Character_Manager::instance()->get_player()->set_animation("player_pirate_fall");
}

void Player_Pirate_Fall_State::on_update(float delta)
{
    Player* player = (Player*)Character_Manager::instance()->get_player();
    if (player->get_hp() <= 0) {
        player->switch_state("player_pirate_dead");
    }
    else if (player->is_on_floor()) {
        player->switch_state("player_pirate_idle");
    }
    else if (player->can_attack()) {
        player->switch_state("player_pirate_attack");
    }else if(player->can_skill()){
        player->switch_state("player_pirate_skill");
    }
}

Player_Pirate_Idle_State::Player_Pirate_Idle_State()
{

}

void Player_Pirate_Idle_State::on_enter()
{
    Character_Manager::instance()->get_player()->set_animation("player_pirate_idle");
}

void Player_Pirate_Idle_State::on_update(float delta)
{
    Player* player = (Player*)Character_Manager::instance()->get_player();
    if (player->get_hp() <= 0) {
        player->switch_state("player_pirate_dead");
    }else if (player->can_attack()) {
        player->switch_state("player_pirate_attack");
    }else if(player->can_skill()){
        player->switch_state("player_pirate_skill");
    }else if (player->get_velocity().y() > 0) {
        player->switch_state("player_pirate_fall");
    }else if (player->can_jump()) {
        player->switch_state("player_pirate_jump");
    }else if (player->can_roll()) {
        player->switch_state("player_pirate_roll");
    }else if (player->is_on_floor() && player->get_move_axis() != 0) {
        player->switch_state("player_pirate_run");
    }
}

Player_Pirate_Jump_State::Player_Pirate_Jump_State()
{

}

void Player_Pirate_Jump_State::on_enter()
{
    Character_Manager::instance()->get_player()->set_animation("player_pirate_jump");
    Player* player = (Player*)Character_Manager::instance()->get_player();
    player->on_jump();
}

void Player_Pirate_Jump_State::on_update(float delta)
{
    Player* player = (Player*)Character_Manager::instance()->get_player();
    if (player->get_hp() <= 0) {
        player->switch_state("player_pirate_dead");
    }
    else if (player->is_on_floor()) {
        player->switch_state("player_pirate_idle");
    }
    else if (player->can_attack()) {
        player->switch_state("player_pirate_attack");
    }else if(player->can_skill()){
        player->switch_state("player_pirate_skill");
    }
}

Player_Pirate_Roll_State::Player_Pirate_Roll_State()
{
    timer.set_wait_time(0.5f);
    timer.set_one_shot(true);
    timer.set_on_timeout(
        [&]() {
            Player* player = (Player*)Character_Manager::instance()->get_player();
            player->setIs_roll(false);
        }
    );
}

void Player_Pirate_Roll_State::on_enter()
{
    Character_Manager::instance()->get_player()->set_animation("player_pirate_roll");
    Player* player = (Player*)Character_Manager::instance()->get_player();
    player->get_hurt_box()->set_enabled(false);
    player->setIs_roll(true);
    player->on_roll();
    timer.restart();
}

void Player_Pirate_Roll_State::on_update(float delta)
{
    timer.on_update(delta);
    Player* player = (Player*)Character_Manager::instance()->get_player();
    if (!player->getIs_roll()) {
        if (player->get_move_axis() != 0) {
            player->switch_state("player_pirate_run");
        }
        else if (player->can_jump()) {
            player->switch_state("player_pirate_jump");
        }
        else {
            player->switch_state("player_pirate_idle");
        }
    }
}

void Player_Pirate_Roll_State::on_exit()
{
    Character_Manager::instance()->get_player()->get_hurt_box()->set_enabled(true);
}

Player_Pirate_Run_State::Player_Pirate_Run_State()
{

}

void Player_Pirate_Run_State::on_enter()
{
    Character_Manager::instance()->get_player()->set_animation("player_pirate_run");
}

void Player_Pirate_Run_State::on_update(float delta)
{
    Player* player = (Player*)Character_Manager::instance()->get_player();
    if (player->get_hp() <= 0) {
        player->switch_state("player_pirate_dead");
    }
    else if (player->get_move_axis() == 0) {
        player->switch_state("player_pirate_idle");
    }
    else if(player->can_jump()) {
        player->switch_state("player_pirate_jump");
    }
    else if (player->can_attack()) {
        player->switch_state("player_pirate_attack");
    }else if(player->can_skill()){
        player->switch_state("player_pirate_skill");
    }else if (player->can_roll()) {
        player->switch_state("player_pirate_roll");
    }
}

void Player_Pirate_Run_State::on_exit(){}