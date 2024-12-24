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

#endif // ENEMY_PIRATE_H
