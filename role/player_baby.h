#ifndef PLAYER_BABY_H
#define PLAYER_BABY_H

#include "player.h"

class Player_Baby : public Player
{
    Q_OBJECT
public:
    explicit Player_Baby(Player_select player_select,QObject *parent = nullptr);
    ~Player_Baby()=default;

private:
    const float CD_skill = 8.00f;
    const float CD_attack = 2.00f;

    const int attack_single_damage=2;
    const int skill_single_damage=3;
};

#endif // PLAYER_BABY_H
