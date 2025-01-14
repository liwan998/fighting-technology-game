#ifndef BULLET_BOBY_SKILL_H
#define BULLET_BOBY_SKILL_H

#include "bullet.h"

class Bullet_Boby_skill : public Bullet
{
    Q_OBJECT
public:
    explicit Bullet_Boby_skill(QObject *parent = nullptr);
    ~Bullet_Boby_skill()=default;

    void on_enter(Player::Player_select player_select)override;
private:
    QPoint off;
};

#endif // BULLET_BOBY_SKILL_H
