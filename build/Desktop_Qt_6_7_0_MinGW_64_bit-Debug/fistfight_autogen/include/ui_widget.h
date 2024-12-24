/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 6.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QLCDNumber *lcdNumber;
    QProgressBar *player1_health;
    QProgressBar *player2_health;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName("Widget");
        Widget->resize(1380, 720);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icon/build/Desktop_Qt_6_7_0_MinGW_64_bit-Debug/resource/icon/\347\214\253\345\222\252.svg"), QSize(), QIcon::Normal, QIcon::Off);
        Widget->setWindowIcon(icon);
        lcdNumber = new QLCDNumber(Widget);
        lcdNumber->setObjectName("lcdNumber");
        lcdNumber->setGeometry(QRect(610, 0, 161, 91));
        player1_health = new QProgressBar(Widget);
        player1_health->setObjectName("player1_health");
        player1_health->setGeometry(QRect(100, 10, 481, 61));
        player1_health->setValue(100);
        player2_health = new QProgressBar(Widget);
        player2_health->setObjectName("player2_health");
        player2_health->setGeometry(QRect(900, 10, 481, 60));
        player2_health->setMinimumSize(QSize(0, 0));
        player2_health->setMaximumSize(QSize(16777215, 16777215));
        player2_health->setBaseSize(QSize(0, 0));
        player2_health->setValue(100);
        player2_health->setTextVisible(true);
        player2_health->setInvertedAppearance(true);

        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QCoreApplication::translate("Widget", "\346\210\230\346\226\227\347\225\214\351\235\242", nullptr));
        player1_health->setFormat(QCoreApplication::translate("Widget", "%p", nullptr));
        player2_health->setFormat(QCoreApplication::translate("Widget", "%p", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
