#include "TisCfgData.h"
#include "InputFileCfg.h"
#include "CodeTable.h"
#include "AdsVarCfg.h"

#define DEL_PTR(ptr) if(ptr) {\
                        delete ptr;\
                        ptr = nullptr;}

TisCfgData* TisCfgData::m_ins = nullptr;

TisCfgData* TisCfgData::Ins()
{
    if(m_ins == nullptr)
        m_ins = new TisCfgData();
    return m_ins;
}

TisCfgData::TisCfgData()
{
    m_pInputFileCfg = new InputFileCfg();
    m_pCodeTableCfg = new CodeTableCfg();
    m_pAdsVarCfg    = new AdsVarCfg();
}

TisCfgData::~TisCfgData()
{
    DEL_PTR(m_pInputFileCfg)
    DEL_PTR(m_pCodeTableCfg)
    DEL_PTR(m_pAdsVarCfg)
}


bool TisCfgData::Init(const QString &inputPath)
{
    QString filePath = inputPath + "\\输入文件配置.ini";
    m_pInputFileCfg->LoodInputFileCfg(filePath);

    filePath = inputPath + "\\接口码位表.xls";
    m_pCodeTableCfg->LoadIFCodeTableCfg(filePath);

    filePath = inputPath;
    m_pAdsVarCfg->LoadAdsVarCfg(filePath);

    return true;
}

CodeTableCfg *TisCfgData::GetCodeTableCfg() const
{
    return m_pCodeTableCfg;
}

AdsVarCfg *TisCfgData::GetAdsVarCfg() const
{
    return m_pAdsVarCfg;
}


