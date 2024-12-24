#ifndef TIMER_H
#define TIMER_H
#include<functional>
class Timer
{
public:
    Timer() = default;
    ~Timer() = default;
    void restart();
    void set_wait_time(float val);
    void set_one_shot(bool flag);
    void set_on_timeout(std::function<void()>on_timeout);
    void pause();
    void resume();
    void on_update(float delta);
private:
    float pass_time = 0;			//已过时间
    float wait_time = 0;			//等待时间
    bool paused = false;		//是否暂停
    bool shotted = false;		//是否触发
    bool one_shot = false;		//单次触发
    std::function<void()>on_timeout;		//触发回调
};

#endif // TIMER_H
