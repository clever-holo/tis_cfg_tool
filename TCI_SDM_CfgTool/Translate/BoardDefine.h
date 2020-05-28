#ifndef BOARDDEFINE_H
#define BOARDDEFINE_H

#include <QString>
#include <QVector>
#include "CodeTable.h"

enum EBoradType
{
    E_Board_Unknow = -1,
    E_Board_EIOCOM = 0,
    E_Board_VIIB,
    E_Board_VOOB,
    E_Board_SDDM,
    E_Board_PDDM46,
    E_Board_TCIM25,
    E_Board_PDDM5,
    E_Board_CDDM,
    E_Board_SIOM,
    E_Board_HIOM,
};

enum EBoardBPType
{
    E_BP2 = 2,
    E_BP5 = 5,
};

/////////////////////////////////////////////
///
class BoardBase
{
public:
    BoardBase();
    virtual ~BoardBase();

    static int GetSlotB(EBoardBPType bp, int slotA);

public:
    BoardBase* Init(const BoardInfo* board_info);

    int Ecid() const;
    int Rock_A() const;
    int Slot_A() const;
    int Rock_B() const;
    int Slot_B() const;
    EBoardBPType BP() const;
    EBoradType BoardType() const;
    QString FullName() const;

protected:
    void AnalysePostion(const QString& full_name, const QString& slot, const QString& bp);
    void AddCode(const QVector<QString>& lstCode);
    void SetPosB();
    void setEcid(int Ecid);
    void setRock_A(int Rock_A);
    void setSlot_A(int Slot_A);
    void setRock_B(int Rock_B);
    void setSlot_B(int Slot_B);
    void setFullName(const QString &FullName);
    void setBP(const EBoardBPType &BP);


protected:
    EBoradType      m_BoardType;
    QString         m_FullName;

    int             m_Ecid;
    int             m_Rock_A;
    int             m_Slot_A;
    int             m_Rock_B;
    int             m_Slot_B;
    EBoardBPType         m_BP;

    QVector<QString>  m_lstCode;
};


class EIOCOMBoard : public BoardBase
{
public:
    EIOCOMBoard();
    ~EIOCOMBoard();
};


class VIIBBoard : public BoardBase
{
public:
    VIIBBoard();
    ~VIIBBoard();
};


class VOOBBoard : public BoardBase
{
public:
    VOOBBoard();
    ~VOOBBoard();
};

class SDDMBoard : public BoardBase
{
public:
    SDDMBoard();
    ~SDDMBoard();
};


class PDDM46Board : public BoardBase
{
public:
   PDDM46Board();
   ~PDDM46Board();
};


class TCIM25Board : public BoardBase
{
public:
   TCIM25Board();
   ~TCIM25Board();
};


class PDDM5Board : public BoardBase
{
public:
   PDDM5Board();
   ~PDDM5Board();
};


class CDDMBoard : public BoardBase
{
public:
   CDDMBoard();
   ~CDDMBoard();
};


class SIOMBoard : public BoardBase
{
public:
   SIOMBoard();
   ~SIOMBoard();
};


class HIOMBoard : public BoardBase
{
public:
   HIOMBoard();
   ~HIOMBoard();
};

#endif // BOARDDEFINE_H
