#ifndef PIRATE_PLAYER_STATE_MACHINE_H
#define PIRATE_PLAYER_STATE_MACHINE_H

#include"player_attack_state.h"
#include"player_dead_state.h"
#include"player_fall_state.h"
#include"player_idle_state.h"
#include"player_jump_state.h"
#include"player_roll_state.h"
#include"player_run_state.h"
#include"player_skill_state.h"

class Pirate_Player_Attack_State:public Player_Attack_State{
    Q_OBJECT
public:
    explicit Pirate_Player_Attack_State(Player::Player_select player_select,QObject *parent = nullptr);
    ~Pirate_Player_Attack_State()=default;
};

class Pirate_Player_Dead_State:public Player_Dead_State{
    Q_OBJECT
public:
    explicit Pirate_Player_Dead_State(Player::Player_select player_select,QObject *parent = nullptr);
    ~Pirate_Player_Dead_State()=default;
};

class Pirate_Player_Fall_State:public Player_Fall_State{
    Q_OBJECT
public:
    explicit Pirate_Player_Fall_State(Player::Player_select player_select,QObject *parent = nullptr);
    ~Pirate_Player_Fall_State()=default;
};

class Pirate_Player_Idle_State:public Player_Idle_State{
    Q_OBJECT
public:
    explicit Pirate_Player_Idle_State(Player::Player_select player_select,QObject *parent = nullptr);
    ~Pirate_Player_Idle_State()=default;
};

class Pirate_Player_Jump_State:public Player_Jump_State{
    Q_OBJECT
public:
    explicit Pirate_Player_Jump_State(Player::Player_select player_select,QObject *parent = nullptr);
    ~Pirate_Player_Jump_State()=default;
};

class Pirate_Player_Roll_State:public Player_Roll_State{
    Q_OBJECT
public:
    explicit Pirate_Player_Roll_State(Player::Player_select player_select,QObject *parent = nullptr);
    ~Pirate_Player_Roll_State()=default;
};

class Pirate_Player_Run_State:public Player_Run_State{
    Q_OBJECT
public:
    explicit Pirate_Player_Run_State(Player::Player_select player_select,QObject *parent = nullptr);
    ~Pirate_Player_Run_State()=default;
};

class Pirate_Player_Skill_State:public Player_Skill_State{
    Q_OBJECT
public:
    explicit Pirate_Player_Skill_State(Player::Player_select player_select,QObject *parent = nullptr);
    ~Pirate_Player_Skill_State()=default;
};

#endif // PIRATE_PLAYER_STATE_MACHINE_H
