#include "bullet.h"
#include"collision_manager.h"

Bullet::Bullet(QObject *parent)
    : QObject{parent}
{
    bullet_box=Collision_Manager::instance()->create_collision_box();
    bullet_animation.set_interval(0.07f);
    bullet_animation.set_is_loop(false);
    bullet_animation.set_on_finished([&](){
        valid=false;
    });
}

Bullet::~Bullet()
{
    Collision_Manager::instance()->destroy_collision_box(bullet_box);
}

void Bullet::on_enter(Player::Player_select player_select)
{
    if(player_select==Player::Player_select::right){
        bullet_box->set_layer_src(Collision_layer::None);
        bullet_box->set_layer_dst(Collision_layer::Player);
        impactTarget=Player::Player_select::left;
    }else{
        bullet_box->set_layer_src(Collision_layer::None);
        bullet_box->set_layer_dst(Collision_layer::Enemy);
        impactTarget=Player::Player_select::right;
    }

}

void Bullet::on_update(float delta)
{
    if(!valid)  return;
    position+=velocity;
    if(bullet_collision){
        bullet_animation.on_update(delta);
        bullet_animation.set_position(position+position_offset+animation_offset);
    }

    bullet_box->set_position(get_logic_center());
    if(position.x()<100||position.x()>WIDE||position.y()<-200||position.y()>HIGHT){
        valid=false;
    }
}

void Bullet::on_render(QPainter &painter)
{
    if(bullet_collision){
        bullet_animation.on_render(painter);
    }else{
        painter.drawImage(position+position_offset+animation_offset,*bullet_img);
    }
}

QPointF Bullet::getPosition() const
{
    return position+position_offset;
}

void Bullet::setPosition(QPointF newPosition)
{
    position = newPosition;
}

QPointF Bullet::getVelocity() const
{
    return velocity;
}

void Bullet::setVelocity(QPointF newVelocity)
{
    velocity = newVelocity;
}

bool Bullet::getValid() const
{
    return valid;
}

bool Bullet::getBullet_collision() const
{
    return bullet_collision;
}

void Bullet::setBullet_collision(bool newBullet_collision)
{
    bullet_collision = newBullet_collision;
}

QPointF Bullet::get_logic_center()
{
    return QPointF(position+position_offset + bullet_box->get_size() / 2);
}
