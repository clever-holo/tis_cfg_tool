#include "BoardDefine.h"
#include <QRegularExpression>
#include "CsmDataManager.h"
#include "EcidDefine.h"
#include "BoardFactory.h"
#include "CsmDevice.h"

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


int BoardBase::EcidOrder() const
{
    return m_EcidOrder;
}

void BoardBase::setEcidOrder(int Ecid)
{
    m_EcidOrder = Ecid;
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

//*///////////////////////
// 生成Csmdata
void BoardBase::GenerateData()
{
    m_PluginID.push_back(PluginID_Main());
    m_PluginID.push_back(PluginID_A());
    m_PluginID.push_back(PluginID_B());

    // 生成开关量
    GenerateDigit();
    // 生成枚举量
    GenerateEnum();
    // 生成模拟量
    GenerateAnalog();
    // 生成曲线量
    GenerateCurve();
    // 生成虚拟状态量
    GenerateVS();
    // 生成设备
    GenerateDev();

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

int BoardBase::PluginID_Main() const
{
    return m_ecid->plugin_main()._plugin_id;
}

int BoardBase::PluginID_A() const
{
    return m_ecid->plugin_A()._plugin_id;
}

int BoardBase::PluginID_B() const
{
    return m_ecid->plugin_B()._plugin_id;
}

const QVector<CsmDataDigit *> BoardBase::Digits(int plugin_id) const
{
    return m_board_digit[plugin_id];
}

const QVector<CsmDataEnum *> BoardBase::Enums(int plugin_id) const
{
    return m_board_enum[plugin_id];
}

const QVector<CsmDataAnalog *> BoardBase::Analogs(int plugin_id) const
{
    return m_board_analog[plugin_id];
}

const QVector<CsmDataCurve *> BoardBase::Curves(int plugin_id) const
{
    return m_board_curve[plugin_id];
}

const CsmDataDev *BoardBase::BoardDevA() const
{
    return m_board_dev_A;
}

const CsmDataDev *BoardBase::BoardDevB() const
{
    return m_board_dev_B;
}

void BoardBase::GenerateDigit()
{
    // 基类方法适用于：SDDM、PDDM46、TCIM25、PDDM5、SIOM

    // 获取采驱后缀
    QVector<QString> v_di, v_sbo;
    BoardFactory::GetBoardInAndOut(m_BoardType, v_di, v_sbo);

    // 采集码位
    QVector<QString> di_kgl;
    foreach (const QString& code, m_lstCode)
    {
        if(!code.isEmpty())
        {
            foreach (const QString& suffix, v_di)
                di_kgl.push_back(code + suffix);
        }
    }
    if(!di_kgl.isEmpty())
        RegisterDigit(di_kgl, BoardFactory::GetMaxDi(m_BoardType));

    // 驱动码位
    QVector<QString> sbo_kgl;
    foreach (const QString& code, m_lstCode)
    {
        if(!code.isEmpty())
        {
            foreach (const QString& suffix, v_sbo)
                sbo_kgl.push_back(code + suffix);
        }
    }
    if(!sbo_kgl.isEmpty())
        RegisterDigit(sbo_kgl, BoardFactory::GetMaxSbo(m_BoardType));
}

void BoardBase::GenerateEnum()
{
    QVector<QString> v_lamp;
    BoardFactory::GetPanelLamp(m_BoardType, v_lamp);

    //
    int use_cnt = m_lstCode.size();
    int all_cnt = v_lamp.size();
    if(use_cnt > all_cnt)
        return;

    QVector<QString> v_use, v_notuse;
    for(int i=0; i<use_cnt; i++)
    {
        if(m_lstCode[i].isEmpty())
            v_notuse.push_back(v_lamp[i]);
        else
            v_use.push_back(v_lamp[i]);
    }

    foreach (const QString& var, v_notuse)
        v_use.push_back(var);

    for(int i=use_cnt; i<all_cnt; i++)
        v_use.push_back(v_lamp[i]);

    RegisterEnum(v_use, BoardFactory::GetMaxLamp(m_BoardType), BoardFactory::GetLampEnumType());
}

void BoardBase::GenerateVS()
{
    CsmVirtualStatus* pVS = Singleton<CsmDataManager>::Instance().GetVs();
    m_dev_alarm_vs_A = pVS->CreateVS(DEF_VS_DEV_ALARM_STATUS, m_DevName_A);
    m_dev_alarm_vs_B = pVS->CreateVS(DEF_VS_DEV_ALARM_STATUS, m_DevName_B);
    pVS->CreateVS(DEF_VS_DEV_STOPUSE_STATUS, m_DevName_A);
    pVS->CreateVS(DEF_VS_DEV_STOPUSE_STATUS, m_DevName_B);
    pVS->CreateVS(DEF_VS_DEV_OVERHAUL_STATUS, m_DevName_A);
    pVS->CreateVS(DEF_VS_DEV_OVERHAUL_STATUS, m_DevName_B);
    pVS->CreateVS(DEF_VS_DEV_STARE_CTRL_STATUS, m_DevName_A);
    pVS->CreateVS(DEF_VS_DEV_STARE_CTRL_STATUS, m_DevName_B);
    pVS->CreateVS(DEF_VS_DEV_CONFIRM_STATUS, m_DevName_A);
    pVS->CreateVS(DEF_VS_DEV_CONFIRM_STATUS, m_DevName_B);
}

//*///////////////////////
// 生成设备
void BoardBase::GenerateDev()
{
    // 生成板卡设备
    GenerateBoardDev();

    // 将该板卡的采集对象生成设备
    GenerateOtherDev();
}

void BoardBase::GenerateBoardDev()
{
    CsmDevice* pDev     = Singleton<CsmDataManager>::Instance().GetDev();
    CsmDevType pDevType = BoardFactory::GetBoardDevType(m_BoardType);
    QString vs_order_A  = QString::number(DEF_VS_PLUGIN_ID) + "#" + QString::number(m_dev_alarm_vs_A->_vs_order);
    QString vs_order_B  = QString::number(DEF_VS_PLUGIN_ID) + "#" + QString::number(m_dev_alarm_vs_B->_vs_order);
    QString comm_vs_A   = QString::number(DEF_VS_PLUGIN_ID) + "#" + QString::number( 3 + (m_EcidOrder-1) * 3 + 1 );
    QString comm_vs_B   = QString::number(DEF_VS_PLUGIN_ID) + "#" + QString::number( 3 + (m_EcidOrder-1) * 3 + 2 );
    m_board_dev_A = pDev->CreateDev(pDevType, m_DevName_A, vs_order_A, comm_vs_A);
    m_board_dev_B = pDev->CreateDev(pDevType, m_DevName_B, vs_order_B, comm_vs_B);

    QVector<CsmDataDigit*>& v_digit_A = m_board_digit[PluginID_A()];
    QVector<CsmDataEnum*>&  v_enum_A  = m_board_enum[PluginID_A()];
    QVector<CsmDataDigit*>& v_digit_B = m_board_digit[PluginID_B()];
    QVector<CsmDataEnum*>&  v_enum_B  = m_board_enum[PluginID_B()];

    // 板卡设备只添加开关量和枚举量
    foreach (CsmDataDigit* var, v_digit_A) {
        m_board_dev_A->AddCJInfo(var);
    }

    foreach (CsmDataEnum* var, v_enum_A) {
        m_board_dev_A->AddCJInfo(var);
    }

    foreach (CsmDataDigit* var, v_digit_B) {
        m_board_dev_B->AddCJInfo(var);
    }

    foreach (CsmDataEnum* var, v_enum_B) {
        m_board_dev_B->AddCJInfo(var);
    }
}

void BoardBase::GenerateOtherDev()
{
    // 生成其他设备
    CsmDevType pDevType = BoardFactory::GetOtherDevType(m_BoardType);
    if(pDevType == CsmDev_Unknow)
        return;

    CsmDevice* pDev = Singleton<CsmDataManager>::Instance().GetDev();
    foreach (const QString& var, m_lstCode)
    {
        if(!var.isEmpty())
        {
            CsmDataDev* pdata = pDev->CreateDev(pDevType, var, "", "");
            m_other_dev.push_back(pdata);
        }
    }

    // 给设备添加采集项，子类实现
    GenerateOtherDev2();

    return;
}

//*///////////////////////
// 生成digit
void BoardBase::RegisterDigit(const QVector<QString> &digit, int max_cnt)
{
    CsmDigit* pDigit = Singleton<CsmDataManager>::Instance().GetDigit();
    CsmDataDigit* pdata;
    foreach (const QString& ele, digit)
    {
        foreach (int plugin_id, m_PluginID)
        {
            pdata = pDigit->CreateDigit(plugin_id, ele, 0, 0, 1, 0, 1, 0);
            m_board_digit[plugin_id].push_back(pdata);
        }
    }

    // 需要预留的码位
    int reserve_cnt = max_cnt - digit.size();
    for(int i=0; i<reserve_cnt; i++)
    {
        foreach (int plugin_id, m_PluginID)
        {
             pDigit->CreateDigit(plugin_id, "DUMMY", 0, 0, 0, 0, 1, 0);
        }
    }
    return;
}

void BoardBase::RegisterEnum(const QVector<QString> &lamp, int max_cnt, int enum_type)
{
    CsmEnum* pEnum = Singleton<CsmDataManager>::Instance().GetEnum();
    CsmDataEnum* pdata;
    foreach (const QString& ele, lamp)
    {
        foreach (int plugin_id, m_PluginID)
        {
            pdata = pEnum->CreateEnum(plugin_id, ele, enum_type, 1, 1);
            m_board_enum[plugin_id].push_back(pdata);
        }
    }

    // 需要预留的码位
    int reserve_cnt = max_cnt - lamp.size();
    for(int i=0; i<reserve_cnt; i++)
    {
        foreach (int plugin_id, m_PluginID)
        {
            pEnum->CreateEnum(plugin_id, "DUMMY", enum_type, 0, 1);
        }
    }
}

ECID *BoardBase::ecid() const
{
    return m_ecid;
}

void BoardBase::setEcid(ECID *ecid)
{
    m_ecid = ecid;
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

    // 分析板卡设备名字
    AnalyseDevNmae();

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
           setEcidOrder(digit);
       }
       else if(strlist[i].contains(QRegExp("^C\\d+")))  // 非EIOCOM板所属ECID
       {
           setEcidOrder(digit);
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

void BoardBase::AnalyseDevNmae()
{
    if(m_BoardType == E_Board_EIOCOM)
    {
        m_DevName_A = QString("执行单元%1-1_A系_EIOCOM-4").arg(m_EcidOrder);
        m_DevName_B = QString("执行单元%1-1_B系_EIOCOM-4").arg(m_EcidOrder);
    }
    else if(m_Rock_A == 1)
    {
        // 位于机笼1
        m_DevName_A = QString("执行单元%1-%2_A系_槽%3").arg(m_EcidOrder).arg(m_Rock_A).arg(m_Slot_A - 2);
        m_DevName_B = QString("执行单元%1-%2_B系_槽%3").arg(m_EcidOrder).arg(m_Rock_B).arg(m_Slot_A - 2);
    }
    else
    {
        m_DevName_A = QString("执行单元%1-%2_A系_槽%3").arg(m_EcidOrder).arg(m_Rock_A).arg(m_Slot_A - 1);
        m_DevName_B = QString("执行单元%1-%2_B系_槽%3").arg(m_EcidOrder).arg(m_Rock_B).arg(m_Slot_A - 1);
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

//-//////////////////////////////////////////////////
// VIIB
VIIBBoard::VIIBBoard()
{
    m_BoardType = E_Board_VIIB;
}

VIIBBoard::~VIIBBoard()
{

}

void VIIBBoard::GenerateDigit()
{
    QVector<QString> kgl;
    foreach (const QString& code, m_lstCode) {
        if(!code.isEmpty())
            kgl.push_back(code);
    }
    RegisterDigit(kgl, BoardFactory::GetMaxDi(m_BoardType));
}

void VIIBBoard::GenerateEnum()
{
    // 基类生成面板灯枚举量
    BoardBase::GenerateEnum();

    // 生成VIIB特殊枚举量
    QVector<QString> spe_enum;
    foreach (const QString& code, m_lstCode) {
        if(!code.isEmpty())
            spe_enum.push_back(code);
    }
    // 特殊枚举量的个数应等于最大采集码位个数
    RegisterEnum(spe_enum, BoardFactory::GetMaxDi(m_BoardType), BoardFactory::GetViibSpecialEnumType());
}


//-//////////////////////////////////////////////////
// VOOB
VOOBBoard::VOOBBoard()
{
    m_BoardType = E_Board_VOOB;
}

VOOBBoard::~VOOBBoard()
{

}

void VOOBBoard::GenerateDigit()
{
    QVector<QString> kgl;
    foreach (const QString& code, m_lstCode) {
        if(!code.isEmpty())
            kgl.push_back(code);
    }
    RegisterDigit(kgl, BoardFactory::GetMaxSbo(m_BoardType));
}

//-//////////////////////////////////////////////////
SDDMBoard::SDDMBoard()
{
    m_BoardType = E_Board_SDDM;
}

SDDMBoard::~SDDMBoard()
{

}

void SDDMBoard::GenerateAnalog()
{
    CsmAnalog* pAnalog = Singleton<CsmDataManager>::Instance().GetAnalog();
    CsmDataAnalog* pdata;
    foreach (const QString& ele, m_lstCode)
    {
        if(ele.isEmpty())
            continue;

        foreach (int plugin_id, m_PluginID)
        {
            pdata = pAnalog->CreateAnalog(E_SDDM_ANALOG_DSDL, plugin_id, ele, 1, "mA", 1, 1);
            m_board_analog[plugin_id].push_back(pdata);
        }

    }
}

void SDDMBoard::GenerateOtherDev()
{
    CsmDevice* pDev = Singleton<CsmDataManager>::Instance().GetDev();

    int count = 0;
    foreach (const QString& var, m_lstCode)
    {
        if(!var.isEmpty())
        {
            CsmDataDev* pdata = pDev->CreateDev(CsmDev_Signal, var, "", "");
            pdata->AddCJInfo(m_board_analog[PluginID_A()][count]);
            pdata->AddCJInfo(m_board_analog[PluginID_B()][count]);
            count++;
        }
    }
}

//-//////////////////////////////////////////////////
PDDM46Board::PDDM46Board()
{
    m_BoardType = E_Board_PDDM46;
}

PDDM46Board::~PDDM46Board()
{

}

void PDDM46Board::GenerateAnalog()
{
    CsmAnalog* pAnalog = Singleton<CsmDataManager>::Instance().GetAnalog();
    CsmDataAnalog* pdata;
    foreach (const QString& ele, m_lstCode)
    {
        if(ele.isEmpty())
            continue;

        foreach (int plugin_id, m_PluginID)
        {
            pdata = pAnalog->CreateAnalog(E_PDDM4_ANALOG_BSDYDY, plugin_id, ele, 1, "V", 1, 1);
            m_board_analog[plugin_id].push_back(pdata);
            pdata = pAnalog->CreateAnalog(E_PDDM4_ANALOG_BSDL, plugin_id, ele, 1, "mA", 1, 1);
            m_board_analog[plugin_id].push_back(pdata);
        }
    }
}

void PDDM46Board::GenerateCurve()
{
    CsmCurve* pCurve = Singleton<CsmDataManager>::Instance().GetCurve();
    CsmDataCurve* pdata;
    foreach (const QString& ele, m_lstCode)
    {
        if(ele.isEmpty())
            continue;

        foreach (int plugin_id, m_PluginID)
        {
            pdata = pCurve->CreateCurve(E_PDDM4_CURVE_DIRECT_CURR, plugin_id, ele + "_道岔动作电流曲线", 1, "A", 25, 1);
            m_board_curve[plugin_id].push_back(pdata);
        }
    }
}

void PDDM46Board::GenerateOtherDev2()
{
    Q_ASSERT(m_other_dev.size() == 1);

    CsmDataDev* pdata = m_other_dev.first();

    // 添加A系模拟量
    foreach (CsmDataAnalog* var, m_board_analog[PluginID_A()]) {
        pdata->AddCJInfo(var);
    }

    // 添加B系模拟量
    foreach (CsmDataAnalog* var, m_board_analog[PluginID_B()]) {
        pdata->AddCJInfo(var);
    }

    // 添加主系曲线
    foreach (CsmDataCurve* var, m_board_curve[PluginID_Main()]) {
        pdata->AddCJInfo(var);
    }
}

//-//////////////////////////////////////////////////
TCIM25Board::TCIM25Board()
{
    m_BoardType = E_Board_TCIM25;
}

TCIM25Board::~TCIM25Board()
{

}

void TCIM25Board::GenerateAnalog()
{
    CsmAnalog* pAnalog = Singleton<CsmDataManager>::Instance().GetAnalog();
    CsmDataAnalog* pdata;

    // 按照板卡发送的顺序生成模拟量
    // (1)每个码位生成1个轨道电压
    foreach (const QString& ele, m_lstCode)
    {
        if(ele.isEmpty())
            continue;

        foreach (int plugin_id, m_PluginID)
        {
            pdata = pAnalog->CreateAnalog(E_TCIM_ANALOG_GDDY, plugin_id, ele, 1, "V", 1, 1);
            m_board_analog[plugin_id].push_back(pdata);
        }
    }

    // （2）生成1个局部信号电压（参考电压）
    foreach (int plugin_id, m_PluginID)
    {
        pdata = pAnalog->CreateAnalog(E_TCIM_ANALOG_JBXHDY, plugin_id, "局部信号电压", 1, "V", 1, 1);
        m_board_analog[plugin_id].push_back(pdata);
    }

    // (3)每个码位生成1个轨道相位角
    foreach (const QString& ele, m_lstCode)
    {
        if(ele.isEmpty())
            continue;

        foreach (int plugin_id, m_PluginID)
        {
            pdata = pAnalog->CreateAnalog(E_TCIM_ANALOG_GDXWJ, plugin_id, ele, 1, "度", 1, 1);
            m_board_analog[plugin_id].push_back(pdata);
        }
    }
}

void TCIM25Board::GenerateOtherDev2()
{
    QVector<CsmDataAnalog*>& v_analog_A = m_board_analog[PluginID_A()];
    QVector<CsmDataAnalog*>& v_analog_B = m_board_analog[PluginID_B()];

    int count = 0;
    int dev_size = m_other_dev.size();
    foreach (CsmDataDev* var, m_other_dev)
    {
        var->AddCJInfo(v_analog_A[count]);
        var->AddCJInfo(v_analog_A[count + dev_size + 1]);
        var->AddCJInfo(v_analog_B[count]);
        var->AddCJInfo(v_analog_B[count + dev_size + 1]);
        count++;
    }
}

//-//////////////////////////////////////////////////
PDDM5Board::PDDM5Board()
{
    m_BoardType = E_Board_PDDM5;
}

PDDM5Board::~PDDM5Board()
{

}

void PDDM5Board::GenerateAnalog()
{
    CsmAnalog* pAnalog = Singleton<CsmDataManager>::Instance().GetAnalog();
    CsmDataAnalog* pdata;

    Q_ASSERT(m_lstCode.size() == 1);
    const QString& ele = m_lstCode.first();

    foreach (int plugin_id, m_PluginID)
    {
        pdata = pAnalog->CreateAnalog(E_PDDM5_ANALOG_SBO_VOLT_C, plugin_id, ele, 1, "V", 1, 1);
        m_board_analog[plugin_id].push_back(pdata);
        pdata = pAnalog->CreateAnalog(E_PDDM5_ANALOG_SBO_VOLT_B, plugin_id, ele, 1, "V", 1, 1);
        m_board_analog[plugin_id].push_back(pdata);
        pdata = pAnalog->CreateAnalog(E_PDDM5_ANALOG_SBO_VOLT_A, plugin_id, ele, 1, "V", 1, 1);
        m_board_analog[plugin_id].push_back(pdata);
        pdata = pAnalog->CreateAnalog(E_PDDM5_ANALOG_EXP_VOLT,  plugin_id, ele, 1, "V", 1, 1);
        m_board_analog[plugin_id].push_back(pdata);
        pdata = pAnalog->CreateAnalog(E_PDDM5_ANALOG_SBO_FN_DL, plugin_id, ele, 1, "mA", 1, 1);
        m_board_analog[plugin_id].push_back(pdata);
        pdata = pAnalog->CreateAnalog(E_PDDM5_ANALOG_SBO_FW_DL, plugin_id, ele, 1, "mA", 1, 1);
        m_board_analog[plugin_id].push_back(pdata);
        pdata = pAnalog->CreateAnalog(E_PDDM5_ANALOG_SBO_DN_DL, plugin_id, ele, 1, "mA", 1, 1);
        m_board_analog[plugin_id].push_back(pdata);
        pdata = pAnalog->CreateAnalog(E_PDDM5_ANALOG_SBO_DW_DL, plugin_id, ele, 1, "mA", 1, 1);
        m_board_analog[plugin_id].push_back(pdata);
    }

}

void PDDM5Board::GenerateCurve()
{
    CsmCurve* pCurve = Singleton<CsmDataManager>::Instance().GetCurve();
    CsmDataCurve* pdata;

    Q_ASSERT(m_lstCode.size() == 1);
    const QString& ele = m_lstCode.first();

    foreach (int plugin_id, m_PluginID)
    {
        pdata = pCurve->CreateCurve(E_PDDM5_CURVE_CURR_C,  plugin_id, ele + "_道岔动作C相电流曲线", 1, "A", 25, 1);
        m_board_curve[plugin_id].push_back(pdata);
        pdata = pCurve->CreateCurve(E_PDDM5_CURVE_PHASE_C, plugin_id, ele + "_道岔动作C相相位曲线", 1, "度", 25, 1);
        m_board_curve[plugin_id].push_back(pdata);
        pdata = pCurve->CreateCurve(E_PDDM5_CURVE_CURR_B,  plugin_id, ele + "_道岔动作B相电流曲线", 1, "A", 25, 1);
        m_board_curve[plugin_id].push_back(pdata);
        pdata = pCurve->CreateCurve(E_PDDM5_CURVE_PHASE_B, plugin_id, ele + "_道岔动作B相相位曲线", 1, "度", 25, 1);
        m_board_curve[plugin_id].push_back(pdata);
        pdata = pCurve->CreateCurve(E_PDDM5_CURVE_CURR_A,  plugin_id, ele + "_道岔动作A相电流曲线", 1, "A", 25, 1);
        m_board_curve[plugin_id].push_back(pdata);
        pdata = pCurve->CreateCurve(E_PDDM5_CURVE_PHASE_A, plugin_id, ele + "_道岔动作A相相位曲线", 1, "度", 25, 1);
        m_board_curve[plugin_id].push_back(pdata);
    }
}

void PDDM5Board::GenerateOtherDev2()
{
    Q_ASSERT(m_other_dev.size() == 1);

    CsmDataDev* pdata = m_other_dev.first();

    // 添加A系模拟量
    foreach (CsmDataAnalog* var, m_board_analog[PluginID_A()]) {
        pdata->AddCJInfo(var);
    }

    // 添加B系模拟量
    foreach (CsmDataAnalog* var, m_board_analog[PluginID_B()]) {
        pdata->AddCJInfo(var);
    }

    // 添加主系曲线
    foreach (CsmDataCurve* var, m_board_curve[PluginID_Main()]) {
        pdata->AddCJInfo(var);
    }
}

//-//////////////////////////////////////////////////
CDDMBoard::CDDMBoard()
{
    m_BoardType = E_Board_CDDM;
}

CDDMBoard::~CDDMBoard()
{

}

void CDDMBoard::GenerateDigit()
{
    // 找出采集码位
    QVector<QString> v_di;
    QVector<QString> v_sbo;

    foreach (QString var, m_lstCode)
    {
        if(var.isEmpty())
            continue;

        if(var.endsWith("-DI"))
            v_di.push_back(var);
        else
            v_sbo.push_back(var);
    }

    RegisterDigit(v_di, BoardFactory::GetMaxDi(m_BoardType));
    RegisterDigit(v_sbo, BoardFactory::GetMaxSbo(m_BoardType));
}

//-//////////////////////////////////////////////////
SIOMBoard::SIOMBoard()
{
    m_BoardType = E_Board_SIOM;
}

SIOMBoard::~SIOMBoard()
{

}

void SIOMBoard::GenerateAnalog()
{
    CsmAnalog* pAnalog = Singleton<CsmDataManager>::Instance().GetAnalog();
    CsmDataAnalog* pdata;
    foreach (const QString& ele, m_lstCode)
    {
        if(ele.isEmpty())
            continue;

        foreach (int plugin_id, m_PluginID)
        {
            pdata = pAnalog->CreateAnalog(E_SIOM_ANALOG_DI_SBO_VOLT, plugin_id, ele, 1, "V", 1, 1);
            m_board_analog[plugin_id].push_back(pdata);
        }
    }

    // 每个SIOM板卡生成7个自检电源电压
    foreach (int plugin_id, m_PluginID)
    {
        for(int i=0; i<7; i++)
        {
            QString name = "自检电源电压_" + QString::number(i+1);
            pdata = pAnalog->CreateAnalog(E_SIOM_ANALOG_SELF_CHECK_VOLT, plugin_id, name, 1, "V", 1, 1);
            m_board_analog[plugin_id].push_back(pdata);
        }
    }
}

void SIOMBoard::GenerateOtherDev2()
{
    QVector<CsmDataAnalog*>& v_analog_A = m_board_analog[PluginID_A()];
    QVector<CsmDataAnalog*>& v_analog_B = m_board_analog[PluginID_B()];

    int count = 0;
    foreach (CsmDataDev* var, m_other_dev)
    {
        var->AddCJInfo(v_analog_A[count]);
        var->AddCJInfo(v_analog_B[count]);
        count++;
    }
}

//-//////////////////////////////////////////////////
HIOMBoard::HIOMBoard()
{
    m_BoardType = E_Board_HIOM;
}

HIOMBoard::~HIOMBoard()
{

}

void HIOMBoard::GenerateAnalog()
{
    CsmAnalog* pAnalog = Singleton<CsmDataManager>::Instance().GetAnalog();
    CsmDataAnalog* pdata;
    foreach (const QString& ele, m_lstCode)
    {
        if(ele.isEmpty())
            continue;

        foreach (int plugin_id, m_PluginID)
        {
            pdata = pAnalog->CreateAnalog(E_HIOM_ANALOG_DB_PORT_VOLT, plugin_id, ele, 1, "V", 1, 1);
            m_board_analog[plugin_id].push_back(pdata);
            pdata = pAnalog->CreateAnalog(E_HIOM_ANALOG_FB_PORT_VOLT, plugin_id, ele, 1, "V", 1, 1);
            m_board_analog[plugin_id].push_back(pdata);
            pdata = pAnalog->CreateAnalog(E_HIOM_ANALOG_SYB_PORT_VOLT, plugin_id, ele, 1, "V", 1, 1);
            m_board_analog[plugin_id].push_back(pdata);
        }
    }
}

void HIOMBoard::GenerateCurve()
{
    CsmCurve* pCurve = Singleton<CsmDataManager>::Instance().GetCurve();
    CsmDataCurve* pdata;
    foreach (const QString& ele, m_lstCode)
    {
        if(ele.isEmpty())
            continue;

        foreach (int plugin_id, m_PluginID)
        {
            pdata = pCurve->CreateCurve(E_HIOM_CURVE_CURR_A, plugin_id, ele + "_道岔动作A相电流曲线", 1, "A", 25, 1);
            m_board_curve[plugin_id].push_back(pdata);
            pdata = pCurve->CreateCurve(E_HIOM_CURVE_CURR_B, plugin_id, ele + "_道岔动作B相电流曲线", 1, "A", 25, 1);
            m_board_curve[plugin_id].push_back(pdata);
            pdata = pCurve->CreateCurve(E_HIOM_CURVE_CURR_C, plugin_id, ele + "_道岔动作C相电流曲线", 1, "A", 25, 1);
            m_board_curve[plugin_id].push_back(pdata);

        }
    }
}

void HIOMBoard::GenerateOtherDev2()
{
    Q_ASSERT(m_other_dev.size() == 1);

    CsmDataDev* pdata = m_other_dev.first();

    // 添加A系模拟量
    foreach (CsmDataAnalog* var, m_board_analog[PluginID_A()]) {
        pdata->AddCJInfo(var);
    }

    // 添加B系模拟量
    foreach (CsmDataAnalog* var, m_board_analog[PluginID_B()]) {
        pdata->AddCJInfo(var);
    }

    // 添加主系曲线
    foreach (CsmDataCurve* var, m_board_curve[PluginID_Main()]) {
        pdata->AddCJInfo(var);
    }
}
