#include "collision_manager.h"

Collision_Manager* Collision_Manager::manager = nullptr;
std::mutex Collision_Manager::m_mutex;

Collision_Manager* Collision_Manager::instance() {
    std::unique_lock<std::mutex>m_mutext;
    if (!manager) {
        manager = new Collision_Manager();
    }
    return manager;
}

Collision_box* Collision_Manager::create_collision_box()    //创建碰撞箱
{
    Collision_box* collision_box = new Collision_box();
    collision_box_list.push_back(collision_box);
    return collision_box;
}

void Collision_Manager::destroy_collision_box(Collision_box* collision_box)     //删除特定碰撞箱
{
    collision_box_list.removeOne(collision_box);
    delete collision_box;
}

void Collision_Manager::delete_all()
{
    for(auto i:collision_box_list){
        delete i;
    }
    collision_box_list.clear();
}

void Collision_Manager::process_collide()   //检测碰撞是否发生
{
    for (auto collision_box_src : collision_box_list) {
        if (!collision_box_src->enabled || collision_box_src->layer_dst == Collision_layer::None) {
            continue;
        }
        for (auto collision_box_dst : collision_box_list) {
            if (!collision_box_dst->enabled || collision_box_src == collision_box_dst ||
                collision_box_src->layer_dst != collision_box_dst->layer_src) {
                continue;
            }
            bool is_collide_x = (fmax(collision_box_src->position.x() + collision_box_src->size.x() / 2,
                                      collision_box_dst->position.x() + collision_box_dst->size.x() / 2)
                                     - fmin(collision_box_src->position.x() - collision_box_src->size.x()/2,
                                            collision_box_dst->position.x() - collision_box_dst->size.x() / 2)
                                 <= collision_box_src->size.x() + collision_box_dst->size.x());

            bool is_collide_y= (fmax(collision_box_src->position.y() + collision_box_src->size.y() / 2,
                                      collision_box_dst->position.y() + collision_box_dst->size.y() / 2)
                                     - fmin(collision_box_src->position.y() - collision_box_src->size.y() / 2,
                                            collision_box_dst->position.y() - collision_box_dst->size.y() / 2)
                                 <= collision_box_src->size.y() + collision_box_dst->size.y());
            if (is_collide_x && is_collide_y && collision_box_src->on_collide) {
                collision_box_src->on_collide();
            }
        }
    }
}

void Collision_Manager::on_debug_render(QPainter &painter)  //画出碰撞箱辅助线
{
    for (auto collision_box : collision_box_list) {
        QPen pen;
        pen.setWidth(2);
        if(collision_box->enabled){
            pen.setColor(Qt::red);
        }else{
            pen.setColor(Qt::white);
        }
        if(collision_box->layer_src==Collision_layer::Player)
            pen.setColor(Qt::blue);
        painter.setPen(pen);
        painter.drawRect((int)(collision_box->position.x() - collision_box->size.x() / 2),
                         (int)(collision_box->position.y() - collision_box->size.y() / 2),
                         (int)collision_box->size.x(),(int)collision_box->size.y());
        pen.setWidth(5);
        pen.setColor(QColor(255,255,255));
        painter.setPen(pen);
        painter.drawPoint(collision_box->position);
    }
}

Collision_Manager::~Collision_Manager()
{
    delete_all();
}
