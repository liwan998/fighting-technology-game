#include "timer.h"

void Timer::restart() {
    pass_time = 0;
    shotted = false;
}
void Timer::set_wait_time(float val) {
    wait_time = val;
}
void Timer::set_one_shot(bool flag) {
    one_shot = flag;
}
void Timer::set_on_timeout(std::function<void()>on_timeout) {
    this->on_timeout = on_timeout;
}
void Timer::pause() {
    paused = true;
}
void Timer::resume() {
    paused = false;
}
void Timer::on_update(float delta) {
    if (paused)
        return;
    pass_time += delta;
    if (pass_time >= wait_time) {
        if ((!one_shot || (one_shot && !shotted)) && on_timeout) {
            on_timeout();
        }
        shotted = true;
        pass_time -=wait_time ;
    }
}
