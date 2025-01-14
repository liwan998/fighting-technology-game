#include "character.h"
#include"collision_manager.h"
#include "sound_manager.h"
#include"floating_text_manager.h"
#include"resources_manager.h"
#include<QWidget>
Character::Character(QObject *parent)
    : QObject{parent}
{
    hit_attack_box = Collision_Manager::instance()->create_collision_box();
    hit_skill_box = Collision_Manager::instance()->create_collision_box();
    hurt_box = Collision_Manager::instance()->create_collision_box();

    hit_attack_box->set_enabled(false);
    hit_skill_box->set_enabled(false);

    timer_invulnerable_status.set_wait_time(1.0f);
    timer_invulnerable_status.set_one_shot(true);
    timer_invulnerable_status.set_on_timeout(
        [&]() {
            is_invulnerable = false;
        }
        );

    timer_invulnerable_blink.set_wait_time(0.1f);
    timer_invulnerable_blink.set_one_shot(false);
    timer_invulnerable_blink.set_on_timeout(
        [&]() {
            is_blink_invulnerable = !is_blink_invulnerable;
        }
        );

    timer_hit_frequency.set_wait_time(4.0f);
    timer_hit_frequency.set_one_shot(true);
    timer_hit_frequency.set_on_timeout([&](){
        hit_frequency=0;
    });

    auto sound_manager=Sound_manager::instance();
    jump_effect=sound_manager->find_sound_effect("jump");
    roll_effect=sound_manager->find_sound_effect("roll");
}

Character::~Character()
{
    Collision_Manager::instance()->destroy_collision_box(hit_attack_box);
    Collision_Manager::instance()->destroy_collision_box(hit_skill_box);
    Collision_Manager::instance()->destroy_collision_box(hurt_box);

}

void Character::decrease_hp(float Blood_volume)   //受到伤害
{
    if (is_invulnerable) return;

    Floating_Text_Manager::instance()->createDefaultText(QString::number(Blood_volume),
                                                         position+position_foot+QPoint(0,-90));//创建伤害文字

    hp-=Blood_volume;
    if(hit_frequency==0)    //第一次被攻击时开启重置攻击次数定时器
        timer_hit_frequency.restart();
    if(++hit_frequency>=HIT_FREQUENCY){ //次数达到提前清除攻击次数
        hit_frequency=0;
        if (hp > 0)
            make_invulnerable();
    }

    on_hurt();
}

int Character::get_hp()
{
    return hp;
}

void Character::set_position(const QPointF &position)
{
    this->position=position;
}

const QPointF &Character::get_position() const
{
    return position;
}

void Character::set_velocity(const QPointF &velocity)
{
    this->velocity=velocity;
}

const QPointF &Character::get_velocity() const
{
    return velocity;
}

QPointF Character::get_logic_center() const //获得逻辑中心位置
{
    return QPointF(position.x()+position_foot.x(), position.y()+position_foot.y() - logic_heigth / 2);
}

void Character::set_enable_gravity(bool enable_gravity)
{
    this->enable_gravity=enable_gravity;
}

Collision_box *Character::get_hit_attack_box()
{
    return hit_attack_box;
}

Collision_box *Character::get_hit_skill_box()
{
    return hit_skill_box;
}

Collision_box *Character::get_hurt_box()
{
    return hurt_box;
}

bool Character::is_on_floor() const
{
    return position.y()+position_foot.y()>=FLOOR_Y;
}

float Character::get_floor_y() const
{
    return FLOOR_Y;
}

void Character::make_invulnerable()
{
    is_invulnerable = true;
    timer_invulnerable_status.restart();
}

void Character::key_Press(QKeyEvent &event)
{

}

void Character::key_Release(QKeyEvent &event)
{

}

void Character::on_update(float delta)
{
    state_machine.on_update(delta);
    if (hp <= 0) {
        velocity.setX(0);
    }
    if (enable_gravity) {
        velocity.setY(velocity.y()+GRAVITY * delta);
    }
    position += (velocity * delta);
    if (is_on_floor()) {
        position.setY(FLOOR_Y-position_foot.y());
        velocity.setY(0);
    }
    if (position.x()+position_foot.x() <= 0) position.setX(-position_foot.x());
    if (position.x()+position_foot.x() >= WIDE) position.setX(WIDE-position_foot.x());

    hurt_box->set_position(get_logic_center());

    timer_invulnerable_status.on_update(delta);
    if (is_invulnerable) {
        timer_invulnerable_blink.on_update(delta);
    }
    timer_hit_frequency.on_update(delta);

    timer_attack_hit.on_update(delta);
    timer_skill_hit.on_update(delta);

    if (!current_animation) return;
    Animation& animation = (is_facing_left ? current_animation->left : current_animation->right);
    animation.on_update(delta);
    animation.set_position(position);
}

void Character::on_render(QPainter &painter)
{
    if (!current_animation || (is_invulnerable && is_blink_invulnerable)) return;
    (is_facing_left ? current_animation->left : current_animation->right).on_render(painter);

    (is_facing_left ? current_animation->left : current_animation->right).setIs_box(false);//动画调试框
}

void Character::switch_state(const std::string &id)
{
    state_machine.switch_to(id);
}

void Character::set_animation(const QString &id)
{
    current_animation = &animation_pool[id];
    if(is_facing_left){
        current_animation->left.reset();
    }else{
        current_animation->right.reset();
    }
}

void Character::on_jump()
{
    velocity.setY(velocity.x()-SPEED_JUMP);
    jump_effect->play();
}

void Character::on_roll()
{
    velocity.setX(is_facing_left ? -SPEED_ROLL : SPEED_ROLL);
    roll_effect->play();
}

void Character::on_attack()
{
    attack_effect->play();
}

void Character::on_skill()
{
    skill_effect->play();
}

void Character::on_hurt()
{
}

void Character::on_dead()
{
    dead_effect->play();
}

void Character::load_image_resource(QString player_name)
{
    Animation_Group &animation_attack = animation_pool["attack"];

    Animation &animation_attack_left = animation_attack.left;
    animation_attack_left.set_interval(0.07f);
    animation_attack_left.set_is_loop(false);
    animation_attack_left.add_fram(Resources_manager::instance()->find_atlas(player_name+"_attack_left"));

    Animation &animation_attack_right = animation_attack.right;
    animation_attack_right.set_interval(0.07f);
    animation_attack_right.set_is_loop(false);
    animation_attack_right.add_fram(Resources_manager::instance()->find_atlas(player_name+"_attack_right"));

    Animation_Group &animation_dead = animation_pool["dead"];

    Animation &animation_dead_left = animation_dead.left;
    animation_dead_left.set_interval(0.07f);
    animation_dead_left.set_is_loop(true);
    animation_dead_left.add_fram(Resources_manager::instance()->find_atlas(player_name+"_dead_left"));

    Animation &animation_dead_right = animation_dead.right;
    animation_dead_right.set_interval(0.07f);
    animation_dead_right.set_is_loop(true);
    animation_dead_right.add_fram(Resources_manager::instance()->find_atlas(player_name+"_dead_right"));

    Animation_Group &animation_fall = animation_pool["fall"];

    Animation &animation_fall_left = animation_fall.left;
    animation_fall_left.set_interval(0.1f);
    animation_fall_left.set_is_loop(false);
    animation_fall_left.add_fram(Resources_manager::instance()->find_atlas(player_name+"_fall_left"));

    Animation &animation_fall_right = animation_fall.right;
    animation_fall_right.set_interval(0.1f);
    animation_fall_right.set_is_loop(false);
    animation_fall_right.add_fram(Resources_manager::instance()->find_atlas(player_name+"_fall_right"));

    Animation_Group &animation_idle = animation_pool["idle"];

    Animation &animation_idle_left = animation_idle.left;
    animation_idle_left.set_interval(0.05f);
    animation_idle_left.set_is_loop(true);
    animation_idle_left.add_fram(Resources_manager::instance()->find_atlas(player_name+"_idle_left"));

    Animation &animation_idle_right = animation_idle.right;
    animation_idle_right.set_interval(0.05f);
    animation_idle_right.set_is_loop(true);
    animation_idle_right.add_fram(Resources_manager::instance()->find_atlas(player_name+"_idle_right"));

    Animation_Group &animation_jump = animation_pool["jump"];

    Animation &animation_jump_left = animation_jump.left;
    animation_jump_left.set_interval(0.1f);
    animation_jump_left.set_is_loop(false);
    animation_jump_left.add_fram(Resources_manager::instance()->find_atlas(player_name+"_jump_left"));

    Animation &animation_jump_right = animation_jump.right;
    animation_jump_right.set_interval(0.1f);
    animation_jump_right.set_is_loop(false);
    animation_jump_right.add_fram(Resources_manager::instance()->find_atlas(player_name+"_jump_right"));

    Animation_Group &animation_roll = animation_pool["roll"];

    Animation &animation_roll_left = animation_roll.left;
    animation_roll_left.set_interval(0.07f);
    animation_roll_left.set_is_loop(false);
    animation_roll_left.add_fram(Resources_manager::instance()->find_atlas(player_name+"_roll_left"));

    Animation &animation_roll_right = animation_roll.right;
    animation_roll_right.set_interval(0.07f);
    animation_roll_right.set_is_loop(false);
    animation_roll_right.add_fram(Resources_manager::instance()->find_atlas(player_name+"_roll_right"));

    Animation_Group &animation_run = animation_pool["run"];

    Animation &animation_run_left = animation_run.left;
    animation_run_left.set_interval(0.07f);
    animation_run_left.set_is_loop(true);
    animation_run_left.add_fram(Resources_manager::instance()->find_atlas(player_name+"_run_left"));

    Animation &animation_run_right = animation_run.right;
    animation_run_right.set_interval(0.07f);
    animation_run_right.set_is_loop(true);
    animation_run_right.add_fram(Resources_manager::instance()->find_atlas(player_name+"_run_right"));

    Animation_Group &animation_skill = animation_pool["skill"];

    Animation &animation_skill_left = animation_skill.left;
    animation_skill_left.set_interval(0.07f);
    animation_skill_left.set_is_loop(false);
    animation_skill_left.add_fram(Resources_manager::instance()->find_atlas(player_name+"_skill_left"));

    Animation &animation_skill_right = animation_skill.right;
    animation_skill_right.set_interval(0.07f);
    animation_skill_right.set_is_loop(false);
    animation_skill_right.add_fram(Resources_manager::instance()->find_atlas(player_name+"_skill_right"));
}

void Character::load_collision_box(Player_select player_select)
{
    hit_attack_box->set_layer_src(Collision_layer::None);
    hit_attack_box->set_layer_dst((player_select == Player_select::left) ? Collision_layer::Enemy : Collision_layer::Player);

    hit_skill_box->set_layer_src(Collision_layer::None);
    hit_skill_box->set_layer_dst((player_select == Player_select::left) ? Collision_layer::Enemy : Collision_layer::Player);

    hurt_box->set_layer_src((player_select == Player_select::left) ? Collision_layer::Player : Collision_layer::Enemy);
    hurt_box->set_layer_dst(Collision_layer::None);
}

QPointF Character::getPosition_foot() const
{
    return position_foot;
}

bool Character::getIs_facing_left() const
{
    return is_facing_left;
}

bool Character::getIs_skill() const
{
    return is_skill;
}

void Character::setIs_skill(bool newIs_skill)
{
    is_skill = newIs_skill;
}

bool Character::getIs_roll() const
{
    return is_roll;
}

void Character::setIs_roll(bool newIs_roll)
{
    is_roll = newIs_roll;
}

bool Character::getIs_attack() const
{
    return is_attack;
}

void Character::setIs_attack(bool newIs_attack)
{
    is_attack = newIs_attack;
}
