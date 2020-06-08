#ifndef CSMVIRTUALSTATUS_H
#define CSMVIRTUALSTATUS_H

#include <QString>
#include <QVector>
#include <QMap>

#define    DEF_VS_PLUGIN_STATUS             (1)
#define    DEF_VS_DEV_ALARM_STATUS          (3)
#define    DEF_VS_DEV_STOPUSE_STATUS        (4)
#define    DEF_VS_DEV_OVERHAUL_STATUS       (5)
#define    DEF_VS_DEV_STARE_CTRL_STATUS     (6)
#define    DEF_VS_DEV_CONFIRM_STATUS        (8)
#define    DEF_VS_NET_NODE_STATUS           (15)
#define    DEF_VS_TCC_SPECIAL_STATUS        (16)

#define    DEF_VS_PLUGIN_ID                 (1003027)


struct CsmDataVS
{
    int         _vs_type;
    int         _vs_plugin_id;
    QString     _vs_uuid;
    QString     _vs_name;
    int         _vs_order;
};


class CsmVirtualStatus
{
public:
    CsmVirtualStatus();

public:
    CsmDataVS *CreateVS(int vs_type, const QString& vs_name);
    void WriteToFile(const QString& outputPath);

    static QString GetVsTypeName(int vs_type);

protected:
    void GenerateConstVS();

private:
    QMap<int, QVector<CsmDataVS*>>     m_vs;

};

#endif // CSMVIRTUALSTATUS_H
