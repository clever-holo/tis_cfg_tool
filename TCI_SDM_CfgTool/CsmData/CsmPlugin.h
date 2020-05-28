#ifndef CSMPLUGIN_H
#define CSMPLUGIN_H

#include <QString>
#include <QVector>

#define PluginType_IPS_Main     (1)
#define PluginType_IPS_A        (2)
#define PluginType_IPS_B        (3)
#define PluginType_Ecid_Main    (4)
#define PluginType_Ecid_A       (5)
#define PluginType_Ecid_B       (6)


struct PluginInfo
{
    int          _plugin_id;
    int          _plugin_type;
    int          _plugin_order;
    QString      _name1;
    QString      _name2;

};

class CsmPlugin
{
public:
    CsmPlugin();

public:
    PluginInfo RegisterPlugin(int plugin_type, const QString& name1, const QString& name2);

protected:
    QVector<PluginInfo>     m_plugin_list;

};

#endif // CSMPLUGIN_H
