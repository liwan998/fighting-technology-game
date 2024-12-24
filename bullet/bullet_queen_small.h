#ifndef BULLET_QUEEN_SMALL_H
#define BULLET_QUEEN_SMALL_H

#include "bullet.h"

class Bullet_queen_small : public Bullet
{
    Q_OBJECT
public:
    explicit Bullet_queen_small(QObject *parent = nullptr);
    ~Bullet_queen_small();

    void on_update(float delta)override;
    void on_enter(Player::Player_select player_select)override;

private:
    float transform=0;
};

#endif // BULLET_QUEEN_SMALL_H
