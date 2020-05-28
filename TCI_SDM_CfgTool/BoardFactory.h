#ifndef BOARDFACTORY_H
#define BOARDFACTORY_H
#include "BoardDefine.h"
#include "CodeTable.h"

class BoardFactory
{
public:
    BoardFactory();

public:
    static BoardBase* CreateBoard(EBoradType board_type);

    static BoardBase *CreateBoard(const BoardInfo *board_info);

    static EBoradType GetBoardType(const QString& board_name);
};

#endif // BOARDFACTORY_H
