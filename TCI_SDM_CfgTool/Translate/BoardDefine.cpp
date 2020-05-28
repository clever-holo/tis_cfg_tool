#include "BoardDefine.h"
#include <QRegularExpression>

BoardBase::BoardBase()
{
    m_BoardType = E_Board_Unknow;
}

BoardBase::~BoardBase()
{

}

int BoardBase::GetSlotB(EBoardBPType bp, int slotA)
{
    if(slotA == 2)
        return 16;

    return bp == E_BP2 ? (slotA + 6) : (slotA + 4);
}

EBoradType BoardBase::BoardType() const
{
    return m_BoardType;
}


int BoardBase::Ecid() const
{
    return m_Ecid;
}

void BoardBase::setEcid(int Ecid)
{
    m_Ecid = Ecid;
}

int BoardBase::Slot_B() const
{
    return m_Slot_B;
}

void BoardBase::setSlot_B(int Slot_B)
{
    m_Slot_B = Slot_B;
}

int BoardBase::Rock_B() const
{
    return m_Rock_B;
}

void BoardBase::setRock_B(int Rock_B)
{
    m_Rock_B = Rock_B;
}

int BoardBase::Slot_A() const
{
    return m_Slot_A;
}

void BoardBase::setSlot_A(int Slot_A)
{
    m_Slot_A = Slot_A;
}

int BoardBase::Rock_A() const
{
    return m_Rock_A;
}

void BoardBase::setRock_A(int Rock_A)
{
    m_Rock_A = Rock_A;
}

QString BoardBase::FullName() const
{
    return m_FullName;
}

void BoardBase::setFullName(const QString &FullName)
{
    m_FullName = FullName;
}

EBoardBPType BoardBase::BP() const
{
    return m_BP;
}

void BoardBase::setBP(const EBoardBPType &BP)
{
    m_BP = BP;
}

BoardBase *BoardBase::Init(const BoardInfo *board_info)
{
    if(board_info == nullptr)
        return nullptr;

    //正常板卡是一组码位，即采驱码位的名称相同
    //TCIM(?)板卡有2组码位，采驱码位名称不一致，子类需要覆写该函数
    if(board_info->_mpPort.size() != 1)
        return nullptr;

    // 设置full_name
    setFullName(board_info->_mpPort.firstKey());

    // 添加采集码位
    AddCode(board_info->_mpPort.first());

    // 分析板卡位置
    AnalysePostion(board_info->_mpPort.firstKey(), board_info->_slot, board_info->_bp);

    // 设置设置b系板卡位置
    SetPosB();

    return this;
}

void BoardBase::AnalysePostion(const QString &full_name, const QString &slot, const QString &bp)
{
   QStringList strlist = full_name.split("_");
   strlist.append(slot);
   strlist.append(bp);

   for(int i=0; i<strlist.size(); i++)
   {
       QRegularExpression rx("(\\d+)");
       QRegularExpressionMatchIterator reg_it = rx.globalMatch(strlist[i]);
       if(!reg_it.hasNext())
           continue;
       int digit = reg_it.next().captured(1).toInt();

       if(strlist[i].contains(QRegExp("^\\d+")))   // EIOCOM板所属ECID
       {
           setEcid(digit);
       }
       else if(strlist[i].contains(QRegExp("^C\\d+")))  // 非EIOCOM板所属ECID
       {
           setEcid(digit);
       }
       else if(strlist[i].contains(QRegExp("^R\\d+")))  // 机笼号
       {
           setRock_A(digit);
       }
       else if(strlist[i].contains(QRegExp("^BP\\d+")))  // BP
       {
           setBP(EBoardBPType(digit));
       }
       else if(strlist[i].contains(QRegExp("^slot NO.\\d+")))  // 槽道号
       {
           setSlot_A(digit);
       }
   }

}

void BoardBase::AddCode(const QVector<QString> &lstCode)
{
    m_lstCode = lstCode;
    QVector<QString>::reverse_iterator rit = m_lstCode.rbegin();
    for(; rit != m_lstCode.rend(); rit++)
    {
        if(!rit->isEmpty())
        {
            m_lstCode.erase(rit.base(), m_lstCode.end());
            break;
        }
    }
    if(rit == m_lstCode.rend())
        m_lstCode.clear();
}

void BoardBase::SetPosB()
{
    setRock_B(Rock_A());
    setSlot_B(BoardBase::GetSlotB(BP(), Slot_A()));
}

EIOCOMBoard::EIOCOMBoard()
{
    m_BoardType = E_Board_EIOCOM;
}

EIOCOMBoard::~EIOCOMBoard()
{

}

VIIBBoard::VIIBBoard()
{
    m_BoardType = E_Board_VIIB;
}

VIIBBoard::~VIIBBoard()
{

}



VOOBBoard::VOOBBoard()
{
    m_BoardType = E_Board_VOOB;
}

VOOBBoard::~VOOBBoard()
{

}

SDDMBoard::SDDMBoard()
{
    m_BoardType = E_Board_SDDM;
}

SDDMBoard::~SDDMBoard()
{

}

PDDM46Board::PDDM46Board()
{
    m_BoardType = E_Board_PDDM46;
}

PDDM46Board::~PDDM46Board()
{

}

TCIM25Board::TCIM25Board()
{
    m_BoardType = E_Board_TCIM25;
}

TCIM25Board::~TCIM25Board()
{

}

PDDM5Board::PDDM5Board()
{
    m_BoardType = E_Board_PDDM5;
}

PDDM5Board::~PDDM5Board()
{

}

CDDMBoard::CDDMBoard()
{
    m_BoardType = E_Board_CDDM;
}

CDDMBoard::~CDDMBoard()
{

}

SIOMBoard::SIOMBoard()
{
    m_BoardType = E_Board_SIOM;
}

SIOMBoard::~SIOMBoard()
{

}

HIOMBoard::HIOMBoard()
{
    m_BoardType = E_Board_HIOM;
}

HIOMBoard::~HIOMBoard()
{

}
