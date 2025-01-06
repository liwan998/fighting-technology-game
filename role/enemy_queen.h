#ifndef ENEMY_QUEEN_H
#define ENEMY_QUEEN_H

#include "character.h"

class Enemy_queen : public Character
{
public:
    explicit Enemy_queen(QObject *parent = nullptr);
    ~Enemy_queen();

    void on_update(float delta)override;
    void on_skill()override;

private:
    const int attack_single_damage=3;
    const int skill_single_damage=5;
};

#endif // ENEMY_QUEEN_H
