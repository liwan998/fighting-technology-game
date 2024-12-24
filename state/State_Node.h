#ifndef STATE_NODE_H
#define STATE_NODE_H

class State_Node
{
public:
    State_Node()=default;
    ~State_Node()=default;

    virtual void on_enter() {};
    virtual void on_update(float delta) {};
    virtual void on_exit() {};

};

#endif // STATE_NODE_H
