#ifndef BULLET_QUEEN_BIG_H
#define BULLET_QUEEN_BIG_H

#include "bullet.h"

class Bullet_queen_big : public Bullet
{
public:
    explicit Bullet_queen_big(QObject *parent = nullptr);
    ~Bullet_queen_big();

    void on_enter(Player::Player_select player_select)override;
    void on_update(float delta)override;
    void on_render(QPainter &painter)override;
private:
    Animation effects;
};

#endif // BULLET_QUEEN_BIG_H
