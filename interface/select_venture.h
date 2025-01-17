#ifndef SELECT_VENTURE_H
#define SELECT_VENTURE_H

#include <QWidget>
#include<QTimer>
#include"unordered_map"
#include"animation.h"
#include "screen.h"

namespace Ui {
class Select_venture;
}

class Select_venture : public Screen
{
    Q_OBJECT

public:
    explicit Select_venture(QWidget *parent = nullptr);
    ~Select_venture();
    void on_enter()override;
    void on_exit()override;

private slots:
    void on_btn_player_last_clicked();

    void on_btn_player_next_clicked();

    void on_btn_game_over_clicked();

    void on_btn_return_home_clicked();

    void on_btn_level_1_clicked();

    void on_btn_level_2_clicked();

    void on_btn_level_3_clicked();

    void on_btn_level_4_clicked();

private:
    const int player_num=4;//当前角色数量

private:
    Ui::Select_venture *ui;
    QTimer timer;
    Animation *current_player1_animation=nullptr;
    int player1_select=0;
    std::unordered_map<int,Animation> animation_pool;
};

#endif // SELECT_VENTURE_H
