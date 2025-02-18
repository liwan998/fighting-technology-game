#include "select.h"
#include "interface/ui_select.h"
#include "resources_manager.h"
#include"interface_manager.h"
#include"character_manager.h"
#include"sound_manager.h"
#include"rand_number.h"

Select::Select(QWidget *parent)
    : Screen(parent)
    , ui(new Ui::Select)
{
    ui->setupUi(this);
    this->setFixedSize(1380,720);

    ui->btn_start->setStyleSheet(
        "QPushButton {"
        "   background: qlineargradient(x1:0, y1:0, x2:1, y2:1,"
        "               stop:0 #FF0000, stop:1 #FFB6C1);"
        "   border: none;"
        "   color: white;"  // 文字颜色
        "   padding: 8px;"
        "   border-radius: 5px;"
        "}"
        "QPushButton:hover {"
        "   background: qlineargradient(x1:0, y1:0, x2:1, y2:1,"
        "               stop:0 #FF6666, stop:1 #FFC0CB);"
        "}"
        "QPushButton:pressed {"
        "   background: qlineargradient(x1:0, y1:0, x2:1, y2:1,"
        "               stop:0 #CC0000, stop:1 #FF69B4);"
        "}");

    ui->btn_over->setStyleSheet(
        "QPushButton {"
        "   background: qlineargradient(x1:0, y1:0, x2:1, y2:1,"
        "               stop:0 #0000FF, stop:1 #FFFFFF);"
        "   border: none;"
        "   color: white;"  // 文字颜色（白色在蓝色区域更显眼）
        "   padding: 8px;"
        "   border-radius: 5px;"
        "}"
        "QPushButton:hover {"
        "   background: qlineargradient(x1:0, y1:0, x2:1, y2:1,"
        "               stop:0 #6666FF, stop:1 #F0F8FF);"  // 浅蓝+亚麻白
        "}"
        "QPushButton:pressed {"
        "   background: qlineargradient(x1:0, y1:0, x2:1, y2:1,"
        "               stop:0 #0000CC, stop:1 #E6E6FA);"  // 深蓝+薰衣草白
        "}");

    ui->btn_return_home->setStyleSheet(
        "QPushButton {"
        "   background: qlineargradient(x1:0, y1:0, x2:1, y2:1,"
        "               stop:0 #0000FF, stop:1 #FFFFFF);"
        "   border: none;"
        "   color: white;"  // 文字颜色（白色在蓝色区域更显眼）
        "   padding: 8px;"
        "   border-radius: 5px;"
        "}"
        "QPushButton:hover {"
        "   background: qlineargradient(x1:0, y1:0, x2:1, y2:1,"
        "               stop:0 #6666FF, stop:1 #F0F8FF);"  // 浅蓝+亚麻白
        "}"
        "QPushButton:pressed {"
        "   background: qlineargradient(x1:0, y1:0, x2:1, y2:1,"
        "               stop:0 #0000CC, stop:1 #E6E6FA);"  // 深蓝+薰衣草白
        "}");

    //60帧更新角色展示图片
    timer.start(1000/60);
    connect(&timer,&QTimer::timeout,this,[&](){
        if(current_player1_animation){
            current_player1_animation=&animation_pool[player1_select];
            current_player1_animation->on_update(0.016);
            QPixmap pixmap=QPixmap::fromImage(*current_player1_animation->get_current_image());
            ui->lab_player1_show->setPixmap(pixmap);
        }
        if(current_player2_animation){
            current_player2_animation=&animation_pool[player2_select+100];
            current_player2_animation->on_update(0.016);
            QPixmap pixmap=QPixmap::fromImage(*current_player2_animation->get_current_image());
            ui->lab_player2_show->setPixmap(pixmap);
        }
    });
    //1P选角展示画面
    Animation &animation_pirate1=animation_pool[0];
    animation_pirate1.add_fram(Resources_manager::instance()->find_atlas("pirate_show"));
    animation_pirate1.set_interval(0.032);

    Animation &animation_queen1=animation_pool[1];
    animation_queen1.add_fram(Resources_manager::instance()->find_atlas("queen_show"));
    animation_queen1.set_interval(0.032);

    Animation &animation_Jinbei1=animation_pool[2];
    animation_Jinbei1.add_fram(Resources_manager::instance()->find_atlas("Jinbei_show"));
    animation_Jinbei1.set_interval(0.032);

    Animation &animation_baby1=animation_pool[3];
    animation_baby1.add_fram(Resources_manager::instance()->find_atlas("baby_show_right"));
    animation_baby1.set_interval(0.07);

    //2P选角展示画面
    Animation &animation_pirate2=animation_pool[100];
    animation_pirate2.add_fram(Resources_manager::instance()->find_atlas("pirate_show"));
    animation_pirate2.set_interval(0.032);

    Animation &animation_queen2=animation_pool[101];
    animation_queen2.add_fram(Resources_manager::instance()->find_atlas("queen_show"));
    animation_queen2.set_interval(0.032);

    Animation &animation_Jinbei2=animation_pool[102];
    animation_Jinbei2.add_fram(Resources_manager::instance()->find_atlas("Jinbei_show"));
    animation_Jinbei2.set_interval(0.032);

    Animation &animation_baby2=animation_pool[103];
    animation_baby2.add_fram(Resources_manager::instance()->find_atlas("baby_show_left"));
    animation_baby2.set_interval(0.07);

    Animation &animation_pirate2_ai=animation_pool[104];
    animation_pirate2_ai.add_fram(Resources_manager::instance()->find_atlas("pirate_show"));
    animation_pirate2_ai.set_interval(0.032);

    Animation &animation_queen2_ai=animation_pool[105];
    animation_queen2_ai.add_fram(Resources_manager::instance()->find_atlas("queen_show"));
    animation_queen2_ai.set_interval(0.032);

    Animation &animation_Jinbei2_ai=animation_pool[106];
    animation_Jinbei2_ai.add_fram(Resources_manager::instance()->find_atlas("Jinbei_show"));
    animation_Jinbei2_ai.set_interval(0.032);

    Animation &animation_baby2_ai=animation_pool[107];
    animation_baby2_ai.add_fram(Resources_manager::instance()->find_atlas("baby_show_left"));
    animation_baby2_ai.set_interval(0.07);

    current_player1_animation=&animation_pool[0];
    current_player2_animation=&animation_pool[100];

    background_music=Sound_manager::instance()->find_background_music("select");
}

Select::~Select()
{
    delete ui;
}

void Select::on_enter()
{
    timer.start();
    int ran = Rand_number::instance()->randomInt(0,4);
    QImage *background=Resources_manager::instance()->find_image("select_background"+QString::number(ran));
    if (background) {
        ui->background->setPixmap(QPixmap::fromImage(*background));
    } else {
        qDebug() << "错误: start_background";
    }
    Screen::on_enter();
}

void Select::on_exit()
{
    timer.stop();
    Screen::on_exit();
}

void Select::on_btn_player1_last_clicked()
{
    if(player1_select==0){
        player1_select=player_num-1;
    }else{
        player1_select--;
    }
    qDebug()<<"当前玩家1为:"<<player1_select;
}


void Select::on_btn_player1_next_clicked()
{
    if(player1_select==player_num-1){
        player1_select=0;
    }else{
        player1_select++;
    }
    qDebug()<<"当前玩家1为:"<<player1_select;
}


void Select::on_btn_player2_last_clicked()
{
    if(player2_select==0){
        player2_select=player_num+ai_num-1;
    }else{
        player2_select--;
    }
    if(player2_select>=player_num){
        ui->lab_show_is_ai->setText("人机");
    }else if(!ui->lab_show_is_ai->text().isEmpty()){
        ui->lab_show_is_ai->clear();
    }
    qDebug()<<"当前玩家2为:"<<player2_select;
}


void Select::on_btn_player2_next_clicked()
{
    if(player2_select==player_num+ai_num-1){
        player2_select=0;
    }else{
        player2_select++;
    }
    if(player2_select>=player_num){
        ui->lab_show_is_ai->setText("人机");
    }else if(!ui->lab_show_is_ai->text().isEmpty()){
        ui->lab_show_is_ai->clear();
    }
    qDebug()<<"当前玩家2为:"<<player2_select;
}


void Select::on_btn_start_clicked()
{
    int player1_select=Interface_manager::instance()->get_select_widget()->getPlayer1_select();
    int player2_select=Interface_manager::instance()->get_select_widget()->getPlayer2_select();

    Character_Manager::instance()->on_enter(player1_select,player2_select);
    Interface_manager::instance()->switch_to(Interface_manager::Interface::game);
}

void Select::on_btn_over_clicked()
{
    Interface_manager::instance()->switch_to(Interface_manager::Interface::over);
}

int Select::getPlayer_num() const
{
    return player_num;
}

int Select::getPlayer2_select() const
{
    return player2_select;
}

int Select::getPlayer1_select() const
{
    return player1_select;
}


void Select::on_btn_return_home_clicked()
{
    Interface_manager::instance()->switch_to(Interface_manager::Interface::start);
}

