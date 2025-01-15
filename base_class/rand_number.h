#ifndef RAND_NUMBER_H
#define RAND_NUMBER_H

#include <mutex>
#include <random>

class Rand_number
{
public:
    static Rand_number* instance();
    int randomInt(int min, int max);
    float randomFloat(float min, float max);

    // 删除拷贝构造函数和赋值运算符
    Rand_number(const Rand_number&) = delete;
    Rand_number& operator=(const Rand_number&) = delete;

private:
    Rand_number();
    ~Rand_number() = default;

private:
    static Rand_number* manager;
    static std::once_flag m_onceFlag;
    std::mt19937 gen;
};

#endif // RAND_NUMBER_H
