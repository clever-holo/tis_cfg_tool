#include "InputFileCfg.h"
#include <qsettings.h>
#include <qfile.h>
#include <qtextcodec.h>

InputFileCfg::InputFileCfg()
{

}

InputFileCfg::~InputFileCfg()
{

}

bool InputFileCfg::LoodInputFileCfg(const QString &filePath)
{
    if(!QFile(filePath).exists())
        return false;

    QSettings *configIni = new QSettings(filePath,QSettings::IniFormat);
    configIni->setIniCodec(QTextCodec::codecForName("System"));
    configIni->beginGroup("INPUT");
    QString strAdsvar = configIni->value("ADSVAR").toString().trimmed();
    m_vAdsvar = strAdsvar.split("#");
    delete configIni;

    return true;
}

bool InputFileCfg::GetAdsVarStationLst(QStringList &vAdsvar) const
{
    vAdsvar = m_vAdsvar;
    return true;
}
