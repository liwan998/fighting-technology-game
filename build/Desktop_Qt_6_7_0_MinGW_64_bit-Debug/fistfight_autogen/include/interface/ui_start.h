/********************************************************************************
** Form generated from reading UI file 'start.ui'
**
** Created by: Qt User Interface Compiler version 6.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_START_H
#define UI_START_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Start
{
public:
    QPushButton *pushButton_2;
    QLabel *label;
    QPushButton *pushButton_1;
    QLabel *background;
    QPushButton *pushButton_3;

    void setupUi(QWidget *Start)
    {
        if (Start->objectName().isEmpty())
            Start->setObjectName("Start");
        Start->resize(1380, 720);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icon/build/Desktop_Qt_6_7_0_MinGW_64_bit-Debug/resource/icon/\347\214\253\345\222\252.svg"), QSize(), QIcon::Normal, QIcon::Off);
        Start->setWindowIcon(icon);
        pushButton_2 = new QPushButton(Start);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setGeometry(QRect(510, 580, 300, 130));
        QFont font;
        font.setPointSize(36);
        pushButton_2->setFont(font);
        label = new QLabel(Start);
        label->setObjectName("label");
        label->setGeometry(QRect(380, 10, 751, 271));
        pushButton_1 = new QPushButton(Start);
        pushButton_1->setObjectName("pushButton_1");
        pushButton_1->setGeometry(QRect(510, 300, 300, 130));
        pushButton_1->setFont(font);
        background = new QLabel(Start);
        background->setObjectName("background");
        background->setGeometry(QRect(0, 0, 1380, 720));
        pushButton_3 = new QPushButton(Start);
        pushButton_3->setObjectName("pushButton_3");
        pushButton_3->setGeometry(QRect(510, 440, 300, 130));
        pushButton_3->setFont(font);
        background->raise();
        pushButton_2->raise();
        label->raise();
        pushButton_1->raise();
        pushButton_3->raise();

        retranslateUi(Start);

        QMetaObject::connectSlotsByName(Start);
    } // setupUi

    void retranslateUi(QWidget *Start)
    {
        Start->setWindowTitle(QCoreApplication::translate("Start", "\345\274\200\345\247\213\347\225\214\351\235\242", nullptr));
        pushButton_2->setText(QCoreApplication::translate("Start", "\351\200\200\345\207\272\346\270\270\346\210\217", nullptr));
        label->setText(QCoreApplication::translate("Start", "image", nullptr));
        pushButton_1->setText(QCoreApplication::translate("Start", "\345\257\271\346\210\230\346\250\241\345\274\217", nullptr));
        background->setText(QCoreApplication::translate("Start", "TextLabel", nullptr));
        pushButton_3->setText(QCoreApplication::translate("Start", "\345\206\222\351\231\251\346\250\241\345\274\217", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Start: public Ui_Start {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_START_H
