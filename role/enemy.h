#ifndef ENEMY_H
#define ENEMY_H

#include "character.h"

class Enemy : public Character
{
    Q_OBJECT
public:
    explicit Enemy(QObject *parent = nullptr);
    ~Enemy()=default;

    void on_update(float delta)override;

protected:
    void load_state_node(const float attackWaitTime,const float skillWaitTime);
    void load_hit_box(const int &attack_single_damage,const int &skill_single_damage);

};

#endif // ENEMY_H
