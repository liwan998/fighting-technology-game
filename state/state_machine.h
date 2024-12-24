#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H
#include"State_Node.h"
#include <string>
#include<unordered_map>
class State_Machine
{
public:
    State_Machine();
    ~State_Machine();

    void on_update(float delta);

    void set_entry(const std::string& id);      //初始进入状态机节点
    void switch_to(const std::string& id);		//切换状态机状态
    void register_state(const std::string& id, State_Node* state_node);		//注册新的状态
    void extracted();
    void destroy_all_state_node(); // 销毁状态节点

private:
    bool need_init = true;  //是否需要初始化
    State_Node* current_state = nullptr;    //当前状态节点
    std::unordered_map<std::string, State_Node*>state_pool; //状态节点储存
};

#endif // STATE_MACHINE_H
