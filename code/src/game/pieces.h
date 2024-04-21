#ifndef PIECES_H
#define PIECES_H
#include "page.h"

enum Factions
{
    Red = 0,
    Black = 1,
};

enum PiecesState
{
    PiecesState_Normal = 0,
    PiecesState_Selecting = 1,
    PiecesState_Died = 2,
};

class pieces  : public page
{
public:
    pieces(PiecesType type);
    ~pieces();
    void init();
    void onClick(pos position) override;

    Factions getFactions(){ return m_faction;}
    static bool select(pieces *piece);
    bool move(pos position);
    bool eat(pieces *piece);
    void die();

    static pieces *s_selected;
private:
    void moveToPosisiton(pos position);

    PiecesType m_type;//什么棋子
    Factions m_faction;//当前棋子属于哪个阵营
    PiecesState m_state;//当前棋子状态
    
};


#endif //PIECES_H