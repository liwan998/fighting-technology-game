#include"resources_manager.h"
#include"interface_manager.h"
#include"sound_manager.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    Resources_manager::instance()->load();
    Sound_manager::instance()->load();
    QApplication a(argc, argv);

    Interface_manager::instance()->enter();

    return a.exec();
}
