#ifndef FLOATING_TEXT_MANAGER_H
#define FLOATING_TEXT_MANAGER_H

#include "floating_text.h"
#include <QList>
#include <QPainter>
#include <mutex>

class Floating_Text_Manager
{
public:
    // 获取单例实例
    static Floating_Text_Manager* instance();

    void createDefaultText(const QString& text, const QPointF& position);// 创建默认浮动文本
    void createColoredText(const QString& text, const QPointF& position, const QColor& color);// 创建带有自定义颜色的浮动文本
    void createCustomText(const QString& text, const QPointF& position, float floatSpeed, float shrinkSpeed, float fontSize);// 创建带有自定义速度和字体大小的浮动文本

    void on_update(float delta);
    void on_render(QPainter& painter);

private:
    Floating_Text_Manager();
    ~Floating_Text_Manager();

    // 禁用拷贝构造函数和赋值运算符
    Floating_Text_Manager(const Floating_Text_Manager&) = delete;
    Floating_Text_Manager& operator=(const Floating_Text_Manager&) = delete;

    static Floating_Text_Manager* manager; // 单例实例
    static std::mutex m_mutex; // 用于线程安全的互斥锁

    QList<Floating_Text*> floating_text_list; // 存储所有浮动文本对象
};

#endif // FLOATING_TEXT_MANAGER_H
