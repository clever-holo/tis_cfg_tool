#include "EcidDefine.h"
#include "CsmDataManager.h"
#include "BoardDefine.h"
#include "CsmDevice.h"

ECID::ECID(int order)
{
   setOrder(order);
}

bool ECID::AddBoard(BoardBase *board)
{
    m_lstBoard.push_back(board);
    board->setEcid(this);
    board->setOrderInEcid(m_lstBoard.size());
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

PluginInfo ECID::plugin_B() const
{
    return m_plugin_B;
}

const CsmDataDev *ECID::DevA() const
{
    return m_ecid_dev_A;
}

const CsmDataDev *ECID::DevB() const
{
    return m_ecid_dev_B;
}

const QVector<BoardBase *> ECID::GetAllBoard() const
{
    return m_lstBoard;
}

PluginInfo ECID::plugin_A() const
{
    return m_plugin_A;
}

PluginInfo ECID::plugin_main() const
{
    return m_plugin_main;
}

//-/////////////////////////////////////////
// 生成CsmData
void ECID::GenerateData()
{
    // 生成接口
    GeneratePlugin();

    // 生成设备
    GenerateDev();

    // 每块板卡生成CSMData
    foreach (BoardBase* pboard, m_lstBoard) {
        pboard->GenerateData();
    }

}

void ECID::GeneratePlugin()
{
    CsmPlugin* pPlugin =  Singleton<CsmDataManager>::Instance().GetPlugin();
    QString ecid_name = QString("执行单元%1").arg(m_Order);
    m_plugin_main = pPlugin->RegisterPlugin(PluginType_Ecid_Main, ecid_name + "_主系", ecid_name + "_主系");
    m_plugin_A = pPlugin->RegisterPlugin(PluginType_Ecid_A, ecid_name + "_A系", ecid_name + "_A系");
    m_plugin_B = pPlugin->RegisterPlugin(PluginType_Ecid_B, ecid_name + "_B系", ecid_name + "_B系");
}

void ECID::GenerateDev()
{
    CsmDevice* pDev     = Singleton<CsmDataManager>::Instance().GetDev();
    m_ecid_dev_A = pDev->CreateDev(CsmDev_OC_OC, QString("执行单元%1_A系").arg(m_Order), "", "");
    m_ecid_dev_B = pDev->CreateDev(CsmDev_OC_OC, QString("执行单元%1_B系").arg(m_Order), "", "");
}
