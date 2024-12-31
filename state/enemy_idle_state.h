#ifndef ENEMY_IDLE_STATE_H
#define ENEMY_IDLE_STATE_H

#include "State_Node.h"
#include"timer.h"
class Enemy_Idle_State : public State_Node
{
    Q_OBJECT
public:
    explicit Enemy_Idle_State(QObject *parent = nullptr);
    ~Enemy_Idle_State()=default;

    // State_Node interface
public:
    virtual void on_enter() override;
    virtual void on_update(float delta) override;
    virtual void on_exit() override;

protected:
    Timer timer;
    bool is_idle;
};

#endif // ENEMY_IDLE_STATE_H
