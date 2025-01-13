#ifndef GAME_H
#define GAME_H

#include "screen.h"
#include "timer.h"
#include <QWidget>
#include<QTimer>
#include<QPainter>
#include<mutex>
QT_BEGIN_NAMESPACE

class Timer;
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Game : public Screen
{
    Q_OBJECT

public:
    Game(QWidget *parent = nullptr);
    ~Game();
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

    std::mutex mutexBulletUpdate;
    std::mutex mutexTextUpdate;
private:
    QPainter painter;
    QImage *background=nullptr;
    const float timer=0.016;

private:
    Ui::Widget *ui;
};
#endif // GAME_H
