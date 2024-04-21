#include "game.h"
#include "log.h"
#include "chessboard.h"

void Game::init()
{
    m_init = true;
    page::initPageMap();
    m_board.init();
    m_state = Steped;
    m_currentFaction = Red;
}

void Game::onClickPieces(pieces *piece)
{
    Debug_log("onClickPieces m_state: %d", m_state);
    if (Steped == m_state)
    {
        if (piece->getFactions() == m_currentFaction)
        {
            if (true == pieces::select(piece)) //选择
            {
                m_state = Selecting;
            }
        }
        else
        {
            Debug_log("this is not your step!");
        }
    }
    else if (Selecting == m_state)
    {
        if (piece->getFactions() == m_currentFaction)
        {
            if (false == pieces::select(piece)) //取消选择
            {
                m_state = Steped;
            }
            else
            {
                //更换选择的棋子
            }
        }
        else
        {
            if (nullptr != pieces::s_selected)
            {
                if (pieces::s_selected->eat(piece))
                {
                    m_state = Steped;
                    switchFaction();
                }
            }
            else
            {
                Debug_log("state error: no piece is selected");
            }
        }
    }
    else
    {
        Debug_log("the state is not defined: %d!", m_state);
    }
    
}

void Game::onClickBoard(pos position)
{
    Debug_log("onClickBoard m_state: %d", m_state);
    if (Selecting == m_state)
    {
        if (nullptr != pieces::s_selected)
        {
            if (pieces::s_selected->move(position))
            {
                m_state = Steped;
                switchFaction();
            }
        }
        else
        {
            Debug_log("state error: no piece is selected");
        }  
    }
}

Game::Game(/* args */)
{
}

Game::~Game()
{
}

void Game::switchFaction()
{
    if (Red == m_currentFaction)
    {
        m_currentFaction = Black;
    }
    else
    {
        m_currentFaction = Red;
    }
    
}
