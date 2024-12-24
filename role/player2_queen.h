#ifndef PLAYER2_QUEEN_H
#define PLAYER2_QUEEN_H

#include "player.h"

class Player2_queen : public Player
{
    Q_OBJECT
public:
    explicit Player2_queen(QObject *parent = nullptr);
    ~Player2_queen();
    void on_update(float delta)override;

    void on_attack()override;
    void on_skill()override;
    void on_dead()override;

private:
    const float CD_skill=7.00f;
    //const float CD_ultimate=20.00f;
    const float CD_attack=2.00f;

    Timer timer_attack_hit;//多少时间可以让敌人被普通攻击一次
    bool is_attack_hit=false;
    Timer timer_skill_hit;//多少时间可以让敌人被技能攻击一次
    bool is_skill_hit=false;

};

#endif // PLAYER2_QUEEN_H
