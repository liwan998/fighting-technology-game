#include "floating_text_manager.h"

Floating_Text_Manager* Floating_Text_Manager::manager = nullptr;
std::mutex Floating_Text_Manager::m_mutex;

Floating_Text_Manager* Floating_Text_Manager::instance()
{
    std::unique_lock<std::mutex>m_mutext; // 加锁，确保线程安全
    if (!manager) {
        manager = new Floating_Text_Manager();
    }
    return manager;
}

Floating_Text_Manager::Floating_Text_Manager()
{
}

Floating_Text_Manager::~Floating_Text_Manager()
{
    // 销毁所有浮动文本对象
    for (auto* text : floating_text_list) {
        delete text;
    }
    floating_text_list.clear();
}

void Floating_Text_Manager::createDefaultText(const QString& text, const QPointF& position)
{
    Floating_Text* floatingText = new Floating_Text(text, position);
    floating_text_list.append(floatingText);
}

void Floating_Text_Manager::createColoredText(const QString& text, const QPointF& position, const QColor& color)
{
    Floating_Text* floatingText = new Floating_Text(text, position);
    floatingText->setColor(color);
    floating_text_list.append(floatingText);
}

void Floating_Text_Manager::createCustomText(const QString& text, const QPointF& position, float floatSpeed, float shrinkSpeed, float fontSize)
{
    Floating_Text* floatingText = new Floating_Text(text, position);
    floatingText->setFloatSpeed(floatSpeed);
    floatingText->setShrinkSpeed(shrinkSpeed);
    floatingText->setFontSize(fontSize);
    floating_text_list.append(floatingText);
}

void Floating_Text_Manager::on_update(float delta)
{
    for (int i = floating_text_list.size() - 1; i >= 0; --i) {
        Floating_Text* text = floating_text_list[i];
        text->on_update(delta);

        if (!text->isValid()) {
            delete text;
            floating_text_list.removeAt(i);
        }
    }
}

void Floating_Text_Manager::on_render(QPainter& painter)
{
    for (auto* text : floating_text_list) {
        text->on_render(painter);
    }
}
