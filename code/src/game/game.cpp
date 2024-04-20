#include "game.h"
#include "log.h"
#include "chessboard.h"

void Game::init()
{
    m_init = true;
    page::initPageMap();
    m_board.init();
}

void Game::onClickPieces()
{
}

void Game::onClickBoard()
{
    Debug_log("onClickBoard");
}

Game::Game(/* args */)
{
}

Game::~Game()
{
}