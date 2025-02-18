#include "game.h"
#include "./ui_game.h"
#include"character_manager.h"
#include"resources_manager.h"
#include"collision_manager.h"
#include"interface_manager.h"
#include"bullet_manager.h"
#include"sound_manager.h"
#include"floating_text_manager.h"
#include<QDebug>
#include<QMessageBox>
#include<thread_pool.h>
#include<QPropertyAnimation>
#include<QGraphicsDropShadowEffect>

Game::Game(QWidget *parent)
    : Screen(parent)
    , ui(new Ui::Widget)
{
    //ui页面修改
    ui->setupUi(this);
    ui->lcdNumber->setDigitCount(3);
    this->setFixedSize(1380,720);

    ui->player1_health->setStyleSheet(
        "QProgressBar {"
        "   border: 2px solid #8B0000;"      // 深红色边框
        "   border-radius: 6px;"            // 圆角边框
        "   background: #2F4F4F;"           // 暗灰色背景
        "   text-align: center;"            // 文字居中
        "   color: #FFD700;"                // 金色文字更醒目
        "   font-weight: bold;"             // 粗体字
        "}"
        "QProgressBar::chunk {"
        "   background: qlineargradient(x1:0, y1:0.5, x2:1, y2:0.5,"  // 水平渐变
        "               stop:0 #FF4500, stop:0.5 #FF0000, stop:1 #8B0000);"  // 橙红→鲜红→暗红
        "   border-radius: 4px;"            // 内部圆角
        "   margin: 1px;"                   // 边距
        "}");

    ui->player2_health->setStyleSheet(
        "QProgressBar {"
        "   border: 2px solid #2F0000;"      // 更深的边框颜色
        "   border-radius: 6px;"
        "   background: #1A1A1A;"           // 深灰色背景
        "   text-align: center;"
        "   color: #FFD700;"                // 金色文字更醒目
        "   font-weight: bold;"
        "}"
        "QProgressBar::chunk {"
        "   background: qlineargradient(x1:0, y1:0.5, x2:1, y2:0.5,"  // 保持水平渐变
        "               stop:0 #8B0000, stop:0.5 #FF0000, stop:1 #FF4500);"  // 反向渐变
        "   border-radius: 4px;"
        "   margin: 1px;"
        "}");

    ui->player1_health->move(20,20);
    ui->player2_health->move(this->width()-ui->player2_health->size().width()-20,20);

    ui->lcdNumber->setStyleSheet(
        "QLCDNumber {"              // LCD数字
        "   background: transparent;"       // 透明背景
        "   color: #FF2222;"       // 亮红色数字
        "   border: 2px solid #FF4444;"
        "   border-radius: 0px;"   // 直角边框
        "   qproperty-segmentStyle: Filled;"
        "}");

    // 添加闪烁动画（需要QTimer配合）
    QTimer::singleShot(1000, [this](){
        ui->lcdNumber->setStyleSheet("color: #FF0000;");  // 变红
        QTimer::singleShot(200, [this](){
            ui->lcdNumber->setStyleSheet("color: #00FF00;");  // 恢复
        });
    });

    // 数字变化动画
    QPropertyAnimation *anim = new QPropertyAnimation(ui->lcdNumber, "value");
    anim->setDuration(1000);
    anim->setEasingCurve(QEasingCurve::OutQuint);
    anim->start();

    QGraphicsDropShadowEffect *effect = new QGraphicsDropShadowEffect;
    effect->setColor(QColor(0, 255, 0, 128));
    effect->setBlurRadius(20);
    ui->lcdNumber->setGraphicsEffect(effect);


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
    connect(&timer60,&QTimer::timeout,this,&Game::time_60);

    timer_dead.set_wait_time(1.0f);
    timer_dead.set_one_shot(true);
    timer_dead.set_on_timeout([&]{
        is_dead=true;
    });
    background_music=Sound_manager::instance()->find_background_music("game");

}

Game::~Game()
{
    delete ui;
}

void Game::on_enter()
{
    is_dead=false;
    timer_dead.restart();
    timer60.start();
    timer_game.start();
    ui->lcdNumber->display(60);
    Screen::on_enter();
}

void Game::on_exit()
{
    timer60.stop();
    timer_game.stop();
    Screen::on_exit();
}

void Game::time_60()
{
    auto manager=Character_Manager::instance();
    manager->on_update(timer);

    Thread_Pool::instance()->add_task(3,[&]{
        std::unique_lock<std::mutex> lock(mutexBulletUpdate);
        Bullet_Manager::instance()->on_update(timer);
    });
    Thread_Pool::instance()->add_task(4,[&]{
        std::unique_lock<std::mutex> lock(mutexTextUpdate);
        Floating_Text_Manager::instance()->on_update(timer);
    });

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

void Game::paintEvent(QPaintEvent *event)
{
    painter.begin(this);
    painter.drawImage(0,0,*background);

    Character_Manager::instance()->on_render(painter);
    Bullet_Manager::instance()->on_render(painter);
    Floating_Text_Manager::instance()->on_render(painter);
    Collision_Manager::instance()->on_debug_render(painter);  //碰撞箱调试框

    painter.end();
}

void Game::keyPressEvent(QKeyEvent *event)
{
    Character_Manager::instance()->key_Press(*event);
}

void Game::keyReleaseEvent(QKeyEvent *event)
{
    Character_Manager::instance()->key_Release(*event);
}
