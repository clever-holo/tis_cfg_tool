#ifndef IPSMANAGER_H
#define IPSMANAGER_H

#include <QVector>
#include <QMap>
#include "Singleton.h"
#include "CsmDataDefine.h"
#include "CsmPlugin.h"

class IpsManager
{
public:
    IpsManager();
    ~IpsManager();

    friend class Singleton<IpsManager>;

public:
    void GenerateCsmData();

protected:
    void GeneratePlugin();
    void GenerateDigit();
    void GenerateEnum();
    void GenerateDev();
    void AddDigit(const QMap<int, QString>& mpVar);


private:
    PluginInfo  m_plugin_main;
    PluginInfo  m_plugin_A;
    PluginInfo  m_plugin_B;

    QMap<int, QVector<CsmDataDigit>>  m_mp_digit;
    QVector<CsmDataEnum*>   m_mp_enum;
    QVector<int>           m_dev_type;
};

#endif // IPSMANAGER_H
