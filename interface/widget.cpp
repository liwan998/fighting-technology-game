#include "widget.h"
#include "./ui_widget.h"
#include"character_manager.h"
#include"resources_manager.h"
#include"collision_manager.h"
#include"interface_manager.h"
#include"bullet_manager.h"
#include"sound_manager.h"
#include"floating_text_manager.h"
#include<QDebug>
#include<QMessageBox>

Widget::Widget(QWidget *parent)
    : Screen(parent)
    , ui(new Ui::Widget)
{
    //ui页面修改
    ui->setupUi(this);
    ui->lcdNumber->setDigitCount(3);
    timer_game.setInterval(1000);
    connect(&timer_game,&QTimer::timeout,this,[&]{
        int currentValue = ui->lcdNumber->intValue();
        if (currentValue > 0) {
            ui->lcdNumber->display(currentValue - 1);
        } else {
            //失败操作
        }
    });

    background=Resources_manager::instance()->find_image("background");
    timer60.setInterval(1000/60);     //每过秒六十帧刷新
    connect(&timer60,&QTimer::timeout,this,&Widget::time_60);

    timer_dead.set_wait_time(1.0f);
    timer_dead.set_one_shot(true);
    timer_dead.set_on_timeout([&]{
        is_dead=true;
    });
    background_music=Sound_manager::instance()->find_background_music("game");

}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_enter()
{
    is_dead=false;
    timer_dead.restart();
    timer60.start();
    timer_game.start();
    ui->lcdNumber->display(60);
    Screen::on_enter();
}

void Widget::on_exit()
{
    timer60.stop();
    timer_game.stop();
    Screen::on_exit();
}

void Widget::time_60()
{
    auto manager=Character_Manager::instance();
    const float timer=0.016;
    manager->on_update(timer);
    Bullet_Manager::instance()->on_update(timer);
    Floating_Text_Manager::instance()->on_update(timer);
    Collision_Manager::instance()->process_collide();
    ui->player1_health->setValue(manager->get_player()->get_hp());
    ui->player2_health->setValue(manager->get_player2()->get_hp());

    this->repaint();
    if(Character_Manager::instance()->get_player()->get_hp()<=0
        ||Character_Manager::instance()->get_player2()->get_hp()<=0)
        timer_dead.on_update(timer);

    if(ui->lcdNumber->value()==0||is_dead){
        int player_hp=Character_Manager::instance()->get_player()->get_hp();
        int player2_hp=Character_Manager::instance()->get_player2()->get_hp();
        QString str;
        if(player_hp>player2_hp){
            str="1P胜利";
        }else if(player_hp<player2_hp){
            str="2P胜利";
        }else{
            str="平局";
        }
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(nullptr, "胜负已分", str+"\n在来一局？",
                                      QMessageBox::Yes | QMessageBox::No);

        if (reply == QMessageBox::Yes) {
            Interface_manager::instance()->switch_to(Interface_manager::Interface::select);
        } else {
            timer60.stop();
            Interface_manager::instance()->switch_to(Interface_manager::Interface::over);
        }
    }
}

void Widget::paintEvent(QPaintEvent *event)
{
    painter.begin(this);
    painter.drawImage(0,0,*background);

    Character_Manager::instance()->on_render(painter);
    Bullet_Manager::instance()->on_render(painter);
    Floating_Text_Manager::instance()->on_render(painter);
    Collision_Manager::instance()->on_debug_render(painter);  //碰撞箱调试框

    painter.end();
}

void Widget::keyPressEvent(QKeyEvent *event)
{
    Character_Manager::instance()->key_Press(*event);
}

void Widget::keyReleaseEvent(QKeyEvent *event)
{
    Character_Manager::instance()->key_Release(*event);
}
