#ifndef ENEMY_DEAD_STATE_H
#define ENEMY_DEAD_STATE_H

#include "State_Node.h"

class Enemy_Dead_State : public State_Node
{
    Q_OBJECT
public:
    explicit Enemy_Dead_State(QObject *parent = nullptr);
    ~Enemy_Dead_State()=default;

    // State_Node interface
public:
    virtual void on_enter() override;
    virtual void on_update(float delta) override;
    virtual void on_exit() override;
};

#endif // ENEMY_DEAD_STATE_H
