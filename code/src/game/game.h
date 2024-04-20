#ifndef GAME_H
#define GAME_H
#include "chessboard.h"
#include "pieces.h"
#include <memory>

class Game
{
public:
    static Game &instance(){static Game instance; return instance;}
    void init();
    void onClickPieces();
    void onClickBoard();

private:
    Game(/* args */);
    ~Game();

    bool m_init = false;
    chessBoard m_board;

};

#define sGame Game::instance()

#endif //GAME_H