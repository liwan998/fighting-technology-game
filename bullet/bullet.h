#ifndef BULLET_H
#define BULLET_H

#include <QObject>
#include<QPointF>
#include<QImage>
#include"animation.h"
#include"collision_box.h"
#include"player.h"

class Bullet : public QObject
{
    Q_OBJECT
public:
    explicit Bullet(QObject *parent = nullptr);
    ~Bullet();
    virtual void on_enter(Player::Player_select player_select);
    virtual void on_update(float delta);
    virtual void on_render(QPainter &painter);
    QPointF getPosition() const;
    void setPosition(QPointF newPosition);

    QPointF getVelocity() const;
    void setVelocity(QPointF newVelocity);

    bool getValid() const;

    bool getBullet_collision() const;
    void setBullet_collision(bool newBullet_collision);

    QPointF get_logic_center();

protected:
    const int WIDE=1450;  //界面宽消失极限
    const int HIGHT=720;  //界面高消失极限

protected:
    QPointF position;                       //子弹位置
    QPointF position_offset={0,0};          //子弹位置偏移
    QPointF velocity;                       //子弹速度
    int damage;                             //子弹伤害
    bool valid=true;                        //子弹是否有效
    bool bullet_collision=false;            //子弹是否发生碰撞
    Player::Player_select impactTarget;     //撞击目标
    Collision_box* bullet_box=nullptr;      //子弹碰撞箱
    QImage *bullet_img=nullptr;             //子弹没有碰到敌人时图片
    Animation bullet_animation;             //子弹碰到敌人后怕播放动画
    QPointF animation_offset={0,0};         //动画位置偏移
};

#endif // BULLET_H
