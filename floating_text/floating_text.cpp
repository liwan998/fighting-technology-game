#include "floating_text.h"

Floating_Text::Floating_Text(const QString& text, const QPointF& position, QObject* parent)
    : QObject{parent},text(text), position(position), fontSize(24), alpha(255), floatSpeed(50.0f),
    shrinkSpeed(10.0f), fadeSpeed(100.0f), is_valid(true)
{
    color = QColor(255, 0, 0); // 默认红色
}

void Floating_Text::on_update(float delta)
{
    if(!is_valid){
        return;
    }

    position.setY(position.y() - floatSpeed * delta);// 上浮

    fontSize -= shrinkSpeed * delta;// 字体缩小
    if (fontSize < 10) fontSize = 10; // 最小字体大小

    alpha -= fadeSpeed * delta; // 透明度减少
    if (alpha < 0) alpha = 0;

    if (alpha <= 0) {
        is_valid = false;
    }
}

void Floating_Text::on_render(QPainter &painter)
{
    if(!is_valid){
        return;
    }

    QFont font = painter.font();// 设置字体
    font.setPointSizeF(fontSize);
    painter.setFont(font);

    QColor textColor = color;// 设置颜色和透明度
    textColor.setAlpha(alpha);
    painter.setPen(textColor);

    painter.drawText(position, text);
}

bool Floating_Text::isValid()
{
    return is_valid;
}

void Floating_Text::setColor(const QColor &color)
{
    this->color = color;
}

void Floating_Text::setFloatSpeed(float speed)
{
    this->floatSpeed = speed;
}

void Floating_Text::setShrinkSpeed(float speed)
{
    this->shrinkSpeed = speed;
}

void Floating_Text::setFontSize(float size)
{
    this->fontSize = size;
}
