#include "enemy_skill_state.h"
#include"character_manager.h"

Enemy_Skill_State::Enemy_Skill_State(QObject *parent)
    : State_Node{parent}
{
    timer.set_one_shot(true);
    timer.set_on_timeout(
        [&]() {
            auto* enemy =Character_Manager::instance()->get_player2();
            enemy->setIs_skill(false);
        }
        );
}

void Enemy_Skill_State::on_enter()
{
    Character_Manager::instance()->get_player2()->set_animation("skill");
    auto* enemy = Character_Manager::instance()->get_player2();
    enemy->get_hit_skill_box()->set_enabled(true);
    enemy->setIs_skill(true);
    update_hit_box_position();
    enemy->on_skill();
    timer.restart();
}

void Enemy_Skill_State::on_update(float delta)
{
    timer.on_update(delta);
    update_hit_box_position();
}

void Enemy_Skill_State::on_exit()
{
    auto enemy = Character_Manager::instance()->get_player2();
    enemy->setIs_skill(false);
    enemy->get_hit_skill_box()->set_enabled(false);
}

void Enemy_Skill_State::update_hit_box_position()
{
    auto* enemy = Character_Manager::instance()->get_player2();
    QPointF pos_center = enemy->get_logic_center();
    Collision_box* hit_box = enemy->get_hit_skill_box();
    const QPointF& size_hit_box = hit_box->get_size();
    QPointF pos_hit_box;
    if(enemy->getIs_facing_left()){
        pos_hit_box = { pos_center.x() - size_hit_box.x() / 2,pos_center.y() };
    }else{
        pos_hit_box = { pos_center.x() + size_hit_box.x() / 2,pos_center.y() };
    }
    hit_box->set_position(pos_hit_box);
}
