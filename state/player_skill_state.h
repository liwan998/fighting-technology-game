#ifndef PLAYER_SKILL_STATE_H
#define PLAYER_SKILL_STATE_H

#include "State_Node.h"
#include"timer.h"
#include"player.h"

class Player_Skill_State : public State_Node
{
    Q_OBJECT
public:
    explicit Player_Skill_State(Player::Player_select player_select,QObject *parent = nullptr);
    ~Player_Skill_State()=default;

    // State_Node interface
public:
    virtual void on_enter() override;
    virtual void on_update(float delta) override;
    virtual void on_exit() override;

protected:
    void update_hit_box_position();

protected:
    Timer timer;
    Player::Player_select player_select=Player::Player_select::left;
};

#endif // PLAYER_SKILL_STATE_H
