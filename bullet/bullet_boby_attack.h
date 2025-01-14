#ifndef BULLET_BOBY_ATTACK_H
#define BULLET_BOBY_ATTACK_H

#include "bullet.h"

class Bullet_Boby_attack : public Bullet
{
    Q_OBJECT
public:
    explicit Bullet_Boby_attack(bool is_left,QObject *parent = nullptr);
    ~Bullet_Boby_attack()=default;

    void on_enter(Player::Player_select player_select)override;
};

#endif // BULLET_BOBY_ATTACK_H
