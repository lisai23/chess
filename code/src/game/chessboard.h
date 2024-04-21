#ifndef CHESSBOARD_H
#define CHESSBOARD_H
#include "image/image.h"
#include "page.h"
#include "pieces.h"
#include <memory>
#include <map>

class chessBoard : public page
{
public:
    chessBoard(/* args */);
    ~chessBoard();
    void init();
    void onClick(pos position) override;
    static std::shared_ptr<pieces> getPieceOnBoard(pos position); 
    static void movePieces(pieces *piece, pos position);
    static void deletPieces(pieces *piece);

private:
    void putPieceOnBoard();

    std::shared_ptr<Image> m_img;
    static std::map<pos,std::shared_ptr<pieces>> s_pieceMap;
};

#endif //CHESSBOARD_H