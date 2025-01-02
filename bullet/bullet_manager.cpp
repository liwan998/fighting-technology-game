#include "bullet_manager.h"
#include"bullet_queen_big.h"
#include"bullet_queen_small.h"

Bullet_Manager* Bullet_Manager::manager=nullptr;
std::mutex Bullet_Manager::m_mutex;

Bullet_Manager *Bullet_Manager::instance()
{
    std::unique_lock<std::mutex>m_mutex;
    if (!manager) {
        manager = new Bullet_Manager();
    }
    return manager;
}

void Bullet_Manager::create_bullet(Bullet_kind kind,bool is_left,QPointF position,Player::Player_select player_select)
{
    Bullet *bullet=nullptr;
    switch (kind) {
    case Bullet_Manager::Bullet_kind::queen_big:
        bullet=new Bullet_queen_big();
        bullet->setVelocity(is_left?QPointF(-5,0):QPointF(5,0));
        break;
    case Bullet_Manager::Bullet_kind::queen_small:
        bullet=new Bullet_queen_small();
        bullet->setVelocity(is_left?QPointF(-4,0):QPointF(4,0));
        break;
    default:
        break;
    }
    bullet->on_enter(player_select);
    bullet->setPosition(position);
    bullet_list.push_back(bullet);
}

void Bullet_Manager::destroy_bullet(Bullet *bullet)
{
    bullet_list.removeOne(bullet);
    delete bullet;
}

void Bullet_Manager::on_update(float delta)
{
    if(bullet_list.isEmpty()) return;
    for(const auto i:bullet_list){
        i->on_update(delta);
        if(!i->getValid()){
            destroy_bullet(i);
        }
    }
}

void Bullet_Manager::on_render(QPainter &painter)
{
    if(bullet_list.isEmpty()) return;
    for(const auto i:bullet_list){
        i->on_render(painter);
    }
}

void Bullet_Manager::deleta_all()
{
    if(bullet_list.isEmpty()) return;
    for(auto i:bullet_list){
        if(i)
            delete i;
    }
    bullet_list.clear();
}

Bullet_Manager::~Bullet_Manager()
{
    for(auto i:bullet_list){
        delete i;
    }
    bullet_list.clear();
}
