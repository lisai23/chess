#include "chessboard.h"
#include "game.h"

chessBoard::chessBoard(/* args */)
{
}

chessBoard::~chessBoard()
{
}

void chessBoard::init()
{
    setRect(480,480);
    open();
}

void chessBoard::onClick()
{
    sGame.onClickBoard();
}