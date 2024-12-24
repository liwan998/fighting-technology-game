#ifndef CHARACTER_MANAGER_H
#define CHARACTER_MANAGER_H

#include <QObject>
#include"character.h"
#include<QPainter>
#include<mutex>

class Character_Manager : public QObject
{
    Q_OBJECT
public:
    static Character_Manager* instance();

    Character* get_player() {
        return player;
    }
    Character* get_player2(){
        return player2;
    }

    void key_Press(QKeyEvent& event);
    void key_Release(QKeyEvent& event);

    void on_update(float delta);
    void on_render(QPainter &painter);
    void on_enter();
    void on_exit();


private:
    std::mutex mtx_update1;
    std::mutex mtx_update2;

private:
    static Character_Manager* manager;
    Character* player=nullptr;
    Character* player2=nullptr;


private:
    Character_Manager();
    ~Character_Manager();
};

#endif // CHARACTER_MANAGER_H
