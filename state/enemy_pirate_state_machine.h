#ifndef ENEMY_PIRATE_STATE_MACHINE_H
#define ENEMY_PIRATE_STATE_MACHINE_H

#include"State_Node.h"
#include"timer.h"

class Enemy_Pirate_Attack_State : public State_Node
{
public:
    Enemy_Pirate_Attack_State();
    ~Enemy_Pirate_Attack_State() = default;

    void on_enter()override;
    void on_update(float delta)override;
    void on_exit()override;

private:
    Timer timer;

private:
    void update_hit_box_position();
};

class Enemy_Pirate_Skill_State : public State_Node
{
public:
    Enemy_Pirate_Skill_State();
    ~Enemy_Pirate_Skill_State() = default;


    void on_enter()override;
    void on_update(float delta)override;
    void on_exit()override;

private:
    Timer timer;

private:
    void update_hit_box_position();
};

class Enemy_Pirate_Dead_State : public State_Node
{
public:
    Enemy_Pirate_Dead_State();
    ~Enemy_Pirate_Dead_State() = default;

    void on_enter()override;
    void on_update(float delta)override;

};

class Enemy_Pirate_Fall_State : public State_Node
{
public:
    Enemy_Pirate_Fall_State();
    ~Enemy_Pirate_Fall_State() = default;

    void on_enter()override;
    void on_update(float delta)override;

};

class Enemy_Pirate_Idle_State : public State_Node
{
public:
    Enemy_Pirate_Idle_State();
    ~Enemy_Pirate_Idle_State() = default;

    void on_enter()override;
    void on_update(float delta)override;

private:
    Timer timer;
    bool is_idle;

};

class Enemy_Pirate_Jump_State : public State_Node
{
public:
    Enemy_Pirate_Jump_State();
    ~Enemy_Pirate_Jump_State() = default;

    void on_enter()override;
    void on_update(float delta)override;

};

class Enemy_Pirate_Run_State : public State_Node
{
public:
    Enemy_Pirate_Run_State();
    ~Enemy_Pirate_Run_State() = default;

    void on_enter()override;
    void on_update(float delta)override;
    void on_exit()override;
};


#endif // ENEMY_PIRATE_STATE_MACHINE_H
