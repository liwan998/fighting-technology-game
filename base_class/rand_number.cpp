#include "rand_number.h"
#include"random"

Rand_number* Rand_number::manager = nullptr;// 静态成员变量初始化
std::mutex Rand_number::m_mutex;

Rand_number *Rand_number::instance()
{
    std::unique_lock<std::mutex>m_mutex;
    if(!manager){
        manager=new Rand_number();
    }
    return manager;
}

int Rand_number::randomInt(int min, int max)
{
    std::random_device rd;  // 用于获取随机种子
    std::mt19937 gen(rd()); // Mersenne Twister 引擎
    std::uniform_int_distribution<> dis(min, max);// 定义分布范围 [min, max]
    int randomValue = dis(gen);// 生成随机整数
    return randomValue;
}

float Rand_number::randomFloat(float min, float max)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(min, max);
    double randomValue = dis(gen);
    return randomValue;
}
