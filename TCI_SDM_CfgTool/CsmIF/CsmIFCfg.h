#ifndef CSMIFCFG_H
#define CSMIFCFG_H

#include <QString>
#include "CsmIF_StationInfo.h"

class CsmIFCfg
{
private:
    CsmIFCfg();
    static CsmIFCfg* m_instance;

public:
    static CsmIFCfg* ins();
    virtual ~CsmIFCfg();

public:
    void GenerateCsmIF(const QString& str_output_path);

protected:
    void WriteStationInfo_StationCode();

private:
    QString    m_output_path;

    CsmIF_StationInfo   m_sta_info;
};

#endif // CSMIFCFG_H
