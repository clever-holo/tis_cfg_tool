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
    int PluginID_Main();
    int PluginID_A();
    int PluginID_B();

    virtual void GenerateDigit();
    virtual void GenerateEnum();
    virtual void GenerateAnalog(){}
    virtual void GenerateCurve(){}
    virtual void GenerateVS();

    virtual void RegisterDigit(const QVector<QString>& digit, int max_cnt);
    virtual void RegisterEnum(const QVector<QString>& lamp, int max_cnt, int enum_type);



protected:
    EBoradType      m_BoardType;
    QString         m_FullName;
    QString         m_DevName_A;
    QString         m_DevName_B;

    int             m_EcidOrder;
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
    QVector<CsmDataDigit*>  m_board_digit;
    QVector<CsmDataEnum*>   m_board_enum;
    QMap<int, QVector<CsmDataAnalog*>> m_board_analog;
    QMap<int, QVector<CsmDataCurve*>>  m_board_curve;

    CsmDataVS*      m_dev_alarm_vs_A;
    CsmDataVS*      m_dev_alarm_vs_B;
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
};


class VOOBBoard : public BoardBase
{
public:
    VOOBBoard();
    ~VOOBBoard();

protected:
    void GenerateDigit();
};

class SDDMBoard : public BoardBase
{
public:
    SDDMBoard();
    ~SDDMBoard();

    enum
    {
        E_SDDM_ANALOG_DSDL = 0, // 灯丝电流模拟量类型
    };

protected:
    void GenerateAnalog();
};


class PDDM46Board : public BoardBase
{
public:
   PDDM46Board();
   ~PDDM46Board();

   enum
   {
       E_PDDM4_ANALOG_BSDYDY = 20, // 表示电源电压
       E_PDDM4_ANALOG_BSDL = 21,   // 表示电流
   };

   enum
   {
        E_PDDM4_CURVE_DIRECT_CURR = 0,  // 道岔动作电流曲线(直流)
   };

protected:
   void GenerateAnalog();
   void GenerateCurve();
};


class TCIM25Board : public BoardBase
{
public:
   TCIM25Board();
   ~TCIM25Board();

   enum
   {
       E_TCIM_ANALOG_JBXHDY = 23,   // 局部信号电压
       E_TCIM_ANALOG_GDDY   = 22,   // 轨道电压
       E_TCIM_ANALOG_GDXWJ  = 24,   // 轨道相位角
   };

protected:
   void GenerateAnalog();

};


class PDDM5Board : public BoardBase
{
public:
   PDDM5Board();
   ~PDDM5Board();

   enum
   {
       E_PDDM5_ANALOG_SBO_VOLT_C = 27, // C相驱动电压
       E_PDDM5_ANALOG_SBO_VOLT_B = 26, // B相驱动电压
       E_PDDM5_ANALOG_SBO_VOLT_A = 25, // A相驱动电压
       E_PDDM5_ANALOG_EXP_VOLT   = 28, // 表示电压
       E_PDDM5_ANALOG_SBO_FN_DL  = 29, // 反表内部回路电流
       E_PDDM5_ANALOG_SBO_FW_DL  = 30, // 反表外部回路电流
       E_PDDM5_ANALOG_SBO_DN_DL  = 31, // 定表内部回路电流
       E_PDDM5_ANALOG_SBO_DW_DL  = 32, // 定表外部回路电流
   };

   enum
   {
       E_PDDM5_CURVE_CURR_C  = 3,       // 道岔动作C相电流曲线
       E_PDDM5_CURVE_PHASE_C = 6,       // 道岔动作C相相位曲线
       E_PDDM5_CURVE_CURR_B  = 2,       // 道岔动作B相电流曲线
       E_PDDM5_CURVE_PHASE_B = 5,       // 道岔动作B相相位曲线
       E_PDDM5_CURVE_CURR_A  = 1,       // 道岔动作A相电流曲线
       E_PDDM5_CURVE_PHASE_A = 4,       // 道岔动作A相相位曲线
   };

protected:
   void GenerateAnalog();
   void GenerateCurve();
};


class CDDMBoard : public BoardBase
{
public:
   CDDMBoard();
   ~CDDMBoard();

protected:
   void GenerateDigit();

};


class SIOMBoard : public BoardBase
{
public:
   SIOMBoard();
   ~SIOMBoard();

   enum
   {
       E_SIOM_ANALOG_DI_SBO_VOLT     = 33,  // 驱动/采集电压
       E_SIOM_ANALOG_SELF_CHECK_VOLT = 34,  // 自检电源电压
   };

protected:
   void GenerateAnalog();
};


class HIOMBoard : public BoardBase
{
public:
   HIOMBoard();
   ~HIOMBoard();

   enum
   {
       E_HIOM_ANALOG_DB_PORT_VOLT   = 35,  // 定表端口采集电压
       E_HIOM_ANALOG_FB_PORT_VOLT   = 36,  // 反表端口采集电压
       E_HIOM_ANALOG_SYB_PORT_VOLT  = 37,  // 手摇把端口采集电压
   };

   enum
   {
       E_HIOM_CURVE_CURR_A  = 1,       // 道岔动作A相电流曲线
       E_HIOM_CURVE_CURR_B  = 2,       // 道岔动作B相电流曲线
       E_HIOM_CURVE_CURR_C  = 3,       // 道岔动作C相电流曲线
   };

protected:
   void GenerateAnalog();
   void GenerateCurve();
};

#endif // BOARDDEFINE_H
