#include "interface_manager.h"
#include"start.h"
#include"select.h"
#include"select_venture.h"
#include"widget.h"
#include<QDebug>

Interface_manager* Interface_manager::manager=nullptr;
std::mutex Interface_manager::m_mutex;

Interface_manager::Interface_manager()
{
    list[Interface_manager::Interface::start]=new Start();
    list[Interface_manager::Interface::start]->setFixedSize(1380,720);
    list[Interface_manager::Interface::select]=new Select();
    list[Interface_manager::Interface::select]->setFixedSize(1380,720);
    list[Interface_manager::Interface::select_venture]=new Select_venture();
    list[Interface_manager::Interface::select_venture]->setFixedSize(1380,720);
    list[Interface_manager::Interface::game]=new Widget();
    list[Interface_manager::Interface::game]->setFixedSize(1380,720);
}
Interface_manager::~Interface_manager()
{
    for(auto i:list){
        delete i.second;
    }
}

Interface_manager *Interface_manager::instance()
{
    std::unique_lock<std::mutex>m_mutex;
    if(!manager){
        manager=new Interface_manager();
    }
    return manager;

}

void Interface_manager::switch_to(Interface interface)
{
    if(interface==Interface_manager::Interface::over){
        exit();
        return;
    }
    if (list.find(interface) != list.end()) {
        QPoint position=list[get_interface()]->pos();   //让窗口位置一致
        if (list[interface] != list[get_interface()]) {// 隐藏当前显示的界面
            list[get_interface()]->hide();
        }
        list[interface]->move(position);
        list[interface]->on_enter();
        list[this->interface]->on_exit();
        list[interface]->show();// 显示新的界面
        this->interface = interface;// 更新当前界面状态
    } else {
        qDebug() << "在列表中未找到界面";
    }
}

Interface_manager::Interface Interface_manager::get_interface()
{
    return interface;
}

Select *Interface_manager::get_select_widget()
{
    return (Select*)list[Interface_manager::Interface::select];
}

void Interface_manager::enter()
{
    list[Interface_manager::Interface::start]->on_enter();
    list[Interface_manager::Interface::start]->show();
}

void Interface_manager::exit()
{
    for(auto i:list){
        i.second->close();
    }
}
