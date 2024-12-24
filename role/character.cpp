#include "character.h"
#include"collision_manager.h"
#include "sound_manager.h"

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

    timer_hit_number.set_wait_time(0.7f);
    timer_hit_number.set_one_shot(true);
    timer_hit_number.set_on_timeout([&](){
        hit_number=0;
    });

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

    hit_number=Blood_volume;
    timer_hit_number.restart();
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
    timer_hit_number.on_update(delta);
    timer_hit_frequency.on_update(delta);

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

    if(hit_number!=0){
        QPen pen;
        pen.setWidth(4);
        pen.setColor(QColor(Qt::red));
        painter.setPen(pen);

        QFont font = painter.font();
        font.setPointSize(24); // 设置字体大小为24点
        painter.setFont(font);

        painter.drawText(position+position_foot+QPoint({0,-150}),"-"+QString::number(hit_number));
    }
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

}

void Character::on_skill()
{

}

void Character::on_hurt()
{
}

void Character::on_dead()
{

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
