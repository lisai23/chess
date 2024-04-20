#ifndef PIXEL_H
#define PIXEL_H
#include <stack>
#include <stdint.h>

class pixel
{
public:
    pixel(/* args */);
    ~pixel();
private:
    std::stack<uint32_t> m_stack;
};


#endif //PIXEL_H