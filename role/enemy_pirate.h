#ifndef ENEMY_PIRATE_H
#define ENEMY_PIRATE_H

#include "enemy.h"

class Enemy_pirate : public Enemy
{
    Q_OBJECT
public:
    explicit Enemy_pirate(QObject *parent = nullptr);
    ~Enemy_pirate()=default;

private:
    const float attackDuration=1.1f;
    const float skillDuration=2.7f;

    const int attack_single_damage=8;
    const int skill_single_damage=5;
};

#endif // ENEMY_PIRATE_H
