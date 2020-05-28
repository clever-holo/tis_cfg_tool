#ifndef CSMDATAMANAGER_H
#define CSMDATAMANAGER_H

#include "Singleton.h"

class CsmPlugin;
class CsmDigit;
class CsmEnum;

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

    void    WriteToFile();

protected:
    void    WriteDigit();


protected:
    CsmPlugin*  m_plugin;
    CsmDigit*   m_digit;
    CsmEnum*    m_enum;
};

#endif // CSMDATAMANAGER_H
