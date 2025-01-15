#ifndef ENEMY_BABY_H
#define ENEMY_BABY_H

#include "enemy.h"

class Enemy_Baby : public Enemy
{
    Q_OBJECT
public:
    explicit Enemy_Baby(QObject *parent = nullptr);
    ~Enemy_Baby()=default;

public:
    virtual void on_attack() override;
    virtual void on_skill() override;
    virtual void on_update(float delta)override;

private:
    int random_position_x();//随机x位置

private:
    const float attackDuration=1.6f;
    const float skillDuration=4.0f;

    const int attack_single_damage=2;
    const int skill_single_damage=3;

    Timer timer_call_interval;
};

#endif // ENEMY_BABY_H
