#ifndef PLAYER_QUEEN_H
#define PLAYER_QUEEN_H

#include "player.h"

class Player_queen : public Player
{
    Q_OBJECT
public:
    explicit Player_queen(Player_select player_select, QObject *parent = nullptr);
    ~Player_queen()=default;

    void on_skill() override;

private:
    const float CD_skill = 7.00f;
    const float CD_attack = 2.00f;

    const int attack_single_damage=3;
    const int skill_single_damage=3;
};

#endif // PLAYER_QUEEN_H
