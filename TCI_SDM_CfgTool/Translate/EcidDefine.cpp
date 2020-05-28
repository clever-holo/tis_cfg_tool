#include "EcidDefine.h"



ECID::ECID(int order)
{
   setOrder(order);
}

bool ECID::AddBoard(BoardBase *board)
{
    m_lstBoard.push_back(board);
    return true;
}

int ECID::Order() const
{
    return m_Order;
}

void ECID::setOrder(int Order)
{
    m_Order = Order;
}
