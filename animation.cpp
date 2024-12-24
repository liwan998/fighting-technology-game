#include "animation.h"
#include<QPainter>

Animation::Animation(QObject *parent)
    : QObject{parent}
{
    timer.set_one_shot(false);
    timer.set_on_timeout(
        [&]() {
            idx_frame++;
            if (idx_frame >= frame_list.size()) {
                idx_frame = is_loop ? 0 : frame_list.size() - 1;
                if (!is_loop && on_finished) {
                    on_finished();
                }
            }
        }
        );
}

Animation::~Animation()
{
}

void Animation::reset()// 重置动画到第一帧
{
    timer.restart();
    idx_frame = 0;
}

void Animation::set_position(QPointF position)
{
    this->position=position;
}

void Animation::set_is_loop(bool is_loop)   //是否循环播放
{
    this->is_loop=is_loop;
}

void Animation::set_interval(float interval)// 设置动画帧间隔时间
{
    timer.set_wait_time(interval);
}

void Animation::set_on_finished(std::function<void ()> on_finished)// 设置动画结束时的回调函数
{
    this->on_finished = on_finished;
}

void Animation::add_fram(Atlas *atlas)
{
    for (int i = 0; i < atlas->get_size(); i++) {
        QImage* image = atlas->get_image(i);
        int width = image->width();
        int heigth = image->height();
        QRect rect_src;
        rect_src.setWidth(width), rect_src.setHeight(heigth);
        rect_src.setX(0), rect_src.setY(0);
        frame_list.push_back({image, rect_src});
    }
}

void Animation::on_render(QPainter &painter)
{
    painter.drawImage(position,*frame_list[idx_frame].image);//画图
    if(is_box){
        QPen pen;
        pen.setColor(Qt::yellow);
        painter.setPen(pen);
        painter.drawRect(position.x(),position.y(),
            frame_list[idx_frame].rect_src.width(),frame_list[idx_frame].rect_src.height());
    }
}

void Animation::on_update(float delta)
{
    timer.on_update(delta);
}


void Animation::setIs_box(bool newIs_box)
{
    is_box = newIs_box;
}

QImage *Animation::get_current_image()
{
    return frame_list[idx_frame].image;
}
