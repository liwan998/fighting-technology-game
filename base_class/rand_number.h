#ifndef RAND_NUMBER_H
#define RAND_NUMBER_H

#include<mutex>

class Rand_number
{
public:
    static Rand_number* instance();
    int randomInt(int min,int max);
    float randomFloat(float min,float max);

private:
    Rand_number()=default;
    ~Rand_number()=default;

private:
    static Rand_number* manager;
    static std::mutex m_mutex;
};

#endif // RAND_NUMBER_H
