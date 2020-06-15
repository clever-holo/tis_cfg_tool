#include "BoardFactory.h"
#include "TisCfgData.h"
#include "AdsVarCfg.h"
#include "PanelLampCfg.h"

#define DEF_ENUM_TYPE_PANEL_LAMP      17

#define DEF_ENUM_TYPE_VIIB_SPECIAL    16

struct BoardCodeSize
{
    EBoradType   _board_type;    // 板卡类型
    int          _max_lamp;      // 最大面板灯个数
    int          _max_di;        // 最大采集码位个数
    int          _max_sbo;       // 最大驱动码位个数
};

const BoardCodeSize c_board_code_size[] =
{
  {E_Board_EIOCOM ,      0,      0,      0 },
  {E_Board_VIIB   ,     32,     32,      0 },
  {E_Board_VOOB   ,     16,      0,     16 },
  {E_Board_SDDM   ,     16,     24,     24 },
  {E_Board_PDDM46 ,      8,      8,      8 },
  {E_Board_TCIM25 ,      8,     24,      0 },
  {E_Board_PDDM5  ,      8,      8,      8 },
  {E_Board_CDDM   ,     16,      8,     16 },
  {E_Board_SIOM   ,     12,      8,      8 },
  {E_Board_HIOM   ,      8,      8,      8 },
};

//*////////////////////////////////////////////////////////////////////
// BoardFactory

BoardFactory::BoardFactory()
{

}

BoardBase *BoardFactory::CreateBoard(EBoradType board_type)
{
    BoardBase* board = nullptr;
    switch(board_type)
    {
    case E_Board_EIOCOM :
        board = new EIOCOMBoard();
        break;

    case E_Board_VIIB :
        board = new VIIBBoard();
        break;

    case E_Board_VOOB :
        board = new VOOBBoard();
        break;

    case E_Board_SDDM :
        board = new SDDMBoard();
        break;

    case E_Board_PDDM46 :
        board = new PDDM46Board();
        break;

    case E_Board_TCIM25 :
        board = new TCIM25Board();
        break;

    case E_Board_PDDM5 :
        board = new PDDM5Board();
        break;

    case E_Board_CDDM :
        board = new CDDMBoard();
        break;

    case E_Board_SIOM :
        board = new SIOMBoard();
        break;
    case E_Board_HIOM :
        board = new HIOMBoard();
        break;
    default:
        break;
    }
    return board;
}

BoardBase *BoardFactory::CreateBoard( const BoardInfo* board_info)
{
    BoardBase* rs = CreateBoard(GetBoardType(board_info->_mpPort.firstKey()));
    if(rs)
        rs = rs->Init(board_info);
    return rs;
}

EBoradType BoardFactory::GetBoardType(const QString &board_name)
{
    if     (board_name.contains("EIOCOM"))      return E_Board_EIOCOM;
    else if(board_name.contains("VIIB"))        return E_Board_VIIB;
    else if(board_name.contains("VOOB"))        return E_Board_VOOB;
    else if(board_name.contains("SDDM"))        return E_Board_SDDM;
    else if(board_name.contains("PDDM46"))      return E_Board_PDDM46;
    else if(board_name.contains("TCIM"))        return E_Board_TCIM25;
    else if(board_name.contains("PDDM5"))       return E_Board_PDDM5;
    else if(board_name.contains("CDDM"))        return E_Board_CDDM;
    else if(board_name.contains("SIOM"))        return E_Board_SIOM;
    else if(board_name.contains("HIOM"))        return E_Board_HIOM;
    else                                        return E_Board_Unknow;
}

void BoardFactory::GetBoardInAndOut(EBoradType board_type, QVector<QString> &v_di, QVector<QString> &v_sbo)
{
    const CodeTableCfg *pCodeTable = TisCfgData::Ins()->GetCodeTableCfg();
    const  QMap<QString, BoardInOut>& inout = pCodeTable->GetInOut();

    QString mapKey = "";
    if     (board_type == E_Board_SDDM)     mapKey = "SDDM-2";
    else if(board_type == E_Board_PDDM46)   mapKey = "PDDM46-2";
    else if(board_type == E_Board_TCIM25)   mapKey = "TCIM-2";
    else if(board_type == E_Board_PDDM5)    mapKey = "PDDM5-2";
    else if(board_type == E_Board_SIOM)     mapKey = "SIOM-2";

    v_di = inout[mapKey]._output;
    v_sbo = inout[mapKey]._input;

    return;
}

void BoardFactory::GetBoardMaxCode(EBoradType board_type, int& max_lamp, int& max_di, int& max_sbo)
{
    int cnt = sizeof(c_board_code_size) / sizeof(BoardCodeSize);
    for(int i=0; i<cnt; i++)
    {
        const BoardCodeSize& var = c_board_code_size[i];
        if(var._board_type == board_type)
        {
            max_lamp = var._max_lamp;
            max_di   = var._max_di;
            max_sbo  = var._max_sbo;
            return;
        }
    }
    max_lamp = 0;
    max_di   = 0;
    max_sbo  = 0;
    return;
}

int BoardFactory::GetMaxLamp(EBoradType board_type)
{
    int max_lamp, max_di, max_sbo;
    GetBoardMaxCode(board_type, max_lamp, max_di, max_sbo);
    return max_lamp;
}

int BoardFactory::GetMaxDi(EBoradType board_type)
{
    int max_lamp, max_di, max_sbo;
    GetBoardMaxCode(board_type, max_lamp, max_di, max_sbo);
    return max_di;
}

int BoardFactory::GetMaxSbo(EBoradType board_type)
{
    int max_lamp, max_di, max_sbo;
    GetBoardMaxCode(board_type, max_lamp, max_di, max_sbo);
    return max_sbo;
}

bool BoardFactory::GetPanelLamp(EBoradType board_type, QVector<QString> &v_lamp)
{
    const PanelLampCfg* pCfg = TisCfgData::Ins()->GetPanelLampCfg();
    const QMap<QString, QVector<QString>>& mp_lamp = pCfg->GetPanelLamp();

    QString mapKey = "";
    if     (board_type == E_Board_SDDM)     mapKey = "SDDM";
    else if(board_type == E_Board_PDDM46)   mapKey = "PDDM46";
    else if(board_type == E_Board_TCIM25)   mapKey = "TCIM";
    else if(board_type == E_Board_PDDM5)    mapKey = "PDDM5";
    else if(board_type == E_Board_SIOM)     mapKey = "SIOM";
    else if(board_type == E_Board_VIIB)     mapKey = "VIIB";
    else if(board_type == E_Board_VOOB)     mapKey = "VOOB";
    else if(board_type == E_Board_HIOM)     mapKey = "HIOM";
    else if(board_type == E_Board_CDDM)     mapKey = "CDDM";
    else return false;

    v_lamp = mp_lamp[mapKey];
    return true;
}

int BoardFactory::GetLampEnumType()
{
    return DEF_ENUM_TYPE_PANEL_LAMP;
}

int BoardFactory::GetViibSpecialEnumType()
{
    return DEF_ENUM_TYPE_VIIB_SPECIAL;
}

CsmDevType BoardFactory::GetBoardDevType(EBoradType board_type)
{
    if     (board_type == E_Board_EIOCOM)       return CsmDev_OC_EIOCOM;
    else if(board_type == E_Board_VIIB)         return CsmDev_OC_VIIB;
    else if(board_type == E_Board_VOOB)         return CsmDev_OC_VOOB;
    else if(board_type == E_Board_SDDM)         return CsmDev_OC_SDDM;
    else if(board_type == E_Board_PDDM46)       return CsmDev_OC_PDDM46;
    else if(board_type == E_Board_TCIM25)       return CsmDev_OC_TCIM25;
    else if(board_type == E_Board_PDDM5)        return CsmDev_OC_PDDM5;
    else if(board_type == E_Board_CDDM)         return CsmDev_OC_CDDM;
    else if(board_type == E_Board_SIOM)         return CsmDev_OC_SIOM;
    else if(board_type == E_Board_HIOM)         return CsmDev_OC_HIOM;
    else                                        return CsmDev_Unknow;
}

CsmDevType BoardFactory::GetOtherDevType(EBoradType board_type)
{

    if     (board_type == E_Board_SDDM)         return CsmDev_Signal;
    else if(board_type == E_Board_PDDM46)       return CsmDev_DC_Switch;
    else if(board_type == E_Board_TCIM25)       return CsmDev_Track;
    else if(board_type == E_Board_PDDM5)        return CsmDev_AC_Switch;
    else if(board_type == E_Board_SIOM)         return CsnDev_Scattered;
    else if(board_type == E_Board_HIOM)         return CsmDev_NonStd_ACSwitch;
    else                                        return CsmDev_Unknow;
}

// CBISpecial.ini 文件用
QString BoardFactory::GetCbiTypeName(EBoradType board_type)
{
    if     (board_type == E_Board_EIOCOM)       return "EIOCOM";
    else if(board_type == E_Board_VIIB)         return "VIIB";
    else if(board_type == E_Board_VOOB)         return "VOOB";
    else if(board_type == E_Board_SDDM)         return "SDDM";
    else if(board_type == E_Board_PDDM46)       return "PDDM46";
    else if(board_type == E_Board_TCIM25)       return "TCIM25";
    else if(board_type == E_Board_PDDM5)        return "PDDM5";
    else if(board_type == E_Board_CDDM)         return "CDDM";
    else if(board_type == E_Board_SIOM)         return "SIOM";
    else if(board_type == E_Board_HIOM)         return "HIOM";
    else                                        return "Unknow";
}

int BoardFactory::GetHdwPortCount(EBoradType board_type)
{
    if     (board_type == E_Board_EIOCOM)       return 0;
    else if(board_type == E_Board_VIIB)         return 32;
    else if(board_type == E_Board_VOOB)         return 16;
    else if(board_type == E_Board_SDDM)         return 6;
    else if(board_type == E_Board_PDDM46)       return 1;
    else if(board_type == E_Board_TCIM25)       return 8;
    else if(board_type == E_Board_PDDM5)        return 1;
    else if(board_type == E_Board_CDDM)         return 12;
    else if(board_type == E_Board_SIOM)         return 6;
    else if(board_type == E_Board_HIOM)         return 1;
    else                                        return 0;
}

