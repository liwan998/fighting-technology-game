#ifndef ENEMY_STATE_MACHINE_H
#define ENEMY_STATE_MACHINE_H

#include"enemy_attack_state.h"
#include"enemy_dead_state.h"
#include"enemy_fall_state.h"
#include"enemy_idle_state.h"
#include"enemy_jump_state.h"
#include"enemy_run_state.h"
#include"enemy_skill_state.h"

class Ordinary_Enemy_Attack_State:public Enemy_Attack_State{
    Q_OBJECT
public:
    explicit Ordinary_Enemy_Attack_State(QObject *parent = nullptr);
    ~Ordinary_Enemy_Attack_State()=default;

public:
    virtual void on_update(float delta) override;
};

class Ordinary_Enemy_Dead_State:public Enemy_Dead_State{
    Q_OBJECT
public:
    explicit Ordinary_Enemy_Dead_State(QObject *parent = nullptr);
    ~Ordinary_Enemy_Dead_State()=default;
};

class Ordinary_Enemy_Fall_State:public Enemy_Fall_State{
    Q_OBJECT
public:
    explicit Ordinary_Enemy_Fall_State(QObject *parent = nullptr);
    ~Ordinary_Enemy_Fall_State()=default;

public:
    virtual void on_update(float delta) override;
};

class Ordinary_Enemy_Idle_State:public Enemy_Idle_State{
    Q_OBJECT
public:
    explicit Ordinary_Enemy_Idle_State(QObject *parent = nullptr);
    ~Ordinary_Enemy_Idle_State()=default;

public:
    virtual void on_update(float delta) override;
};

class Ordinary_Enemy_Jump_State:public Enemy_Jump_State{
    Q_OBJECT
public:
    explicit Ordinary_Enemy_Jump_State(QObject *parent = nullptr);
    ~Ordinary_Enemy_Jump_State()=default;

public:
    virtual void on_update(float delta) override;
};

class Ordinary_Enemy_Run_State:public Enemy_Run_State{
    Q_OBJECT
public:
    explicit Ordinary_Enemy_Run_State(QObject *parent = nullptr);
    ~Ordinary_Enemy_Run_State()=default;

public:
    virtual void on_update(float delta) override;
};

class Ordinary_Enemy_Skill_State:public Enemy_Skill_State{
    Q_OBJECT
public:
    explicit Ordinary_Enemy_Skill_State(QObject *parent = nullptr);
    ~Ordinary_Enemy_Skill_State()=default;

public:
    virtual void on_update(float delta) override;
};

#endif // ENEMY_STATE_MACHINE_H
