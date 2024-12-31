#ifndef QUEEN_ENEMY_STATE_MACHINE_H
#define QUEEN_ENEMY_STATE_MACHINE_H

#include"enemy_attack_state.h"
#include"enemy_dead_state.h"
#include"enemy_fall_state.h"
#include"enemy_idle_state.h"
#include"enemy_jump_state.h"
#include"enemy_run_state.h"
#include"enemy_skill_state.h"

class Queen_Enemy_Attack_State:public Enemy_Attack_State{
    Q_OBJECT
public:
    explicit Queen_Enemy_Attack_State(QObject *parent = nullptr);
    ~Queen_Enemy_Attack_State()=default;

    // State_Node interface
public:
    virtual void on_update(float delta) override;

    // Enemy_Attack_State interface
protected:
    virtual void update_hit_box_position() override;
};

class Queen_Enemy_Dead_State:public Enemy_Dead_State{
    Q_OBJECT
public:
    explicit Queen_Enemy_Dead_State(QObject *parent = nullptr);
    ~Queen_Enemy_Dead_State()=default;
};

class Queen_Enemy_Fall_State:public Enemy_Fall_State{
    Q_OBJECT
public:
    explicit Queen_Enemy_Fall_State(QObject *parent = nullptr);
    ~Queen_Enemy_Fall_State()=default;

    // State_Node interface
public:
    virtual void on_update(float delta) override;
};

class Queen_Enemy_Idle_State:public Enemy_Idle_State{
    Q_OBJECT
public:
    explicit Queen_Enemy_Idle_State(QObject *parent = nullptr);
    ~Queen_Enemy_Idle_State()=default;

    // State_Node interface
public:
    virtual void on_update(float delta) override;
};

class Queen_Enemy_Jump_State:public Enemy_Jump_State{
    Q_OBJECT
public:
    explicit Queen_Enemy_Jump_State(QObject *parent = nullptr);
    ~Queen_Enemy_Jump_State()=default;

    // State_Node interface
public:
    virtual void on_update(float delta) override;
};

class Queen_Enemy_Run_State:public Enemy_Run_State{
    Q_OBJECT
public:
    explicit Queen_Enemy_Run_State(QObject *parent = nullptr);
    ~Queen_Enemy_Run_State()=default;

    // State_Node interface
public:
    virtual void on_update(float delta) override;
};

class Queen_Enemy_Skill_State:public Enemy_Skill_State{
    Q_OBJECT
public:
    explicit Queen_Enemy_Skill_State(QObject *parent = nullptr);
    ~Queen_Enemy_Skill_State()=default;

    // State_Node interface
public:
    virtual void on_update(float delta) override;
};

#endif // QUEEN_ENEMY_STATE_MACHINE_H
