#include "TisCfgGenerator.h"
#include "CommonMethod.h"
#include "TisCfgData.h"
#include "IpsManager.h"
#include "EcidManager.h"
#include "CsmDataManager.h"

CfgGenerator* CfgGenerator::m_instance = nullptr;

CfgGenerator::CfgGenerator()
{

}

CfgGenerator* CfgGenerator::ins()
{
    if(m_instance == nullptr)
        m_instance = new CfgGenerator();
    return m_instance;
}

QString CfgGenerator::inputPath() const
{
    return m_inputPath;
}

void CfgGenerator::setInputPath(const QString &inputPath)
{
    m_inputPath = inputPath;
}

QString CfgGenerator::outputPath() const
{
    return m_outputPath;
}

void CfgGenerator::setOutputPath(const QString &outputPath)
{
    m_outputPath = outputPath;
}

QString CfgGenerator::dbm() const
{
    return m_dbm;
}

void CfgGenerator::setDbm(const QString &dbm)
{
    m_dbm = dbm;
}

QString CfgGenerator::station_name() const
{
    return m_station_name;
}

void CfgGenerator::setStation_name(const QString &station_name)
{
    m_station_name = station_name;
}

QString CfgGenerator::station_no() const
{
    return m_station_no;
}

void CfgGenerator::setStation_no(const QString &station_no)
{
    m_station_no = station_no;
}

void CfgGenerator::GenerateCfg()
{
    if(!CommonMethod::IsFileExist(m_inputPath))
    {
        // 输入路径不存在
        return;
    }

    if(!CommonMethod::IsFileExist(m_outputPath))
    {
        // 输出路径不存在
        return;
    }



    // 加载配置文件
    TisCfgData::Ins()->Init(m_inputPath);

    // 生成IPS开关量和枚举量
    Singleton<IpsManager>::Instance().GenerateCsmData();

    // 转换接口码位表配置
    Singleton<EcidManager>::Instance().LoadEcidInfo(TisCfgData::Ins()->GetCodeTableCfg());

    // 生成ECID的Data
    Singleton<EcidManager>::Instance().GenerateData();

    // 输出配置（文件）
    Singleton<CsmDataManager>::Instance().WriteToFile(m_outputPath);
}
