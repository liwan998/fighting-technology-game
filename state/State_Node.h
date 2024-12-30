#ifndef STATE_NODE_H
#define STATE_NODE_H
#include<QObject>

class State_Node:public QObject
{
    Q_OBJECT
public:
    explicit State_Node(QObject *parent = nullptr):QObject{parent}{}
    ~State_Node()=default;

    virtual void on_enter() {};
    virtual void on_update(float delta) {};
    virtual void on_exit() {};

};

#endif // STATE_NODE_H
