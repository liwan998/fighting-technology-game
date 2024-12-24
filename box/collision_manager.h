#ifndef COLLISION_MANAGER_H
#define COLLISION_MANAGER_H

#include <QObject>

#include"collision_box.h"
#include <QPainter>
//工厂
class Collision_Manager : public QObject
{
    Q_OBJECT
public:
    static Collision_Manager* instance();

    Collision_box* create_collision_box();
    void destroy_collision_box(Collision_box* collision_box);
    void delete_all();

    void process_collide();
    void on_debug_render(QPainter &painter);

private:
    Collision_Manager() = default;
    ~Collision_Manager();

private:
    static Collision_Manager* manager;
    QList<Collision_box*> collision_box_list;



};

#endif // COLLISION_MANAGER_H
