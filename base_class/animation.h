#ifndef ANIMATION_H
#define ANIMATION_H

#include"atlas.h"
#include"timer.h"
#include<QPoint>
#include<QVector>
#include<QRect>
#include<QPainter>

class Animation
{
public:
    explicit Animation();
    ~Animation();

private:
    struct Frame {
        QRect rect_src;
        QImage* image = nullptr;
        Frame() = default;
        Frame(QImage* image, const QRect& rect_src) :image(image), rect_src(rect_src) {};
        ~Frame() = default;
    };

public:
    void reset();
    void set_position(QPointF position);
    void set_is_loop(bool is_loop);
    void set_interval(float interval);
    void set_on_finished(std::function<void()>on_finished);
    void setIs_box(bool newIs_box);
    QImage* get_current_image();


public:
    void add_fram(Atlas *atlas);

    void on_render(QPainter &painter);
    void on_update(float delta);

private:
    Timer timer;
    QPointF position;
    bool is_loop=true;                              //是否循环播放
    bool is_box=false;                                    //调试框
    size_t idx_frame=0;                             //当前动画帧索引
    QVector<Frame>frame_list;                        //储存的帧动画
    std::function<void()> on_finished;              //动画结束后处理
};

#endif // ANIMATION_H
