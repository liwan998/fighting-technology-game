/********************************************************************************
** Form generated from reading UI file 'select_venture.ui'
**
** Created by: Qt User Interface Compiler version 6.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SELECT_VENTURE_H
#define UI_SELECT_VENTURE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Select_venture
{
public:
    QLabel *lab_player1_show;
    QPushButton *btn_player_last;
    QPushButton *btn_player_next;
    QPushButton *btn_level_1;
    QPushButton *btn_level_2;
    QPushButton *btn_level_3;
    QPushButton *btn_level_4;
    QPushButton *btn_game_over;
    QLabel *background;
    QPushButton *btn_return_home;

    void setupUi(QWidget *Select_venture)
    {
        if (Select_venture->objectName().isEmpty())
            Select_venture->setObjectName("Select_venture");
        Select_venture->resize(1380, 720);
        lab_player1_show = new QLabel(Select_venture);
        lab_player1_show->setObjectName("lab_player1_show");
        lab_player1_show->setGeometry(QRect(10, 10, 380, 620));
        btn_player_last = new QPushButton(Select_venture);
        btn_player_last->setObjectName("btn_player_last");
        btn_player_last->setGeometry(QRect(20, 640, 100, 40));
        btn_player_next = new QPushButton(Select_venture);
        btn_player_next->setObjectName("btn_player_next");
        btn_player_next->setGeometry(QRect(140, 640, 100, 40));
        btn_level_1 = new QPushButton(Select_venture);
        btn_level_1->setObjectName("btn_level_1");
        btn_level_1->setGeometry(QRect(420, 10, 220, 90));
        QFont font;
        font.setPointSize(20);
        font.setBold(true);
        btn_level_1->setFont(font);
        btn_level_2 = new QPushButton(Select_venture);
        btn_level_2->setObjectName("btn_level_2");
        btn_level_2->setGeometry(QRect(660, 10, 220, 90));
        btn_level_2->setFont(font);
        btn_level_3 = new QPushButton(Select_venture);
        btn_level_3->setObjectName("btn_level_3");
        btn_level_3->setGeometry(QRect(900, 10, 220, 90));
        btn_level_3->setFont(font);
        btn_level_4 = new QPushButton(Select_venture);
        btn_level_4->setObjectName("btn_level_4");
        btn_level_4->setGeometry(QRect(1140, 10, 220, 90));
        btn_level_4->setFont(font);
        btn_game_over = new QPushButton(Select_venture);
        btn_game_over->setObjectName("btn_game_over");
        btn_game_over->setGeometry(QRect(1190, 630, 191, 91));
        QFont font1;
        font1.setPointSize(26);
        font1.setBold(true);
        btn_game_over->setFont(font1);
        background = new QLabel(Select_venture);
        background->setObjectName("background");
        background->setGeometry(QRect(0, 0, 1380, 720));
        btn_return_home = new QPushButton(Select_venture);
        btn_return_home->setObjectName("btn_return_home");
        btn_return_home->setGeometry(QRect(990, 630, 191, 91));
        btn_return_home->setFont(font1);
        background->raise();
        lab_player1_show->raise();
        btn_player_last->raise();
        btn_player_next->raise();
        btn_level_1->raise();
        btn_level_2->raise();
        btn_level_3->raise();
        btn_level_4->raise();
        btn_game_over->raise();
        btn_return_home->raise();

        retranslateUi(Select_venture);

        QMetaObject::connectSlotsByName(Select_venture);
    } // setupUi

    void retranslateUi(QWidget *Select_venture)
    {
        Select_venture->setWindowTitle(QCoreApplication::translate("Select_venture", "Form", nullptr));
        lab_player1_show->setText(QCoreApplication::translate("Select_venture", "TextLabel", nullptr));
        btn_player_last->setText(QCoreApplication::translate("Select_venture", "\344\270\212\344\270\200\344\270\252\350\247\222\350\211\262", nullptr));
        btn_player_next->setText(QCoreApplication::translate("Select_venture", "\344\270\213\344\270\200\344\270\252\350\247\222\350\211\262", nullptr));
        btn_level_1->setText(QCoreApplication::translate("Select_venture", "\347\254\254\344\270\200\345\205\263", nullptr));
        btn_level_2->setText(QCoreApplication::translate("Select_venture", "\347\254\254\344\272\214\345\205\263", nullptr));
        btn_level_3->setText(QCoreApplication::translate("Select_venture", "\347\254\254\344\270\211\345\205\263", nullptr));
        btn_level_4->setText(QCoreApplication::translate("Select_venture", "\347\254\254\345\233\233\345\205\263", nullptr));
        btn_game_over->setText(QCoreApplication::translate("Select_venture", "\351\200\200\345\207\272\346\270\270\346\210\217", nullptr));
        background->setText(QCoreApplication::translate("Select_venture", "TextLabel", nullptr));
        btn_return_home->setText(QCoreApplication::translate("Select_venture", "\350\277\224\345\233\236\351\246\226\351\241\265", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Select_venture: public Ui_Select_venture {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SELECT_VENTURE_H
