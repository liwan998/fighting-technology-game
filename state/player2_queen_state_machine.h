#ifndef PLAYER2_QUEEN_STATE_MACHINE_H
#define PLAYER2_QUEEN_STATE_MACHINE_H
#include"State_Node.h"
#include"timer.h"

class Player2_Queen_Attack_State : public State_Node
{
public:
    Player2_Queen_Attack_State();
    ~Player2_Queen_Attack_State() = default;

    void on_enter()override;
    void on_update(float delta)override;
    void on_exit()override;

private:
    Timer timer;

private:
    void update_hit_box_position();
};

class Player2_Queen_Skill_State : public State_Node
{
public:
    Player2_Queen_Skill_State();
    ~Player2_Queen_Skill_State() = default;

    void on_enter()override;
    void on_update(float delta)override;
    void on_exit()override;

private:
    Timer timer;

private:
    void update_hit_box_position();
};

class Player2_Queen_Dead_State : public State_Node
{
public:
    Player2_Queen_Dead_State();
    ~Player2_Queen_Dead_State() = default;

    void on_enter()override;
    void on_update(float delta)override;


};

class Player2_Queen_Fall_State : public State_Node
{
public:
    Player2_Queen_Fall_State();
    ~Player2_Queen_Fall_State() = default;

    void on_enter()override;
    void on_update(float delta)override;

};

class Player2_Queen_Idle_State : public State_Node
{
public:
    Player2_Queen_Idle_State();
    ~Player2_Queen_Idle_State() = default;

    void on_enter()override;
    void on_update(float delta)override;

};

class Player2_Queen_Jump_State : public State_Node
{
public:
    Player2_Queen_Jump_State();
    ~Player2_Queen_Jump_State() = default;

    void on_enter()override;
    void on_update(float delta)override;

};

class Player2_Queen_Roll_State : public State_Node
{
public:
    Player2_Queen_Roll_State();
    ~Player2_Queen_Roll_State() = default;

    void on_enter()override;
    void on_update(float delta)override;
    void on_exit()override;

private:
    Timer timer;
};

class Player2_Queen_Run_State : public State_Node
{
public:
    Player2_Queen_Run_State();
    ~Player2_Queen_Run_State() = default;

    void on_enter()override;
    void on_update(float delta)override;
    void on_exit()override;
};



#endif // PLAYER2_QUEEN_STATE_MACHINE_H
