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

    //
    Singleton<EcidManager>::Instance().LoadEcidInfo(TisCfgData::Ins()->GetCodeTableCfg());

    // 输出配置（文件）
    Singleton<CsmDataManager>::Instance().WriteToFile();
}
