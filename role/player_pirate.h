#ifndef PLAYER_PIRATE_H
#define PLAYER_PIRATE_H

#include "player.h"

class Player_pirate : public Player
{
    Q_OBJECT
public:
    explicit Player_pirate(QObject *parent = nullptr);
    ~Player_pirate();
    void on_update(float delta)override;

    void on_attack()override;
    void on_skill()override;
    void on_dead()override;

private:
    const float CD_skill=5.00f;
    //const float CD_ultimate=20.00f;
    const float CD_attack=1.00f;

    Timer timer_attack_hit;//多少时间可以让敌人被普通攻击一次
    bool is_attack_hit=false;
    Timer timer_skill_hit;//多少时间可以让敌人被技能攻击一次
    bool is_skill_hit=false;
};

#endif // PLAYER_PIRATE_H
