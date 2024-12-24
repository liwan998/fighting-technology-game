#ifndef PLAYER_H
#define PLAYER_H
//玩家角色控制基类
#include "character.h"
#include"timer.h"



class Player : public Character
{
    Q_OBJECT
public:
    explicit Player(QObject *parent = nullptr);

    enum class Player_select{
        left=0,
        right
    };


public:
    ~Player();

public:


    int get_move_axis()const {
        return is_right_key_down - is_left_key_down;
    }

    Player_select getPlayer_selects() const;
    void setPlayer_selects(Player_select newPlayer_selects);

    void setIs_key_control(bool newIs_key_control);

    void clear_button();

public:
    void key_Press(QKeyEvent& event)override;
    void key_Release(QKeyEvent& event)override;

    void on_update(float delta)override;
    void on_render(QPainter &painter)override;

public://动作
    void on_jump()override;
    void on_roll()override;
    void on_attack()override;
    void on_skill()override;
    //void on_ultimate();
    void on_hurt()override;
    void on_dead()override;

    const bool can_attack()const;
    const bool can_skill()const;
    //const bool can_ultimate();
    const bool can_jump()const;
    const bool can_roll()const;

private:
    bool is_left_key_down = false;      //按键控制
    bool is_right_key_down = false;
    bool is_jump_key_down = false;
    bool is_roll_key_down = false;

    bool is_key_control=true;   //当前是否可以控制角色

    bool is_attack_key_down = false;    //普通攻击
    bool is_skill_key_down = false;     //小技能
    //bool is_ultimate_key_down=false;    //大招

protected:
    const float CD_ROLL = 0.75f;

protected:
    Timer timer_roll;  //翻滚
    bool is_roll_cd=false;

    Timer timer_skill; //小技能
    bool is_skill_cd=false;

    // Timer timer_ultimate; //大招
    // bool is_ultimate=false;
    // bool is_ultimate_cd=false;

    Timer timer_attack;//普通攻击
    bool is_attack_cd=false;

protected:
    Player_select player_selects=Player::Player_select::left;


};

#endif // PLAYER_H
