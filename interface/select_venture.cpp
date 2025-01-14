#include "select_venture.h"
#include "ui_select_venture.h"
#include"resources_manager.h"
#include"interface_manager.h"
#include"sound_manager.h"
#include"rand_number.h"

Select_venture::Select_venture(QWidget *parent)
    : Screen(parent)
    , ui(new Ui::Select_venture)
{
    ui->setupUi(this);
    timer.start(1000/60);
    connect(&timer,&QTimer::timeout,this,[&](){
        if(current_player1_animation){
            current_player1_animation=&animation_pool[player1_select];
            current_player1_animation->on_update(0.016);
            QPixmap pixmap=QPixmap::fromImage(*current_player1_animation->get_current_image());
            ui->lab_player1_show->setPixmap(pixmap);
        }
    });
    //角色展示界面
    Animation &animation_pirate1=animation_pool[0];
    animation_pirate1.add_fram(Resources_manager::instance()->find_atlas("pirate_show"));
    animation_pirate1.set_interval(0.032);

    Animation &animation_queen1=animation_pool[1];
    animation_queen1.add_fram(Resources_manager::instance()->find_atlas("queen_show"));
    animation_queen1.set_interval(0.032);

    current_player1_animation=&animation_pool[0];
    background_music=Sound_manager::instance()->find_background_music("select");
}

Select_venture::~Select_venture()
{
    delete ui;
}

void Select_venture::on_enter()
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

void Select_venture::on_exit()
{
    timer.stop();
    Screen::on_exit();
}

void Select_venture::on_btn_player_last_clicked()
{
    if(player1_select==0){
        player1_select=player_num-1;
    }else{
        player1_select--;
    }
}


void Select_venture::on_btn_player_next_clicked()
{
    if(player1_select==player_num-1){
        player1_select=0;
    }else{
        player1_select++;
    }
}


void Select_venture::on_btn_game_over_clicked()
{
    Interface_manager::instance()->switch_to(Interface_manager::Interface::over);
}


void Select_venture::on_btn_return_home_clicked()
{
    Interface_manager::instance()->switch_to(Interface_manager::Interface::start);
}

