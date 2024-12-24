#ifndef START_H
#define START_H

#include "screen.h"

#include <QWidget>

namespace Ui {
class Start;
}

class Start : public Screen
{
    Q_OBJECT

public:
    explicit Start(QWidget *parent = nullptr);
    ~Start();
    void on_enter()override;
    void on_exit()override;

private slots:
    void on_pushButton_1_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::Start *ui;
};

#endif // START_H
