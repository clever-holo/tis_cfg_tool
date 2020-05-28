#include "IpsManager.h"
#include "TisCfgData.h"
#include "AdsVarCfg.h"
#include "CsmDataManager.h"
#include "CsmPlugin.h"
#include "CsmDigit.h"
#include "CsmEnum.h"

IpsManager::IpsManager()
{

}

IpsManager::~IpsManager()
{

}

void IpsManager::GenerateCsmData()
{
   GeneratePlugin();
   GenerateDigit();
   GenerateEnum();
}

void IpsManager::GeneratePlugin()
{
   CsmPlugin* pPlugin =  Singleton<CsmDataManager>::Instance().GetPlugin();
   m_plugin_main = pPlugin->RegisterPlugin(PluginType_IPS_Main, "TISPS主机", "TISPS主机");
   m_plugin_A = pPlugin->RegisterPlugin(PluginType_IPS_A, "TISPS_A机", "TISPS_A机");
   m_plugin_B = pPlugin->RegisterPlugin(PluginType_IPS_B, "TISPS_B机", "TISPS_B机");
}

void IpsManager::GenerateDigit()
{
    AdsVarCfg* pVarCfg = TisCfgData::Ins()->GetAdsVarCfg();
    const QVector<SingleStationAdsVar>& var_info = pVarCfg->GetVarInfo();

    for(int i=0; i<var_info.size(); i++)
    {
        const SingleStationAdsVar& singles_station = var_info[i];
        AddDigit(singles_station.m_mpIndiCode);
        AddDigit(singles_station.m_mpCtrlCode);
    }

}

void IpsManager::GenerateEnum()
{

}

void IpsManager::AddDigit(const QMap<int, QString> &mpVar)
{
     CsmDigit* pDigit = Singleton<CsmDataManager>::Instance().GetDigit();
     QMap<int, QString>::const_iterator it = mpVar.begin();
     for(; it != mpVar.end(); it++)
     {
        pDigit->CreateDigit(m_plugin_main._plugin_id, it.value(), 0, 0, 1, 0, 1, 0);
        pDigit->CreateDigit(m_plugin_A._plugin_id,    it.value(), 0, 0, 1, 0, 1, 0);
        pDigit->CreateDigit(m_plugin_B._plugin_id,    it.value(), 0, 0, 1, 0, 1, 0);
     }
}
