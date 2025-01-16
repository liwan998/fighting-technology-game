#include "screen.h"
#include<QMediaPlayer>
Screen::Screen(QWidget *parent)
    : QWidget{parent}
{}

Screen::~Screen()
{

}

void Screen::on_enter()
{
    background_music->play();
}

void Screen::on_exit()
{
    background_music->stop();
}
