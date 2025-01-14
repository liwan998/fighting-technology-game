#include "start.h"
#include "interface/ui_start.h"
#include "resources_manager.h"
#include"interface_manager.h"
#include<QImage>
#include "rand_number.h"
#include<QDebug>
#include"sound_manager.h"

Start::Start(QWidget *parent)
    : Screen(parent)
    , ui(new Ui::Start)
{
    ui->setupUi(this);
    QImage *title=Resources_manager::instance()->find_image("start_title");
    if (title) {
        ui->label->setPixmap(QPixmap::fromImage(*title));
    } else {
        qDebug() << "错误: start_title";
    }
    background_music=Sound_manager::instance()->find_background_music("start");
}

Start::~Start()
{
    delete ui;
}

void Start::on_enter()
{
    int ran = Rand_number::instance()->randomInt(0,2);
    QImage *background=Resources_manager::instance()->find_image("start_background"+QString::number(ran));
    if (background) {
        ui->background->setPixmap(QPixmap::fromImage(*background));
    } else {
        qDebug() << "错误: start_background";
    }
    Screen::on_enter();
}

void Start::on_exit()
{
    Screen::on_exit();
}

void Start::on_pushButton_1_clicked()
{
    Interface_manager::instance()->switch_to(Interface_manager::Interface::select);
}


void Start::on_pushButton_2_clicked()
{
    this->close();
}


void Start::on_pushButton_3_clicked()
{
    Interface_manager::instance()->switch_to(Interface_manager::Interface::select_venture);
}

