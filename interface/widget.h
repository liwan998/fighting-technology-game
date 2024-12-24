#ifndef WIDGET_H
#define WIDGET_H

#include "screen.h"
#include "timer.h"
#include <QWidget>
#include<QTimer>
#include<QPainter>
QT_BEGIN_NAMESPACE

class Timer;
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public Screen
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    void on_enter()override;
    void on_exit()override;

private slots:
    void time_60();
    void paintEvent(QPaintEvent *event)override;//画图事件更新函数
    void keyPressEvent(QKeyEvent *event)override;//按下按键
    void keyReleaseEvent(QKeyEvent *event)override;//抬起按键

private:
    QTimer timer60;     //帧间隔
    QTimer timer_game;  //游戏内倒计时
    Timer timer_dead;
    bool is_dead=false;
private:
    QPainter painter;
    QImage *background=nullptr;

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
