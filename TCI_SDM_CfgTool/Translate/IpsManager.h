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
    void AddDigit(const QMap<int, QString>& mpVar);


private:
    PluginInfo  m_plugin_main;
    PluginInfo  m_plugin_A;
    PluginInfo  m_plugin_B;

    QVector<CsmDataDigit>  m_digit;
    QVector<CsmDataDigit>  m_enum;
};

#endif // IPSMANAGER_H
