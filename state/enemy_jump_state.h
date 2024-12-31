#ifndef ENEMY_JUMP_STATE_H
#define ENEMY_JUMP_STATE_H

#include "State_Node.h"

class Enemy_Jump_State : public State_Node
{
    Q_OBJECT
public:
    explicit Enemy_Jump_State(QObject *parent = nullptr);

    // State_Node interface
public:
    virtual void on_enter() override;
    virtual void on_update(float delta) override;
    virtual void on_exit() override;
};

#endif // ENEMY_JUMP_STATE_H
