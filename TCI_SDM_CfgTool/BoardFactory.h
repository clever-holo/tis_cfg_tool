#ifndef BOARDFACTORY_H
#define BOARDFACTORY_H

#include "BoardDefine.h"
#include "CodeTable.h"
#include "CsmDataDefine.h"

class BoardFactory
{
public:
    BoardFactory();

public:
    static BoardBase* CreateBoard(EBoradType board_type);

    static BoardBase *CreateBoard(const BoardInfo *board_info);

    static EBoradType GetBoardType(const QString& board_name);

    static void GetBoardInAndOut(EBoradType board_type, QVector<QString>& v_di, QVector<QString>& v_sbo);

    static void GetBoardMaxCode(EBoradType board_type, int &max_lamp, int &max_di, int &max_sbo);

    static int GetMaxLamp(EBoradType board_type);

    static int GetMaxDi(EBoradType board_type);

    static int GetMaxSbo(EBoradType board_type);

    static bool GetPanelLamp(EBoradType board_type, QVector<QString>& v_lamp);

    static int GetLampEnumType();

    static int GetViibSpecialEnumType();

    static CsmDevType GetBoardDevType(EBoradType board_type);

    static CsmDevType GetOtherDevType(EBoradType board_type);

    static QString GetCbiTypeName(EBoradType board_type);

    static int GetHdwPortCount(EBoradType board_type);
};

#endif // BOARDFACTORY_H
