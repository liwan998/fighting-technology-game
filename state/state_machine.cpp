#include "state_machine.h"
#include<vector>
State_Machine::State_Machine()
{

}

State_Machine::~State_Machine()
{
    destroy_all_state_node();
}

void State_Machine::on_update(float delta)
{
    if (!current_state) return;
    if (need_init) {
        current_state->on_enter();
        need_init = false;
    }
    current_state->on_update(delta);
}

void State_Machine::set_entry(const std::string &id)
{
    current_state = state_pool[id];
}

void State_Machine::switch_to(const std::string &id)
{
    if (current_state) current_state->on_exit();
    current_state = state_pool[id];
    if (current_state) current_state->on_enter();
}

void State_Machine::register_state(const std::string &id, State_Node *state_node)
{
    state_pool[id] = state_node;
}

void State_Machine::destroy_all_state_node()
{

    //在遍历std::unordered_map时，删除元素会导致迭代器失效。在C++标准库中，
    // 当你删除一个元素后，std::unordered_map的迭代器可能会失效（特别是对于std::unordered_map，删除操作可能会导致rehash）。
    // 这意味着当你删除一个元素后，你不能继续使用同一个迭代器来访问后续的元素。

    std::vector<std::string> keys_to_delete;

    for (const auto& state : state_pool) {
        if (state.second != nullptr) {
            keys_to_delete.push_back(state.first);
        }
    }

    for (const auto& key : keys_to_delete) {
        auto it = state_pool.find(key);
        if (it != state_pool.end() && it->second != nullptr) {
            delete it->second;
            state_pool.erase(it);
        }
    }

}
