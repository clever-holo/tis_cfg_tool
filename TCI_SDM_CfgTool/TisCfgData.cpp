#include "TisCfgData.h"
#include "CodeTable.h"
#include "AdsVarCfg.h"
#include "PanelLampCfg.h"
#include "TisCfgGenerator.h"
#include "IPTable.h"
#include "BlockCfg.h"
#include "GroundEquipmentTable.h"
#include "TisTisTable.h"
#include "TisZpwTable.h"
#include "IFInfoTable.h"

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
    m_pCodeTableCfg = new CodeTableCfg();
    m_pAdsVarCfg    = new AdsVarCfg();
    m_pPanelLampCfg = new PanelLampCfg();
    m_pIPTable      = new IPTable();
    m_pBlockCfg     = new BlockCfg();
    m_pGroundEquCfg = new GroundEquipmentTable();
    m_pTisTisCfg    = new TisTisTable();
    m_pTisZpwCfg    = new TisZpwTable();
    m_pIFInfoCfg    = new IFInfoTable();
}

TisCfgData::~TisCfgData()
{
    DEL_PTR(m_pCodeTableCfg);
    DEL_PTR(m_pAdsVarCfg);
    DEL_PTR(m_pPanelLampCfg);
    DEL_PTR(m_pIPTable);
    DEL_PTR(m_pBlockCfg);
    DEL_PTR(m_pGroundEquCfg);
    DEL_PTR(m_pTisTisCfg);
    DEL_PTR(m_pTisZpwCfg);
    DEL_PTR(m_pIFInfoCfg);
}


bool TisCfgData::Init(const QString &inputPath)
{
    QString filePath = inputPath ;
    m_pCodeTableCfg->LoadIFCodeTableCfg(filePath);

    filePath = inputPath;
    m_pAdsVarCfg->LoadAdsVarCfg(filePath);

    filePath = inputPath + "\\ECID_BOARD_PANNEL.cfg";
    m_pPanelLampCfg->LoadPanelLamp(filePath);

    filePath = inputPath;
    m_pIPTable->LoadCfg(filePath);

    filePath = inputPath;
    m_pBlockCfg->LoadCfg(filePath);

    filePath = inputPath;
    m_pGroundEquCfg->LoadCfg(filePath);

    filePath = inputPath;
    m_pTisTisCfg->LoadCfg(filePath);

    filePath = inputPath;
    m_pTisZpwCfg->LoadCfg(filePath);

    filePath = inputPath;
    m_pIFInfoCfg->LoadCfg(filePath);

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

PanelLampCfg *TisCfgData::GetPanelLampCfg() const
{
    return m_pPanelLampCfg;
}

QString TisCfgData::GetStaName() const
{
    return m_pCodeTableCfg->sta_name();
}

QString TisCfgData::GetStano() const
{
    return m_pCodeTableCfg->sta_no();
}

void TisCfgData::GetAllStationNo(QVector<int> &v_sta_no) const
{
    m_pAdsVarCfg->GetAllStationNo(v_sta_no);
}

BlockCfg *TisCfgData::GetBlockCfg() const
{
    return m_pBlockCfg;
}

GroundEquipmentTable *TisCfgData::pGroundEquCfg() const
{
    return m_pGroundEquCfg;
}

TisTisTable *TisCfgData::pTisTisCfg() const
{
    return m_pTisTisCfg;
}

TisZpwTable *TisCfgData::pTisZpwCfg() const
{
    return m_pTisZpwCfg;
}

IFInfoTable *TisCfgData::pIFInfoCfg() const
{
    return m_pIFInfoCfg;
}


