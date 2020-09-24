#ifndef ITISCFGIF_H
#define ITISCFGIF_H
#include <qstring.h>

class CodeTableCfg;
class AdsVarCfg;
class PanelLampCfg;
class IPTable;
class BlockCfg;
class GroundEquipmentTable;
class TisTisTable;
class TisZpwTable;
class IFInfoTable;

class TisCfgData
{
protected:
    TisCfgData();
    ~TisCfgData();
    static TisCfgData* m_ins;

public:
    static TisCfgData* Ins();

public:
    bool Init(const QString& inputPath);

    CodeTableCfg *GetCodeTableCfg() const;

    AdsVarCfg *GetAdsVarCfg() const;

    PanelLampCfg* GetPanelLampCfg() const;

    QString GetStaName() const;
    QString GetStano() const;

    void GetAllStationNo(QVector<int>& v_sta_no) const;

    BlockCfg *GetBlockCfg() const;

    GroundEquipmentTable *pGroundEquCfg() const;

    TisTisTable *pTisTisCfg() const;

    TisZpwTable *pTisZpwCfg() const;

    IFInfoTable *pIFInfoCfg() const;

protected:
    CodeTableCfg*           m_pCodeTableCfg;
    AdsVarCfg*              m_pAdsVarCfg;
    PanelLampCfg*           m_pPanelLampCfg;
    IPTable*                m_pIPTable;
    BlockCfg*               m_pBlockCfg;
    GroundEquipmentTable*   m_pGroundEquCfg;
    TisTisTable*            m_pTisTisCfg;
    TisZpwTable*            m_pTisZpwCfg;
    IFInfoTable*            m_pIFInfoCfg;
};



#endif // ITISCFGIF_H
