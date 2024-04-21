#include "rules.h"
#include "chessboard.h"

rules::rules(PiecesType type)
{
    switch (type)
    {
    case PiecesType_shuai_red:
    {
        m_reg = std::make_shared<rule_jiang>();
        break;
    }
    case PiecesType_shi_red:
    {
        m_reg = std::make_shared<rule_shi>();
        break;
    }
    case PiecesType_xiang_red:
    {
        m_reg = std::make_shared<rule_xiang>();
        break;
    }
    case PiecesType_ma_red:
    {
        m_reg = std::make_shared<rule_ma>();
        break;
    }
    case PiecesType_ju_red:
    {
        m_reg = std::make_shared<rule_ju>();
        break;
    }
    case PiecesType_pao_red:
    {
        m_reg = std::make_shared<rule_pao>();
        break;
    }
    case PiecesType_bing_red:
    {
        m_reg = std::make_shared<rule_bing>();
        break;
    }
    case PiecesType_jiang_black:
    {
        m_reg = std::make_shared<rule_jiang>();
        break;
    }
    case PiecesType_shi_black:
    {
        m_reg = std::make_shared<rule_shi>();
        break;
    }
    case PiecesType_xiang_black:
    {
        m_reg = std::make_shared<rule_xiang>();
        break;
    }
    case PiecesType_ma_black:
    {
        m_reg = std::make_shared<rule_ma>();
        break;
    }
    case PiecesType_ju_black:
    {
        m_reg = std::make_shared<rule_ju>();
        break;
    }
    case PiecesType_pao_black:
    {
        m_reg = std::make_shared<rule_pao>();
        break;
    }
    case PiecesType_zu_black:
    {
        m_reg = std::make_shared<rule_bing>();
        break;
    }
    
    default:
        break;
    }
}

rules::~rules()
{
}

bool rules::move(pos src_pos, pos des_pos)
{
    bool ret = false;
    if (nullptr != m_reg.get())
    {
        ret = m_reg->move(src_pos, des_pos);
    }

    return ret;
}

bool rule_jiang::move(pos src_pos, pos des_pos)
{
    bool ret = false;
    if (src_pos.x < 3 || src_pos.x > 5 || src_pos.y < 0 || src_pos.y > 2)//自身不在九宫格内
    {
       ret = false;
    }

    if (des_pos.x < 3 || des_pos.x > 5 || des_pos.y < 0 || des_pos.y > 2)//要走出九宫格
    {
       ret = false;
    }

    if (src_pos.x != des_pos.x || src_pos.y != des_pos.y)//跳着走
    {
        ret = false;
    }

    //对将
    if (src_pos.y != des_pos.y)
    {
        for (size_t i = 0; i < CHESS_HEIGHT; i++)
        {
            pos position;
            position.x = des_pos.x;
            position.y = i;
            chessBoard::getPieceOnBoard(position);
        }
    }   
    
    //己方占用

    
    return ret;
}

bool rule_shi::move(pos src_pos, pos des_pos)
{
    return false;
}

bool rule_xiang::move(pos src_pos, pos des_pos)
{
    return false;
}

bool rule_ma::move(pos src_pos, pos des_pos)
{
    return false;
}

bool rule_ju::move(pos src_pos, pos des_pos)
{
    return false;
}

bool rule_pao::move(pos src_pos, pos des_pos)
{
    return false;
}

bool rule_bing::move(pos src_pos, pos des_pos)
{
    return false;
}
