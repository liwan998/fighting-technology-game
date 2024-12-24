#include "collision_box.h"

void Collision_box::set_enabled(bool flag)
{
    this->enabled = flag;
}

void Collision_box::set_layer_src(Collision_layer layer)
{
    this->layer_src = layer;
}

void Collision_box::set_layer_dst(Collision_layer layer)
{
    this->layer_dst = layer;
}

void Collision_box::set_on_collide(std::function<void ()> on_collide)
{
    this->on_collide = on_collide;
}

void Collision_box::set_size(const QPointF &size)
{
    this->size = size;
}

const QPointF Collision_box::get_size() const
{
    return size;
}

void Collision_box::set_position(const QPointF position)
{
    this->position = position;
}
