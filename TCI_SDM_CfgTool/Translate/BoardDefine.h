#ifndef BOARDDEFINE_H
#define BOARDDEFINE_H

#include <QString>
#include <QVector>
#include "CodeTable.h"
#include "CsmDataDefine.h"
#include "CsmPlugin.h"
#include "CsmDigit.h"
#include "CsmEnum.h"
#include "CsmAnalog.h"
#include "CsmCurve.h"
#include "CsmVirtualStatus.h"

class ECID;
class CsmDataDev;
class MyIniFile;

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

    int EcidOrder() const;
    int Rock_A() const;
    int Slot_A() const;
    int Rock_B() const;
    int Slot_B() const;
    EBoardBPType BP() const;
    EBoradType BoardType() const;
    QString FullName() const;

    void GenerateData();

    ECID *ecid() const;
    void setEcid(ECID *ecid);

    int PluginID_Main() const;
    int PluginID_A() const;
    int PluginID_B() const;

    const QVector<CsmDataDigit*> Digits(int plugin_id) const;
    const QVector<CsmDataEnum*> Enums(int plugin_id) const;
    const QVector<CsmDataAnalog*> Analogs(int plugin_id) const;
    const QVector<CsmDataCurve*> Curves(int plugin_id) const;

    const CsmDataDev *BoardDevA() const;
    const CsmDataDev *BoardDevB() const;

    int OrderInEcid() const;
    void setOrderInEcid(int OrderInEcid);

    void WriteEcidHdw(MyIniFile* myfile) const;

protected:
    void AnalysePostion(const QString& full_name, const QString& slot, const QString& bp);
    void AnalyseDevNmae();
    void AddCode(const QVector<QString>& lstCode);
    void SetPosB();
    void setEcidOrder(int EcidOrder);
    void setRock_A(int Rock_A);
    void setSlot_A(int Slot_A);
    void setRock_B(int Rock_B);
    void setSlot_B(int Slot_B);
    void setFullName(const QString &FullName);
    void setBP(const EBoardBPType &BP);

    virtual void GenerateDigit();
    virtual void GenerateEnum();
    virtual void GenerateAnalog(){}
    virtual void GenerateCurve(){}
    virtual void GenerateVS();
    virtual void GenerateDev();
    virtual void GenerateBoardDev();
    virtual void GenerateOtherDev();
    virtual void GenerateOtherDev2(){}

    virtual void RegisterDigit(const QVector<QString>& digit, int max_cnt);
    virtual void RegisterEnum(const QVector<QString>& lamp, int max_cnt, int enum_type);

    virtual QString GetHdwInput() const;
    virtual QString GetHdwOutput() const;
    virtual const QVector<QString> &GetPorts() const;

protected:
    EBoradType      m_BoardType;
    QString         m_FullName;
    QString         m_DevName_A;
    QString         m_DevName_B;

    int             m_EcidOrder;    // begin with 1;
    int             m_OrderInEcid;  // begin with 1;
    int             m_Rock_A;
    int             m_Slot_A;
    int             m_Rock_B;
    int             m_Slot_B;
    EBoardBPType    m_BP;

    QVector<int>    m_PluginID;
    QVector<QString>  m_lstCode;

    ECID*           m_ecid;
    // ////////////////////////////////////////////
    // CsmData
    QMap<int, QVector<CsmDataDigit*>>  m_board_digit;   // key: plugin_id
    QMap<int, QVector<CsmDataEnum*>>   m_board_enum;    // key: plugin_id
    QMap<int, QVector<CsmDataAnalog*>> m_board_analog;  // key: analog_type
    QMap<int, QVector<CsmDataCurve*>>  m_board_curve;   // key: curve_type

    CsmDataVS*      m_dev_alarm_vs_A;
    CsmDataVS*      m_dev_alarm_vs_B;

    CsmDataDev*     m_board_dev_A;
    CsmDataDev*     m_board_dev_B;

    QVector<CsmDataDev*>  m_other_dev;
};


class EIOCOMBoard : public BoardBase
{
public:
    EIOCOMBoard();
    ~EIOCOMBoard();

protected:
    void GenerateDigit(){}
    void GenerateEnum(){}
    void GenerateAnalog(){}
    void GenerateCurve(){}
};


class VIIBBoard : public BoardBase
{
public:
    VIIBBoard();
    ~VIIBBoard();

protected:
    void GenerateDigit();
    void GenerateEnum();

    QString GetHdwInput() const  {return "*";}
    QString GetHdwOutput() const  {return "";}
};


class VOOBBoard : public BoardBase
{
public:
    VOOBBoard();
    ~VOOBBoard();

protected:
    void GenerateDigit();

    QString GetHdwInput() const  {return "";}
    QString GetHdwOutput() const  {return "*";}
};

class SDDMBoard : public BoardBase
{
public:
    SDDMBoard();
    ~SDDMBoard();

protected:
    void GenerateAnalog();
    void GenerateOtherDev();
};


class PDDM46Board : public BoardBase
{
public:
   PDDM46Board();
   ~PDDM46Board();

protected:
   void GenerateAnalog();
   void GenerateCurve();
   void GenerateOtherDev2();
};


class TCIM25Board : public BoardBase
{
public:
   TCIM25Board();
   ~TCIM25Board();

protected:
   void GenerateAnalog();
   void GenerateOtherDev2();
};


class PDDM5Board : public BoardBase
{
public:
   PDDM5Board();
   ~PDDM5Board();

protected:
   void GenerateAnalog();
   void GenerateCurve();
   void GenerateOtherDev2();
};


class CDDMBoard : public BoardBase
{
public:
   CDDMBoard();
   ~CDDMBoard();

protected:
   void GenerateDigit();

   QString GetHdwInput() const;
   const QVector<QString> &GetPorts() const;
};


class SIOMBoard : public BoardBase
{
public:
   SIOMBoard();
   ~SIOMBoard();

protected:
   void GenerateAnalog();
   void GenerateOtherDev2();
};


class HIOMBoard : public BoardBase
{
public:
   HIOMBoard();
   ~HIOMBoard();

protected:
   void GenerateAnalog();
   void GenerateCurve();
   void GenerateOtherDev2();
};

#endif // BOARDDEFINE_H
