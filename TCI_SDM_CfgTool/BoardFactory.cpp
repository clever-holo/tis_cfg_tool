#include "BoardFactory.h"

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
    else if(board_name.contains("TCIM25"))      return E_Board_TCIM25;
    else if(board_name.contains("PDDM5"))       return E_Board_PDDM5;
    else if(board_name.contains("CDDM"))        return E_Board_CDDM;
    else if(board_name.contains("SIOM"))        return E_Board_SIOM;
    else if(board_name.contains("HIOM"))        return E_Board_HIOM;
    else                                        return E_Board_Unknow;
}
