#include "CsmDataManager.h"
#include "CsmAnalog.h"
#include "CsmDigit.h"
#include "CsmCurve.h"
#include "CsmEnum.h"
#include "CsmPlugin.h"
#include <QSettings>

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

void CsmDataManager::WriteToFile(const QString& outputPath)
{
    WriteDigit(outputPath);
    WriteEnum(outputPath);
}

void CsmDataManager::WriteDigit(const QString &outputPath)
{
    m_digit->WriteToFile(outputPath);
}

void CsmDataManager::WriteEnum(const QString &outputPath)
{
    m_enum->WriteToFile(outputPath);
}

