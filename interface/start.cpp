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
    this->setFixedSize(1380,720);

    ui->pushButton_1->setStyleSheet(
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

    ui->pushButton_3->setStyleSheet(
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

    ui->pushButton_2->setStyleSheet(
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

