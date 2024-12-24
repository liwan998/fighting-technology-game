#ifndef ENEMY_QUEEN_H
#define ENEMY_QUEEN_H

#include "character.h"

class Enemy_queen : public Character
{
public:
    explicit Enemy_queen(QObject *parent = nullptr);
    ~Enemy_queen();

    void on_update(float delta)override;
    void on_render(QPainter &painter)override;

    void on_attack()override;
    void on_skill()override;
    void on_dead()override;

private:
    Timer timer_attack_hit;//多少时间可以让敌人被普通攻击一次
    bool is_attack_hit=false;
    Timer timer_skill_hit;//多少时间可以让敌人被技能攻击一次
    bool is_skill_hit=false;
};

#endif // ENEMY_QUEEN_H
