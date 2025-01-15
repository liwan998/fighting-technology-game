#ifndef ENEMY_QUEEN_H
#define ENEMY_QUEEN_H

#include "enemy.h"

class Enemy_queen : public Enemy
{
    Q_OBJECT
public:
    explicit Enemy_queen(QObject *parent = nullptr);
    ~Enemy_queen()=default;

    void on_skill()override;

private:
    const float attackDuration=1.9f;
    const float skillDuration=1.6f;

    const int attack_single_damage=3;
    const int skill_single_damage=5;
};

#endif // ENEMY_QUEEN_H
