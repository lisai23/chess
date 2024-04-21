#include "chessboard.h"
#include "game.h"
#include <vector>
#include <utility>

std::map<pos,std::shared_ptr<pieces>> chessBoard::s_pieceMap = {};

static std::vector<std::pair<PiecesType,pos>> s_pieceVector
{
    {PiecesType_ju_black,{0,0,CHESS_POS}},
    {PiecesType_ma_black,{1,0,CHESS_POS}},
    {PiecesType_xiang_black,{2,0,CHESS_POS}},
    {PiecesType_shi_black,{3,0,CHESS_POS}},
    {PiecesType_jiang_black,{4,0,CHESS_POS}},
    {PiecesType_shi_black,{5,0,CHESS_POS}},
    {PiecesType_xiang_black,{6,0,CHESS_POS}},
    {PiecesType_ma_black,{7,0,CHESS_POS}},
    {PiecesType_ju_black,{8,0,CHESS_POS}},
    {PiecesType_pao_black,{1,2,CHESS_POS}},
    {PiecesType_pao_black,{7,2,CHESS_POS}},
    {PiecesType_zu_black,{0,3,CHESS_POS}},
    {PiecesType_zu_black,{2,3,CHESS_POS}},
    {PiecesType_zu_black,{4,3,CHESS_POS}},
    {PiecesType_zu_black,{6,3,CHESS_POS}},
    {PiecesType_zu_black,{8,3,CHESS_POS}},

    {PiecesType_ju_red,{0,9,CHESS_POS}},
    {PiecesType_ma_red,{1,9,CHESS_POS}},
    {PiecesType_xiang_red,{2,9,CHESS_POS}},
    {PiecesType_shi_red,{3,9,CHESS_POS}},
    {PiecesType_shuai_red,{4,9,CHESS_POS}},
    {PiecesType_shi_red,{5,9,CHESS_POS}},
    {PiecesType_xiang_red,{6,9,CHESS_POS}},
    {PiecesType_ma_red,{7,9,CHESS_POS}},
    {PiecesType_ju_red,{8,9,CHESS_POS}},
    {PiecesType_pao_red,{1,7,CHESS_POS}},
    {PiecesType_pao_red,{7,7,CHESS_POS}},
    {PiecesType_bing_red,{0,6,CHESS_POS}},
    {PiecesType_bing_red,{2,6,CHESS_POS}},
    {PiecesType_bing_red,{4,6,CHESS_POS}},
    {PiecesType_bing_red,{6,6,CHESS_POS}},
    {PiecesType_bing_red,{8,6,CHESS_POS}},
};

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
    putPieceOnBoard();
}

void chessBoard::onClick(pos position)
{
    position.switchChessPos();
    sGame.onClickBoard(position);
}

std::shared_ptr<pieces> chessBoard::getPieceOnBoard(pos position)
{
    return s_pieceMap[position];
}

void chessBoard::putPieceOnBoard()
{
    for (auto it = s_pieceVector.begin(); it != s_pieceVector.end(); it++)
    {
        s_pieceMap[it->second] = std::make_shared<pieces>(it->first);
        s_pieceMap[it->second]->init();
    }
}

void chessBoard::movePieces(pieces *piece, pos position)
{
    pos src_pos = piece->getPos();
    s_pieceMap[position] = s_pieceMap[src_pos];
    s_pieceMap[src_pos].reset();
}

void chessBoard::deletPieces(pieces *piece)
{
    pos src_pos = piece->getPos();
    s_pieceMap[src_pos].reset();
}
