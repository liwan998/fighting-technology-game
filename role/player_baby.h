#ifndef PLAYER_BABY_H
#define PLAYER_BABY_H

#include "player.h"

class Player_Baby : public Player
{
    Q_OBJECT
public:
    explicit Player_Baby(Player_select player_select,QObject *parent = nullptr);
    ~Player_Baby()=default;

public:
    virtual void on_attack() override;
    virtual void on_skill() override;
    virtual void on_update(float delta)override;

private:
    int random_position_x();//随机x位置

private:
    const float CD_skill = 8.00f;
    const float CD_attack = 2.00f;

    const int attack_single_damage=2;
    const int skill_single_damage=3;

    Timer timer_call_interval;
};

#endif // PLAYER_BABY_H
