#ifndef FLOATING_TEXT_H
#define FLOATING_TEXT_H

#include <QObject>
#include <QPainter>
#include <QPointF>
#include <QColor>
class Floating_Text : public QObject
{
    Q_OBJECT
public:
    explicit Floating_Text(const QString& text, const QPointF& position,QObject *parent = nullptr);
    ~Floating_Text()=default;

public:
    void on_update(float delta); // 更新文本状态
    void on_render(QPainter& painter); // 绘制文本

    bool isValid();

    void setColor(const QColor& color);
    void setFloatSpeed(float speed);
    void setShrinkSpeed(float speed);
    void setFontSize(float size);

private:
    QString text; // 显示的文本
    QPointF position; // 文本的初始位置
    QColor color; // 文本颜色
    float fontSize; // 字体大小
    float alpha; // 文本透明度
    float floatSpeed; // 上浮速度
    float shrinkSpeed; // 字体缩小速度
    float fadeSpeed; // 透明度减少速度
    bool is_valid; // 动画是否有效
};

#endif // FLOATING_TEXT_H
