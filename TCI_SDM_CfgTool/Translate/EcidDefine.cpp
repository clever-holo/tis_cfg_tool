#include "EcidDefine.h"
#include "CsmDataManager.h"
#include "BoardDefine.h"

ECID::ECID(int order)
{
   setOrder(order);
}

bool ECID::AddBoard(BoardBase *board)
{
    m_lstBoard.push_back(board);
    board->setEcid(this);
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
