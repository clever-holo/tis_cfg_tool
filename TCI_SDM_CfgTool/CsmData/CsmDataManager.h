#ifndef CSMDATAMANAGER_H
#define CSMDATAMANAGER_H

#include "Singleton.h"
#include <QString>

class CsmPlugin;
class CsmDigit;
class CsmEnum;
class CsmAnalog;
class CsmCurve;
class CsmVirtualStatus;
class CsmDevice;
class CsmCBISpecial;

class CsmDataManager
{
public:
    CsmDataManager();
    ~CsmDataManager();

    friend class Singleton<CsmDataManager>;

public:
    CsmPlugin* GetPlugin();
    CsmDigit*  GetDigit();
    CsmEnum*   GetEnum();
    CsmAnalog* GetAnalog();
    CsmCurve*  GetCurve();
    CsmVirtualStatus* GetVs();
    CsmDevice *GetDev();
    CsmCBISpecial *GetCBISpecila();

    void    WriteToFile(const QString& outputPath);

protected:
    void    WritePlugin(const QString& outputPath);
    void    WriteDigit(const QString& outputPath);
    void    WriteEnum(const QString& outputPath);
    void    WriteAnalog(const QString& outputPath);
    void    WriteCurve(const QString& outputPath);
    void    WriteVS(const QString& outputPath);
    void    WriteDev(const QString& outputPath);
    void    WriteCBISpecial(const QString& outputPath);

    void    GenerateOtherData();

protected:
    CsmPlugin*          m_plugin;
    CsmDigit*           m_digit;
    CsmEnum*            m_enum;
    CsmAnalog*          m_analog;
    CsmCurve*           m_curve;
    CsmVirtualStatus*   m_vs;
    CsmDevice*          m_dev;
    CsmCBISpecial*      m_cbi_special;
};

#endif // CSMDATAMANAGER_H
