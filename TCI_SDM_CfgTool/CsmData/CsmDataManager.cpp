#include "CsmDataManager.h"
#include "CsmAnalog.h"
#include "CsmDigit.h"
#include "CsmCurve.h"
#include "CsmEnum.h"
#include "CsmPlugin.h"
#include "CsmVirtualStatus.h"
#include "CsmDevice.h"
#include "CsmCBISpecial.h"
#include "CsmEcidHdw.h"
#include "CsmUserModi.h"
#include "CsmOtherFile.h"

CsmDataManager::CsmDataManager()
{
    m_plugin = new CsmPlugin();
    m_digit  = new CsmDigit();
    m_enum   = new CsmEnum();
    m_analog = new CsmAnalog();
    m_curve  = new CsmCurve();
    m_vs     = new CsmVirtualStatus();
    m_dev    = new CsmDevice();
    m_cbi_special = new CsmCBISpecial();
    m_ecid_hdw = new CsmEcidHdw();
    m_other_file = new CsmOtherFile();
}

CsmDataManager::~CsmDataManager()
{

}

CsmPlugin *CsmDataManager::GetPlugin()
{
    return m_plugin;
}

CsmDigit *CsmDataManager::GetDigit()
{
    return m_digit;
}

CsmEnum *CsmDataManager::GetEnum()
{
    return m_enum;
}

CsmAnalog *CsmDataManager::GetAnalog()
{
    return m_analog;
}

CsmCurve *CsmDataManager::GetCurve()
{
    return m_curve;
}

CsmVirtualStatus *CsmDataManager::GetVs()
{
    return m_vs;
}

CsmDevice *CsmDataManager::GetDev()
{
    return m_dev;
}

CsmCBISpecial *CsmDataManager::GetCBISpecila()
{
    return m_cbi_special;
}

void CsmDataManager::WriteToFile(const QString& outputPath)
{
    GenerateOtherData();

    WritePlugin(outputPath);
    WriteDigit(outputPath);
    WriteEnum(outputPath);
    WriteAnalog(outputPath);
    WriteCurve(outputPath);
    WriteVS(outputPath);
    WriteDev(outputPath);
    WriteCBISpecial(outputPath);
    WriteEcidHdw(outputPath);
    WriteUserModi(outputPath);
    WriteOtherfile(outputPath);
}

void CsmDataManager::WritePlugin(const QString &outputPath)
{
    m_plugin->WriteToFile(outputPath);
}

void CsmDataManager::WriteDigit(const QString &outputPath)
{
    m_digit->WriteToFile(outputPath);
}

void CsmDataManager::WriteEnum(const QString &outputPath)
{
    m_enum->WriteToFile(outputPath);
}

void CsmDataManager::WriteAnalog(const QString &outputPath)
{
    m_analog->WriteToFile(outputPath);
}

void CsmDataManager::WriteCurve(const QString &outputPath)
{
    m_curve->WriteToFile(outputPath);
}

void CsmDataManager::WriteVS(const QString &outputPath)
{
    m_vs->WriteToFile(outputPath);
}

void CsmDataManager::WriteDev(const QString& outputPath)
{
    m_dev->WriteToFile(outputPath);
}

void CsmDataManager::WriteCBISpecial(const QString &outputPath)
{
    m_cbi_special->WriteToFile(outputPath);
}

void CsmDataManager::WriteEcidHdw(const QString &outputPath)
{
    m_ecid_hdw->WriteToFile(outputPath);
}

void CsmDataManager::WriteUserModi(const QString &outputPath)
{
    m_user_modi->WriteToFile(outputPath);
}

void CsmDataManager::WriteOtherfile(const QString &outputPath)
{
    m_other_file->WriteToFile(outputPath);
}

void CsmDataManager::GenerateOtherData()
{
    // 虚拟状态量_接口状态 (可以考虑挪到接口类中，每添加一个接口，就生成一个接口状态VS)
    const QVector<PluginInfo> & v_plugin = m_plugin->GetAllPlugin();
    foreach (const PluginInfo& var, v_plugin)
    {
        m_vs->CreateVS(DEF_VS_PLUGIN_STATUS, var._name1);
    }
}

