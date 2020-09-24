#ifndef IPTABLE_H
#define IPTABLE_H

#include <QString>
#include <QVector>
#include "ExcelWrapper.h"

enum NetHostType
{
    HostType_NULL = 0,
    HostType_IPS,
    HostType_SDM,
    HostType_MMI,
    HostType_OC,
    HostType_OC_LEU,
    HostType_RSSP1,		// 外部RSSP1通信节点
    HostType_RESERVE,
};

///
/// \brief The NetHost class
///
class NetHost
{
public:
    NetHost() {m_host_type = HostType_NULL;}
    static NetHost *CreatenetHost(NetHostType type, const QString &host_name);
    static NetHostType ParseHostType(const QString& host_name);

public:
    QString host_name() const;

    void setHost_name(const QString &host_name);

protected:
    NetHostType     m_host_type;
    QString         m_host_name;
};

///
/// \brief The SdmHost class
///
class SdmHost : public NetHost
{
public:
    SdmHost() {m_host_type = HostType_SDM;}
};

///
/// \brief The SdmHost class
///
class IpsHost : public NetHost
{
public:
    IpsHost() {m_host_type = HostType_IPS;}
};

///
/// \brief The SdmHost class
///
class MmiHost : public NetHost
{
public:
    MmiHost() {m_host_type = HostType_MMI;}
};

///
/// \brief The SdmHost class
///
class OcHost : public NetHost
{
public:
    OcHost() {m_host_type = HostType_OC;}
};

///
/// \brief The SdmHost class
///
class OcLeuHost : public NetHost
{
public:
    OcLeuHost() {m_host_type = HostType_OC_LEU;}
};

///
/// \brief The MmiHost class
///
class Rssp1Host : public NetHost
{
public:
    Rssp1Host() {m_host_type = HostType_RSSP1;}
};

///
/// \brief The IPTable class
///
class IPTable
{
public:
    IPTable();

public:
    void LoadCfg(const QString &inputFilePath);

    NetHost* GetNetHost(const QString& host_name);

protected:
    void LoadInternal(const QString &inputFilePath);
    void LoadExternal(const QString &inputFilePath);

    void LoadOneSheet(const ExcelSheet& sheet);
    void Addhost(const QString& host_name);

protected:
    ExcelBook           m_excelbook;

    QVector<NetHost*>   m_net_hosts;

};

#endif // IPTABLE_H
