#ifndef RULES_H
#define RULES_H
#include "define.h"
#include <memory>

class regulation
{
public:
    regulation(/* args */){}
    virtual ~regulation(){}
    virtual bool move(pos src_pos, pos des_pos) = 0;
};

class rule_jiang : public regulation
{
public:
    rule_jiang(/* args */){}
    ~rule_jiang(){}

    bool move(pos src_pos, pos des_pos) override;
};

class rule_shi : public regulation
{
public:
    rule_shi(/* args */){}
    ~rule_shi(){}

    bool move(pos src_pos, pos des_pos) override;
};

class rule_xiang : public regulation
{
public:
    rule_xiang(/* args */){}
    ~rule_xiang(){}

    bool move(pos src_pos, pos des_pos) override;
};

class rule_ma : public regulation
{
public:
    rule_ma(/* args */){}
    ~rule_ma(){}

    bool move(pos src_pos, pos des_pos) override;
};

class rule_ju : public regulation
{
public:
    rule_ju(/* args */){}
    ~rule_ju(){}

    bool move(pos src_pos, pos des_pos) override;
};

class rule_pao : public regulation
{
public:
    rule_pao(/* args */){}
    ~rule_pao(){}

    bool move(pos src_pos, pos des_pos) override;
};

class rule_bing : public regulation
{
public:
    rule_bing(/* args */){}
    ~rule_bing(){}

    bool move(pos src_pos, pos des_pos) override;
};



class rules
{
public:
    rules(PiecesType type);
    ~rules();

    bool move(pos src_pos, pos des_pos);
private:
    std::shared_ptr<regulation> m_reg;
};


#endif //RULES_H