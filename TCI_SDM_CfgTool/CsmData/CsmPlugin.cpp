#include "CsmPlugin.h"
#include "MyIniFile.h"
#include "CommonMethod.h"
#include "TisCfgGenerator.h"

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

void CsmPlugin::WriteToFile(const QString &outputPath)
{
    QString sta_name = CfgGenerator::ins()->station_name();
    QString file = outputPath + "\\" + sta_name + "\\Project\\PluginCfg\\PLUGIN_LIST.INI";
    MyIniFile myfile(file);
    if(myfile.Open(QIODevice::WriteOnly | QIODevice::Truncate))
    {
        // 注释
        myfile.WriteLine(";;汇总信息：序号 = 主类型码, 子类型个数");
        myfile.WriteLine(";;汇总信息\\X: X=主类型号 序号 = 子类型号, 设备个数, 设备最大采集项数");
        myfile.WriteLine(";;设备采集信息\\X\\Y\\Z: X=主类型号 Y=子类型号 Z=设备号 序号 = UUID, 数据类别（0开关1模拟2曲线4枚举）, 数据类型号, 接口号, 码位, 采集项使用模式, 接口标识号, 逻辑子号");
        myfile.WriteLine();
        myfile.WriteLine();

        //
        QString sec = "本站接口列表";
        myfile.WriteSec(sec);

        QString key = "总数";
        QString val = QString::number(m_plugin_list.size());
        myfile.Write(key, val);

        int count = 0;
        foreach (const PluginInfo& var, m_plugin_list)
        {
            count++;
            key = QString("%1").arg(count, -3);
            val = QString("%1,%2,  %3,%4,  %5")
                    .arg(var._plugin_id, 10)
                    .arg(var._plugin_type, 2)
                    .arg(var._name1, -15 + CommonMethod::ChineseNumber(var._name1))
                    .arg(var._plugin_order, 3)
                    .arg(var._name2, -15 + CommonMethod::ChineseNumber(var._name2));
            myfile.Write(key, val);

        }

        myfile.WriteSec("本站虚拟接口列表");
        myfile.Write("总数", "0");

        myfile.WriteSec("数据版本");
        myfile.Write("版本号", "1");

        myfile.Close();
    }
}
