#ifndef INTERFACE_MANAGER_H
#define INTERFACE_MANAGER_H

#include"screen.h"
#include <QObject>
#include<mutex>
#include"select.h"
class QMediaPlayer;
class Interface_manager : public QObject
{
    Q_OBJECT
public:
    static Interface_manager *instance();
    enum class Interface{
        start=0,
        select,
        select_venture,
        game,
        levels_1,
        levels_2,
        levels_3,
        levels_4,
        over
    };
    void switch_to(Interface interface);//界面跳转
    Interface get_interface();
    Select* get_select_widget();
    void enter();
    void exit();

private:
    Interface_manager();
    ~Interface_manager();

private:
    static Interface_manager* manager;
    static std::mutex m_mutex;
    Interface interface=Interface_manager::Interface::start;
    std::unordered_map<Interface,Screen*> list;    //界面容器
};

#endif // INTERFACE_MANAGER_H
