#ifndef ENEMY_QUEEN_STATE_MACHINE_H
#define ENEMY_QUEEN_STATE_MACHINE_H

#include"State_Node.h"
#include"timer.h"

class Enemy_Queen_Attack_State : public State_Node
{
public:
    Enemy_Queen_Attack_State();
    ~Enemy_Queen_Attack_State() = default;

    void on_enter()override;
    void on_update(float delta)override;
    void on_exit()override;

private:
    Timer timer;

private:
    void update_hit_box_position();
};

class Enemy_Queen_Skill_State : public State_Node
{
public:
    Enemy_Queen_Skill_State();
    ~Enemy_Queen_Skill_State() = default;


    void on_enter()override;
    void on_update(float delta)override;
    void on_exit()override;

private:
    Timer timer;

private:
    void update_hit_box_position();
};

class Enemy_Queen_Dead_State : public State_Node
{
public:
    Enemy_Queen_Dead_State();
    ~Enemy_Queen_Dead_State() = default;

    void on_enter()override;
    void on_update(float delta)override;

};

class Enemy_Queen_Fall_State : public State_Node
{
public:
    Enemy_Queen_Fall_State();
    ~Enemy_Queen_Fall_State() = default;

    void on_enter()override;
    void on_update(float delta)override;

};

class Enemy_Queen_Idle_State : public State_Node
{
public:
    Enemy_Queen_Idle_State();
    ~Enemy_Queen_Idle_State() = default;

    void on_enter()override;
    void on_update(float delta)override;

private:
    Timer timer;
    bool is_idle;

};

class Enemy_Queen_Jump_State : public State_Node
{
public:
    Enemy_Queen_Jump_State();
    ~Enemy_Queen_Jump_State() = default;

    void on_enter()override;
    void on_update(float delta)override;

};

class Enemy_Queen_Run_State : public State_Node
{
public:
    Enemy_Queen_Run_State();
    ~Enemy_Queen_Run_State() = default;

    void on_enter()override;
    void on_update(float delta)override;
    void on_exit()override;
};

#endif // ENEMY_QUEEN_STATE_MACHINE_H
