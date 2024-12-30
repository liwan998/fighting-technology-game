#ifndef PLAYER_FALL_STATE_H
#define PLAYER_FALL_STATE_H

#include "State_Node.h"
#include"player.h"

class Player_Fall_State : public State_Node
{
    Q_OBJECT
public:
    explicit Player_Fall_State(Player::Player_select player_select,QObject *parent = nullptr);
    ~Player_Fall_State()=default;

    // State_Node interface
public:
    virtual void on_enter() override;
    virtual void on_update(float delta) override;
    virtual void on_exit() override;

protected:
    Player::Player_select player_select=Player::Player_select::left;
};

#endif // PLAYER_FALL_STATE_H
