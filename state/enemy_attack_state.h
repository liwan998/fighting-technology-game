#ifndef ENEMY_ATTACK_STATE_H
#define ENEMY_ATTACK_STATE_H

#include "State_Node.h"
#include"timer.h"

class Enemy_Attack_State : public State_Node
{
    Q_OBJECT
public:
    explicit Enemy_Attack_State(QObject *parent = nullptr);
    ~Enemy_Attack_State()=default;

    // State_Node interface
public:
    virtual void on_enter() override;
    virtual void on_update(float delta) override;
    virtual void on_exit() override;

protected:
    virtual void update_hit_box_position();

protected:
    Timer timer;
};

#endif // ENEMY_ATTACK_STATE_H
