#include "rand_number.h"

Rand_number* Rand_number::manager = nullptr;
std::once_flag Rand_number::m_onceFlag;

// 构造函数，初始化随机数引擎
Rand_number::Rand_number() : gen(std::random_device{}()) {}

Rand_number* Rand_number::instance()
{
    // 使用 std::call_once 确保单例对象只被初始化一次
    std::call_once(m_onceFlag, []() {
        manager = new Rand_number();
    });
    return manager;
}

// 生成指定范围内的随机整数
int Rand_number::randomInt(int min, int max)
{
    // 定义整数分布范围 [min, max]
    std::uniform_int_distribution<> dis(min, max);
    // 生成并返回随机整数
    return dis(gen);
}

// 生成指定范围内的随机浮点数
float Rand_number::randomFloat(float min, float max)
{
    // 定义浮点数分布范围 [min, max]
    std::uniform_real_distribution<> dis(min, max);
    // 生成随机浮点数并转换为 float 类型返回
    return static_cast<float>(dis(gen));
}
