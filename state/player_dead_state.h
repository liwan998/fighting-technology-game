#ifndef PLAYER_DEAD_STATE_H
#define PLAYER_DEAD_STATE_H

#include "State_Node.h"
#include"player.h"

class Player_Dead_State : public State_Node
{
    Q_OBJECT
public:
    explicit Player_Dead_State(Player::Player_select player_select,QObject *parent = nullptr);
    ~Player_Dead_State()=default;

    // State_Node interface
public:
    virtual void on_enter() override;
    virtual void on_update(float delta) override;
    virtual void on_exit() override;

protected:
    Player::Player_select player_select=Player::Player_select::left;
};

#endif // PLAYER_DEAD_STATE_H
