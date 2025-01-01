#ifndef CHARACTER_H
#define CHARACTER_H
//游戏角色基类
#include <QObject>
#include<QKeyEvent>
#include<QMediaPlayer>
#include"animation.h"
#include"collision_box.h"
#include"state_machine.h"
#include"timer.h"


class Character : public QObject
{
    Q_OBJECT
public:
    explicit Character(QObject *parent = nullptr);
    ~Character();

protected:
    struct Animation_Group {
        Animation left;
        Animation right;
    };

public:
    void decrease_hp(float Blood_volume);
    int get_hp();
    void set_position(const QPointF& position);
    const QPointF& get_position()const;
    QPointF getPosition_foot() const;
    void set_velocity(const QPointF& velocity);
    const QPointF& get_velocity()const;
    QPointF get_logic_center()const;
    void set_enable_gravity(bool enable_gravity);
    Collision_box* get_hit_attack_box();
    Collision_box* get_hit_skill_box();
    Collision_box* get_hurt_box();
    bool is_on_floor()const;
    float get_floor_y()const;
    bool getIs_facing_left() const;

public://进入各种状态
    void make_invulnerable();

public:
    virtual void key_Press(QKeyEvent& event);
    virtual void key_Release(QKeyEvent& event);
    virtual void on_update(float delta);
    virtual void on_render(QPainter &painter);

    void switch_state(const std::string& id);
    void set_animation(const QString& id);

    void setIs_attack(bool newIs_attack);
    bool getIs_attack() const;

    bool getIs_roll() const;
    void setIs_roll(bool newIs_roll);

    bool getIs_skill() const;
    void setIs_skill(bool newIs_skill);

public:
    virtual void on_jump();
    virtual void on_roll();
    virtual void on_attack();
    virtual void on_skill();
    virtual void on_hurt();
    virtual void on_dead();

protected:
    const float FLOOR_Y = 620;		//地板的竖直方向坐标
    const float GRAVITY = 980*2;	//重力大小

    const int WIDE=1380;  //界面宽
    const int HIGHT=720;  //界面高

    const int HIT_FREQUENCY=5;  //单位时间被攻击多少次可以进入无敌状态

    float SPEED_RUN = 300.0f;
    float SPEED_JUMP = 780.0f;
    float SPEED_ROLL = 800.0f;

protected:  //各种状态
    bool is_blink_invulnerable=false;//当前是否处于闪烁的不可见帧
    Timer timer_invulnerable_blink;	//无敌闪烁定时器
    bool is_invulnerable = false;	//无敌状态
    Timer timer_invulnerable_status;//无敌状态定时器

    float hit_number=0;            //显示受伤数字
    Timer timer_hit_number;     //受伤数字显示时间
    int hit_frequency;          //受击次数
    Timer timer_hit_frequency;  //重置受击次数
protected:
    float hp = 100;
    QPointF position;               //角色位置
    QPointF position_foot;          //角色脚底位置偏移量
    QPointF velocity;				//速度
    float logic_heigth = 0;			//逻辑高度
    bool is_facing_left = true;		//角色是否向左
    State_Machine state_machine;	//角色状态机
    bool enable_gravity = true;		//重力模拟
    Collision_box* hit_attack_box = nullptr;	//普通攻击碰撞箱
    Collision_box* hit_skill_box = nullptr;   //技能攻击碰撞箱
    Collision_box* hurt_box = nullptr;	//受击碰撞箱
    Animation_Group* current_animation = nullptr;//当前角色动画帧
    std::unordered_map<QString, Animation_Group>animation_pool;//角色动画池

protected:
    bool is_roll=false;     //是否处于翻滚
    bool is_skill=false;    //是否处于技能攻击
    bool is_attack=false;   //是否处于普通攻击

protected://音乐特效
    QMediaPlayer *jump_effect=nullptr;
    QMediaPlayer *roll_effect=nullptr;
    QMediaPlayer *attack_effect=nullptr;
    QMediaPlayer *skill_effect=nullptr;
    QMediaPlayer *dead_effect=nullptr;

};

#endif // CHARACTER_H
