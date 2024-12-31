#ifndef ENEMY_FALL_STATE_H
#define ENEMY_FALL_STATE_H

#include "State_Node.h"

class Enemy_Fall_State : public State_Node
{
    Q_OBJECT
public:
    explicit Enemy_Fall_State(QObject *parent = nullptr);
    ~Enemy_Fall_State()=default;

    // State_Node interface
public:
    virtual void on_enter() override;
    virtual void on_update(float delta) override;
    virtual void on_exit() override;
};

#endif // ENEMY_FALL_STATE_H
