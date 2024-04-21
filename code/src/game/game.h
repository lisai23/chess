#ifndef GAME_H
#define GAME_H
#include "chessboard.h"
#include "pieces.h"
#include <memory>

enum GameState
{
    Steped = 0,
    Selecting = 1,
};

class Game
{
public:
    static Game &instance(){static Game instance; return instance;}
    void init();
    void onClickPieces(pieces *piece);
    void onClickBoard(pos position);


private:
    Game(/* args */);
    ~Game();
    void switchFaction();

    bool m_init = false;
    chessBoard m_board;

    GameState m_state;
    Factions m_currentFaction;
};

#define sGame Game::instance()

#endif //GAME_H