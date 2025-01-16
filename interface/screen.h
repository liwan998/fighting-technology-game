#ifndef SCREEN_H
#define SCREEN_H

#include <QWidget>

class QMediaPlayer;
class Screen : public QWidget
{
    Q_OBJECT
public:
    explicit Screen(QWidget *parent = nullptr);
    ~Screen();
public:
    virtual void on_enter();
    virtual void on_exit();

protected:
    QMediaPlayer *background_music=nullptr;
};

#endif // SCREEN_H
