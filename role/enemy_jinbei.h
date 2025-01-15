#ifndef ENEMY_JINBEI_H
#define ENEMY_JINBEI_H

#include "enemy.h"

class Enemy_Jinbei : public Enemy
{
    Q_OBJECT
public:
    explicit Enemy_Jinbei(QObject *parent = nullptr);
    ~Enemy_Jinbei()=default;

private:
    const float attackDuration=1.12f;
    const float skillDuration=3.0f;

    const int attack_single_damage=12;
    const int skill_single_damage=6;
};

#endif // ENEMY_JINBEI_H
