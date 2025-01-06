#include"resources_manager.h"
#include"interface_manager.h"
#include"sound_manager.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Resources_manager::instance()->load();
    Sound_manager::instance()->load();

    Interface_manager::instance()->enter();

    return a.exec();
}
