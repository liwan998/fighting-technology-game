#ifndef BULLET_MANAGER_H
#define BULLET_MANAGER_H

#include <QObject>
#include<mutex>
#include"bullet.h"
#include"player.h"

class Bullet_Manager : public QObject
{
    Q_OBJECT
public:
    enum class Bullet_kind{
        queen_big=0,
        queen_small
    };

public:
    static Bullet_Manager* instance();
    void create_bullet(Bullet_kind kind,bool is_left,QPointF position,Player::Player_select player_select);
    void destroy_bullet(Bullet*bullet);
    void on_update(float delta);
    void on_render(QPainter &painter);
    void deleta_all();
private:
    Bullet_Manager() = default;
    ~Bullet_Manager();

private:
    static Bullet_Manager* manager;
    static std::mutex m_mutex;
    QList<Bullet*> bullet_list;

};

#endif // BULLET_MANAGER_H
