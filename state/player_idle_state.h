#ifndef PLAYER_IDLE_STATE_H
#define PLAYER_IDLE_STATE_H

#include "State_Node.h"
#include"player.h"

class Player_Idle_State : public State_Node
{
    Q_OBJECT
public:
    explicit Player_Idle_State(Player::Player_select player_select,QObject *parent = nullptr);
    ~Player_Idle_State()=default;

    // State_Node interface
public:
    virtual void on_enter() override;
    virtual void on_update(float delta) override;
    virtual void on_exit() override;

protected:
    Player::Player_select player_select=Player::Player_select::left;
};

#endif // PLAYER_IDLE_STATE_H
