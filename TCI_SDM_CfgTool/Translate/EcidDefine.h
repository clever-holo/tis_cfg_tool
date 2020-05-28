#ifndef ECIDDEFINE_H
#define ECIDDEFINE_H

#include "BoardDefine.h"

class ECID
{
public:
    ECID(int order);

public:
    bool AddBoard(BoardBase* board);


    int Order() const;

private:
    void setOrder(int Order);

private:
    int m_Order;


    QVector<BoardBase*>     m_lstBoard;
};



#endif // ECIDDEFINE_H
