/********************************************************************************
** Form generated from reading UI file 'select.ui'
**
** Created by: Qt User Interface Compiler version 6.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SELECT_H
#define UI_SELECT_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Select
{
public:
    QLabel *lab_player1_show;
    QLabel *lab_player2_show;
    QPushButton *btn_player1_last;
    QPushButton *btn_player1_next;
    QPushButton *btn_player2_last;
    QPushButton *btn_player2_next;
    QPushButton *btn_start;
    QPushButton *btn_over;
    QLabel *background;
    QLabel *lab_show_is_ai;
    QPushButton *btn_return_home;

    void setupUi(QWidget *Select)
    {
        if (Select->objectName().isEmpty())
            Select->setObjectName("Select");
        Select->resize(1380, 720);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icon/build/Desktop_Qt_6_7_0_MinGW_64_bit-Debug/resource/icon/\347\214\253\345\222\252.svg"), QSize(), QIcon::Normal, QIcon::Off);
        Select->setWindowIcon(icon);
        lab_player1_show = new QLabel(Select);
        lab_player1_show->setObjectName("lab_player1_show");
        lab_player1_show->setGeometry(QRect(200, 10, 380, 620));
        lab_player2_show = new QLabel(Select);
        lab_player2_show->setObjectName("lab_player2_show");
        lab_player2_show->setGeometry(QRect(940, 10, 380, 620));
        btn_player1_last = new QPushButton(Select);
        btn_player1_last->setObjectName("btn_player1_last");
        btn_player1_last->setGeometry(QRect(220, 640, 100, 40));
        btn_player1_next = new QPushButton(Select);
        btn_player1_next->setObjectName("btn_player1_next");
        btn_player1_next->setGeometry(QRect(320, 640, 100, 40));
        btn_player2_last = new QPushButton(Select);
        btn_player2_last->setObjectName("btn_player2_last");
        btn_player2_last->setGeometry(QRect(960, 640, 100, 40));
        btn_player2_next = new QPushButton(Select);
        btn_player2_next->setObjectName("btn_player2_next");
        btn_player2_next->setGeometry(QRect(1060, 640, 100, 40));
        btn_start = new QPushButton(Select);
        btn_start->setObjectName("btn_start");
        btn_start->setGeometry(QRect(630, 200, 120, 50));
        btn_over = new QPushButton(Select);
        btn_over->setObjectName("btn_over");
        btn_over->setGeometry(QRect(630, 320, 120, 50));
        background = new QLabel(Select);
        background->setObjectName("background");
        background->setGeometry(QRect(0, 0, 1380, 720));
        lab_show_is_ai = new QLabel(Select);
        lab_show_is_ai->setObjectName("lab_show_is_ai");
        lab_show_is_ai->setGeometry(QRect(890, 90, 121, 51));
        QFont font;
        font.setPointSize(22);
        font.setBold(true);
        lab_show_is_ai->setFont(font);
        btn_return_home = new QPushButton(Select);
        btn_return_home->setObjectName("btn_return_home");
        btn_return_home->setGeometry(QRect(630, 260, 120, 50));
        background->raise();
        lab_player1_show->raise();
        lab_player2_show->raise();
        btn_player1_last->raise();
        btn_player1_next->raise();
        btn_player2_last->raise();
        btn_player2_next->raise();
        btn_start->raise();
        btn_over->raise();
        lab_show_is_ai->raise();
        btn_return_home->raise();

        retranslateUi(Select);

        QMetaObject::connectSlotsByName(Select);
    } // setupUi

    void retranslateUi(QWidget *Select)
    {
        Select->setWindowTitle(QCoreApplication::translate("Select", "\351\200\211\346\213\251\347\225\214\351\235\242", nullptr));
        lab_player1_show->setText(QCoreApplication::translate("Select", "TextLabel", nullptr));
        lab_player2_show->setText(QCoreApplication::translate("Select", "TextLabel", nullptr));
        btn_player1_last->setText(QCoreApplication::translate("Select", "\344\270\212\344\270\200\344\270\252\350\247\222\350\211\262", nullptr));
        btn_player1_next->setText(QCoreApplication::translate("Select", "\344\270\213\344\270\200\344\270\252\350\247\222\350\211\262", nullptr));
        btn_player2_last->setText(QCoreApplication::translate("Select", "\344\270\212\344\270\200\344\270\252\350\247\222\350\211\262", nullptr));
        btn_player2_next->setText(QCoreApplication::translate("Select", "\344\270\213\344\270\200\344\270\252\350\247\222\350\211\262", nullptr));
        btn_start->setText(QCoreApplication::translate("Select", "\345\274\200\345\247\213", nullptr));
        btn_over->setText(QCoreApplication::translate("Select", "\347\273\223\346\235\237", nullptr));
        background->setText(QCoreApplication::translate("Select", "TextLabel", nullptr));
        lab_show_is_ai->setText(QString());
        btn_return_home->setText(QCoreApplication::translate("Select", "\350\277\224\345\233\236\351\246\226\351\241\265", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Select: public Ui_Select {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SELECT_H
