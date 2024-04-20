#ifndef CHESSBOARD_H
#define CHESSBOARD_H
#include "image/image.h"
#include "page.h"

class chessBoard : public page
{
public:
    chessBoard(/* args */);
    ~chessBoard();
    void init();
    void onClick() override;

private:
    Image m_img;
};

#endif //CHESSBOARD_H