#ifndef SELECT_H
#define SELECT_H

#include <QWidget>
#include<QTimer>
#include "screen.h"
#include"animation.h"
#include"unordered_map"

namespace Ui {
class Select;
}

class Select : public Screen
{
    Q_OBJECT

public:
    explicit Select(QWidget *parent = nullptr);
    ~Select();
    void on_enter()override;
    void on_exit()override;

    int getPlayer1_select() const;

    int getPlayer2_select() const;

    int getPlayer_num() const;

private slots:
    void on_btn_player1_last_clicked();

    void on_btn_player1_next_clicked();

    void on_btn_player2_last_clicked();

    void on_btn_player2_next_clicked();

    void on_btn_start_clicked();

    void on_btn_over_clicked();

    void on_btn_return_home_clicked();

private:
    const int player_num=3;//当前角色数量
    const int ai_num=2;     //ai角色数量

private:
    Ui::Select *ui;

    QTimer timer;

    Animation *current_player1_animation=nullptr;
    Animation *current_player2_animation=nullptr;

    int player1_select=0;
    int player2_select=0;

    std::unordered_map<int,Animation> animation_pool;
};

#endif // SELECT_H
