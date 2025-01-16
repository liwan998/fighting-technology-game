#include "character_manager.h"

#include"player_pirate.h"
#include"player_queen.h"

#include"enemy_pirate.h"
#include"enemy_queen.h"

#include"player_jinbei.h"
#include"enemy_jinbei.h"

#include"player_baby.h"
#include"enemy_baby.h"

#include"thread_pool.h"

Character_Manager* Character_Manager::manager = nullptr;
std::mutex Character_Manager::m_mutex;

Character_Manager* Character_Manager::instance()
{
    std::unique_lock<std::mutex>m_mutex;
    if (!manager) {
        manager = new Character_Manager();
    }
    return manager;
}

void Character_Manager::key_Press(QKeyEvent& event){
    player->key_Press(event);
    player2->key_Press(event);
}
void Character_Manager::key_Release(QKeyEvent& event){

    player->key_Release(event);
    player2->key_Release(event);
}

void Character_Manager::on_update(float delta)
{
    auto thread_pool=Thread_Pool::instance();
    thread_pool->add_task(2,[&,delta](){
        std::unique_lock<std::mutex> lock(mtx_update1);
        player->on_update(delta);
    });
    thread_pool->add_task(2,[&,delta](){
        std::unique_lock<std::mutex> lock(mtx_update2);
        player2->on_update(delta);
    });
}

void Character_Manager::on_render(QPainter &painter)
{
    player->on_render(painter);
    player2->on_render(painter);
}

void Character_Manager::on_enter(int player1_select,int player2_select)
{
    if(player){
        delete player;
    }
    if(player2){
        delete player2;
    }
    switch (player1_select) {
    case 0:
        player =new Player_pirate(Player::Player_select::left);
        break;
    case 1:
        player=new Player_queen(Player::Player_select::left);
        break;
    case 2:
        player=new Player_Jinbei(Player::Player_select::left);
        break;
    case 3:
        player=new Player_Baby(Player::Player_select::left);
        break;
    default:
        break;
    }
    switch (player2_select) {
    case 0:
        player2 =new Player_pirate(Player::Player_select::right);
        break;
    case 1:
        player2=new Player_queen(Player::Player_select::right);
        break;
    case 2:
        player2=new Player_Jinbei(Player::Player_select::right);
        break;
    case 3:
        player2=new Player_Baby(Player::Player_select::right);
        break;
    case 4:
        player2=new Enemy_pirate();
        break;
    case 5:
        player2=new Enemy_queen();
        break;
    case 6:
        player2=new Enemy_Jinbei();
        break;
    case 7:
        player2=new Enemy_Baby();
        break;
    default:
        break;
    }
}

void Character_Manager::on_exit()
{
    Thread_Pool::instance()->stop();
    if(player){
        delete player;
    }
    if(player2){
        delete player2;
    }
}


Character_Manager::Character_Manager()
{
    player =new Player_pirate(Player::Player_select::left);
    player2 =new Player_pirate(Player::Player_select::right);
}

Character_Manager::~Character_Manager()
{
    if(player){
        delete player;
    }
    if(player2){
        delete player2;
    }

}
