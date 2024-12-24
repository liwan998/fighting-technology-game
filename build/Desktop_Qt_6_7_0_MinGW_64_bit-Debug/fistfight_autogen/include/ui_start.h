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
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Start
{
public:
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QLabel *label;

    void setupUi(QWidget *Start)
    {
        if (Start->objectName().isEmpty())
            Start->setObjectName("Start");
        Start->resize(1380, 720);
        pushButton = new QPushButton(Start);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(510, 350, 360, 150));
        QFont font;
        font.setPointSize(36);
        pushButton->setFont(font);
        pushButton_2 = new QPushButton(Start);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setGeometry(QRect(510, 540, 360, 150));
        pushButton_2->setFont(font);
        label = new QLabel(Start);
        label->setObjectName("label");
        label->setGeometry(QRect(320, 100, 751, 201));

        retranslateUi(Start);

        QMetaObject::connectSlotsByName(Start);
    } // setupUi

    void retranslateUi(QWidget *Start)
    {
        Start->setWindowTitle(QCoreApplication::translate("Start", "Form", nullptr));
        pushButton->setText(QCoreApplication::translate("Start", "\345\274\200\345\247\213\346\270\270\346\210\217", nullptr));
        pushButton_2->setText(QCoreApplication::translate("Start", "\345\274\200\345\247\213\346\270\270\346\210\217", nullptr));
        label->setText(QCoreApplication::translate("Start", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Start: public Ui_Start {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_START_H
