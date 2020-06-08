#include "CsmPlugin.h"

#define  PLUGIN_BEGIN   (1050000)

CsmPlugin::CsmPlugin()
{

}

PluginInfo CsmPlugin::RegisterPlugin(int plugin_type, const QString &name1, const QString &name2)
{
    PluginInfo plugin_info;
    plugin_info._plugin_order = m_plugin_list.size();
    plugin_info._plugin_type  = plugin_type;
    plugin_info._plugin_id    = PLUGIN_BEGIN +  plugin_info._plugin_order + 1;
    plugin_info._name1        = name1;
    plugin_info._name2        = name2;

    m_plugin_list.push_back(plugin_info);
    return plugin_info;
}

int CsmPlugin::GetPluginType(int plugin_id) const
{
    foreach(const PluginInfo& var, m_plugin_list)
    {
        if(var._plugin_id == plugin_id)
            return var._plugin_type;
    }
    return -1;
}

const QVector<PluginInfo> &CsmPlugin::GetAllPlugin() const
{
    return m_plugin_list;

}
