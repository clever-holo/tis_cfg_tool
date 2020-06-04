#include "IpsManager.h"
#include "TisCfgData.h"
#include "AdsVarCfg.h"
#include "CsmDataManager.h"
#include "CsmPlugin.h"
#include "CsmDigit.h"
#include "CsmEnum.h"

//*///
struct board_alarm_enum
{
    QString _name;
    int     _enum_type;
    int     _is_valid;
    int     _cj_freq;
};

const board_alarm_enum c_board_alarm_enum[] =
{
    {"A系电源状态",    1, 1, 1 },
    {"A系风扇状态",    2, 1, 1 },
    {"A系STBY状态",   3, 1, 1 },
    {"B系电源状态",    1, 1, 1 },
    {"B系风扇状态",    2, 1, 1 },
    {"B系STBY状态",   4, 1, 1 },
    {"同步通道1状态",  5, 1, 1 },
    {"同步通道2状态",  6, 1, 1 },
    {"LVDS通道1状态", 7, 1, 1 },
    {"LVDS通道2状态", 8, 1, 1 },
    {"看门狗状态",     9, 1, 1 },
    {"启动模式状态",   10, 1, 1 },
    {"A系MPU1状态",   11, 1, 1 },
    {"B系MPU1状态",   11, 1, 1 },
    {"A系MPU2状态",   12, 1, 1 },
    {"B系MPU2状态",   12, 1, 1 },
    {"A系MNCU状态",   13, 1, 1 },
    {"B系MNCU状态",   13, 1, 1 },
    {"A系MCU状态",    14, 1, 1 },
    {"B系MCU状态",    14, 1, 1 },
    {"A系MNCU2状态",  15, 1, 1 },
    {"B系MNCU2状态",  15, 1, 1 },
    {"A系MCU2状态",   18, 1, 1 },
    {"B系MCU2状态",   18, 1, 1 },
    {"SDLU1状态",     19, 1, 1 },
    {"SDLU2状态",     20, 1, 1 },
    {"SDLU3状态",     21, 1, 1 },
    {"SDLU4状态",     22, 1, 1 },
};

//*////////////////////////////////////////////////////////
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
    CsmEnum* pEnum = Singleton<CsmDataManager>::Instance().GetEnum();

    int cnt = sizeof(c_board_alarm_enum)/sizeof(board_alarm_enum);
    for(int i=0; i<cnt; i++)
    {
       pEnum->CreateEnum(m_plugin_main._plugin_id,
                         c_board_alarm_enum[i]._name,
                         c_board_alarm_enum[i]._enum_type,
                         c_board_alarm_enum[i]._is_valid,
                         c_board_alarm_enum[i]._cj_freq);
    }
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
