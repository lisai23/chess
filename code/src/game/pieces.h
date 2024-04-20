#ifndef PIECES_H
#define PIECES_H
#include "page.h"

class pieces  : public page
{
public:
    pieces(/* args */);
    ~pieces();

    void onClick() override;
private:
    /* data */
};


#endif //PIECES_H