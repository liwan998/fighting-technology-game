#ifndef PLAYER_JINBEI_H
#define PLAYER_JINBEI_H

#include "player.h"

class Player_Jinbei : public Player
{
    Q_OBJECT
public:
    explicit Player_Jinbei(Player_select player_select,QObject *parent = nullptr);
    ~Player_Jinbei()=default;

private:
    const float CD_skill = 8.00f;
    const float CD_attack = 2.00f;

    const float attackDuration=1.12f;
    const float skillDuration=3.0f;

    const int attack_single_damage=12;
    const int skill_single_damage=6;
};

#endif // PLAYER_JINBEI_H
