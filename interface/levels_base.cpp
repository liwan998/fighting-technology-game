#include "levels_base.h"
#include<QProgressBar>
#include<Qtimer.h>
#include<QMediaPlayer>

#include"character_manager.h"
#include"bullet_manager.h"
#include"floating_text_manager.h"
#include"collision_manager.h"

#include"thread_pool.h"

Levels_Base::Levels_Base(QWidget *parent)
    : QWidget{parent}
{
    this->setFixedSize(1380,720);
    timerFrameInterval60=new QTimer(this);
    timerFrameInterval60->start(16);
    connect(timerFrameInterval60,&QTimer::timeout,this,[&]{
        on_update(0.016);
    });

    timer_dead.set_wait_time(1.0f);
    timer_dead.set_one_shot(true);
    timer_dead.set_on_timeout([&]{
        is_dead=true;
    });

    P1HealthBar=new QProgressBar(this);
    P1HealthBar->resize(481,61);
    P1HealthBar->move(100,10);
    P1HealthBar->setMaximum(100);
    P1HealthBar->setMinimum(0);
    P1HealthBar->setValue(100);

    P2HealthBar=new QProgressBar(this);
    P2HealthBar->resize(481,61);
    P2HealthBar->move(900,10);
    P2HealthBar->setMaximum(100);
    P2HealthBar->setMinimum(0);
    P2HealthBar->setValue(100);

}

void Levels_Base::on_enter()
{
    timerFrameInterval60->start();
    timer_dead.restart();
    background_music->play();
}

void Levels_Base::on_exit()
{
    timerFrameInterval60->stop();
    background_music->stop();
}

void Levels_Base::on_update(float date)
{
    auto characte=Character_Manager::instance();
    characte->on_update(date);

    Thread_Pool::instance()->add_task(3,[&]{
        std::unique_lock<std::mutex> lock(mutexBulletUpdate);
        Bullet_Manager::instance()->on_update(date);
    });
    Thread_Pool::instance()->add_task(4,[&]{
        std::unique_lock<std::mutex> lock(mutexTextUpdate);
        Floating_Text_Manager::instance()->on_update(date);
    });
    Thread_Pool::instance()->add_task(2,[&]{
        std::unique_lock<std::mutex> lock(mutexProcessCollide);
        Collision_Manager::instance()->process_collide();
    });

    P1HealthBar->setValue(characte->get_player()->get_hp());
    P2HealthBar->setValue(characte->get_player2()->get_hp());

    this->repaint();

    if(Character_Manager::instance()->get_player()->get_hp()<=0
        ||Character_Manager::instance()->get_player2()->get_hp()<=0)
        timer_dead.on_update(date);
    if(is_dead){
        int player_hp=Character_Manager::instance()->get_player()->get_hp();
        int player2_hp=Character_Manager::instance()->get_player2()->get_hp();
        if(player_hp>player2_hp){
            emit game_over(true);
        }else if(player_hp<player2_hp){
            emit game_over(false);
        }
    }
}


void Levels_Base::paintEvent(QPaintEvent *event)
{
    painter.begin(this);
    painter.drawImage(0,0,*background);

    Character_Manager::instance()->on_render(painter);          //角色
    Bullet_Manager::instance()->on_render(painter);             //子弹
    Floating_Text_Manager::instance()->on_render(painter);      //漂浮文字
    Collision_Manager::instance()->on_debug_render(painter);    //碰撞箱调试框

    painter.end();
}

void Levels_Base::keyPressEvent(QKeyEvent *event)
{
    Character_Manager::instance()->key_Press(*event);
}

void Levels_Base::keyReleaseEvent(QKeyEvent *event)
{
    Character_Manager::instance()->key_Release(*event);
}
