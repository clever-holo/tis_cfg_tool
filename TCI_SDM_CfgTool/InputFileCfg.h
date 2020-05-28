#ifndef IINPUTFILECFGIF_H
#define IINPUTFILECFGIF_H
#include <qvector.h>
#include <qstringlist.h>

class IInputFileCfgIF
{

};


class InputFileCfg  : IInputFileCfgIF
{
public:
    InputFileCfg();
    ~InputFileCfg();

public:
    bool LoodInputFileCfg(const QString& filePath);
    bool GetAdsVarStationLst(QStringList& vAdsvar) const;

private:
    QStringList m_vAdsvar;
};

#endif // IINPUTFILECFGIF_H
