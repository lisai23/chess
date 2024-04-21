#include "pieces.h"
#include "game.h"
#include "log.h"
#include "rules.h"
#include "rules.cpp"

pieces *pieces::s_selected = nullptr;

pieces::pieces(PiecesType m_type)
    :m_state(PiecesState_Normal), m_type(m_type)
{
    if (m_type > PiecesType_bing_red)
    {
        m_faction = Black;
    }
    else
    {
        m_faction = Red;
    }
}

pieces::~pieces()
{
}

void pieces::init()
{
    
}

void pieces::onClick(pos position)
{
    sGame.onClickPieces(this);
}

bool pieces::select(pieces *piece)
{
    bool ret = false;
    if (nullptr != piece)
    {
        if (PiecesState_Selecting == piece->m_state)
        {
            piece->m_state = PiecesState_Normal;
            piece->flash(false);
            s_selected = nullptr;
        }
        else if (PiecesState_Normal == piece->m_state)
        {
            piece->m_state = PiecesState_Selecting;
            piece->flash(true);
            s_selected = piece;
            ret = true;
        }
        else
        {
            Debug_log("the piece is died, can not select");
        }
        
    }
    else
    {
        Debug_log("piece is nullptr");
    }

    return ret;
}

bool pieces::move(pos position)
{
    bool ret = false;
    if (rules(m_type).move(this->m_pos,position))
    {
        this->moveToPosisiton(position);
        ret = true;
    }
    return ret;
}

bool pieces::eat(pieces *piece)
{
    bool ret = false;
    if (nullptr == piece)
    {
        Debug_log("piece is nullptr");
        return false;
    }

    pos des_pos = piece->m_pos;
    if (rules(m_type).move(this->m_pos,piece->m_pos))
    {
        piece->die();
        this->moveToPosisiton(des_pos);
        ret = true;
    }
    
    return ret;
}

void pieces::die()
{
    close();
    chessBoard::deletPieces(this);
}

void pieces::moveToPosisiton(pos position)
{
    chessBoard::movePieces(this,position);
}
