#ifndef ITISCFGIF_H
#define ITISCFGIF_H
#include <qstring.h>

class InputFileCfg;
class CodeTableCfg;
class AdsVarCfg;
class PanelLampCfg;

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

    InputFileCfg* GetInputFileCfg() {return m_pInputFileCfg;}

    CodeTableCfg *GetCodeTableCfg() const;

    AdsVarCfg *GetAdsVarCfg() const;

    PanelLampCfg* GetPanelLampCfg() const;

protected:
    InputFileCfg*           m_pInputFileCfg;
    CodeTableCfg*           m_pCodeTableCfg;
    AdsVarCfg*              m_pAdsVarCfg;
    PanelLampCfg*           m_pPanelLampCfg;
};



#endif // ITISCFGIF_H
