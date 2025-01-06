#ifndef PLAYER_PIRATE_H
#define PLAYER_PIRATE_H

#include "player.h"

class Player_pirate : public Player
{
    Q_OBJECT
public:
    explicit Player_pirate(Player_select player_select, QObject *parent = nullptr);
    ~Player_pirate()=default;

private:
    const float CD_skill = 5.00f;
    const float CD_attack = 1.00f;

    const int attack_single_damage=8;
    const int skill_single_damage=5;
};

#endif // PLAYER_PIRATE_H
