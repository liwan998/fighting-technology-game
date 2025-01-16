#ifndef LEVELS_BASE_H
#define LEVELS_BASE_H

#include <QWidget>
#include <qpainter.h>
#include <mutex>
#include"timer.h"

class QProgressBar;
class QTimer;
class QMediaPlayer;
class QPainter;

class Levels_Base : public QWidget
{
    Q_OBJECT
public:
    explicit Levels_Base(QWidget *parent = nullptr);
    ~Levels_Base()=default;

public:
    virtual void on_enter();
    virtual void on_exit();

protected:
    virtual void on_update(float date);

protected:
    virtual void paintEvent(QPaintEvent *event) override;//画图事件更新函数
    void keyPressEvent(QKeyEvent *event)override;//按下按键
    void keyReleaseEvent(QKeyEvent *event)override;//抬起按键
signals:
    void game_over(bool isP1Win);
protected:
    QImage *background=nullptr;
    QProgressBar *P1HealthBar=nullptr;
    QProgressBar *P2HealthBar=nullptr;
    QTimer *timerFrameInterval60=nullptr;
    QMediaPlayer *background_music=nullptr;
    QPainter painter;
    Timer timer_dead;
    bool is_dead=false;

    std::mutex mutexBulletUpdate;
    std::mutex mutexTextUpdate;
    std::mutex mutexProcessCollide;
};

#endif // LEVELS_BASE_H
