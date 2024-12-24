#ifndef COLLISION_BOX_H
#define COLLISION_BOX_H

#include<QPointF>
#include <functional>

enum class Collision_layer
{
    None,
    Player,
    Enemy,
};

class Collision_box
{
    friend class Collision_Manager;
private:
    Collision_box() = default;
    ~Collision_box() = default;

public:
    void set_enabled(bool flag);
    void set_layer_src(Collision_layer layer);
    void set_layer_dst(Collision_layer layer);
    void set_on_collide(std::function<void()>on_collide);
    void set_size(const QPointF& size);
    const QPointF get_size()const;
    void set_position(const QPointF position);

private:
    QPointF size;
    QPointF position;               //碰撞逻辑中心位置
    bool enabled = true;                                    //是否启用碰撞
    std::function<void()> on_collide;                       //回调函数
    Collision_layer layer_src = Collision_layer::None;		//自身碰撞层
    Collision_layer layer_dst = Collision_layer::None;		//目标碰撞层
};

#endif // COLLISION_BOX_H
