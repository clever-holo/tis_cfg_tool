#include "CsmDataManager.h"
#include "CsmAnalog.h"
#include "CsmDigit.h"
#include "CsmCurve.h"
#include "CsmEnum.h"
#include "CsmPlugin.h"

CsmDataManager::CsmDataManager()
{
    m_plugin = new CsmPlugin();
    m_digit  = new CsmDigit();
    m_enum   = new CsmEnum();
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

void CsmDataManager::WriteToFile()
{

}

void CsmDataManager::WriteDigit()
{

}
