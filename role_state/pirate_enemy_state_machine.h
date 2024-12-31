#ifndef PIRATE_ENEMY_STATE_MACHINE_H
#define PIRATE_ENEMY_STATE_MACHINE_H

#include"enemy_attack_state.h"
#include"enemy_dead_state.h"
#include"enemy_fall_state.h"
#include"enemy_idle_state.h"
#include"enemy_jump_state.h"
#include"enemy_run_state.h"
#include"enemy_skill_state.h"


class Pirate_Enemy_Attack_State:public Enemy_Attack_State{
    Q_OBJECT
public:
    explicit Pirate_Enemy_Attack_State(QObject *parent = nullptr);
    ~Pirate_Enemy_Attack_State()=default;

    // State_Node interface
public:
    virtual void on_update(float delta) override;
};

class Pirate_Enemy_Dead_State:public Enemy_Dead_State{
    Q_OBJECT
public:
    explicit Pirate_Enemy_Dead_State(QObject *parent = nullptr);
    ~Pirate_Enemy_Dead_State()=default;
};

class Pirate_Enemy_Fall_State:public Enemy_Fall_State{
    Q_OBJECT
public:
    explicit Pirate_Enemy_Fall_State(QObject *parent = nullptr);
    ~Pirate_Enemy_Fall_State()=default;

    // State_Node interface
public:
    virtual void on_update(float delta) override;
};

class Pirate_Enemy_Idle_State:public Enemy_Idle_State{
    Q_OBJECT
public:
    explicit Pirate_Enemy_Idle_State(QObject *parent = nullptr);
    ~Pirate_Enemy_Idle_State()=default;

    // State_Node interface
public:
    virtual void on_update(float delta) override;
};

class Pirate_Enemy_Jump_State:public Enemy_Jump_State{
    Q_OBJECT
public:
    explicit Pirate_Enemy_Jump_State(QObject *parent = nullptr);
    ~Pirate_Enemy_Jump_State()=default;

    // State_Node interface
public:
    virtual void on_update(float delta) override;
};

class Pirate_Enemy_Run_State:public Enemy_Run_State{
    Q_OBJECT
public:
    explicit Pirate_Enemy_Run_State(QObject *parent = nullptr);
    ~Pirate_Enemy_Run_State()=default;

    // State_Node interface
public:
    virtual void on_update(float delta) override;
};

class Pirate_Enemy_Skill_State:public Enemy_Skill_State{
    Q_OBJECT
public:
    explicit Pirate_Enemy_Skill_State(QObject *parent = nullptr);
    ~Pirate_Enemy_Skill_State()=default;

    // State_Node interface
public:
    virtual void on_update(float delta) override;
};


#endif // PIRATE_ENEMY_STATE_MACHINE_H
