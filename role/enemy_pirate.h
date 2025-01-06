#ifndef ENEMY_PIRATE_H
#define ENEMY_PIRATE_H

#include "character.h"

class Enemy_pirate : public Character
{
    Q_OBJECT
public:
    explicit Enemy_pirate(QObject *parent = nullptr);
    ~Enemy_pirate();

    void on_update(float delta)override;

private:
    const int attack_single_damage=8;
    const int skill_single_damage=5;
};

#endif // ENEMY_PIRATE_H
