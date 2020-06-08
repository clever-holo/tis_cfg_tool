#include "CsmVirtualStatus.h"
#include "CsmDigit.h"
#include <QChar>
#include "MyIniFile.h"
#include "CommonMethod.h"


CsmVirtualStatus::CsmVirtualStatus()
{
    QVector<int> v_type;
    v_type.push_back(DEF_VS_DEV_ALARM_STATUS);
    v_type.push_back(DEF_VS_DEV_STOPUSE_STATUS);
    v_type.push_back(DEF_VS_DEV_OVERHAUL_STATUS);
    v_type.push_back(DEF_VS_DEV_STARE_CTRL_STATUS);
    v_type.push_back(DEF_VS_DEV_CONFIRM_STATUS);

    foreach(int var, v_type)
    {
        for(int i=0; i<4; i++)
            CreateVS(var, QString("默认分组总状态%1").arg(i+1));
    }
}

CsmDataVS *CsmVirtualStatus::CreateVS(int vs_type, const QString &vs_name)
{
    QVector<CsmDataVS*>& v_vs = m_vs[vs_type];

    CsmDataVS* vs_unit = new CsmDataVS();
    vs_unit->_vs_type      = vs_type;
    vs_unit->_vs_plugin_id = DEF_VS_PLUGIN_ID;
    vs_unit->_vs_uuid      = QString("%1%2%3").arg(DEF_VS_PLUGIN_ID, 8, 10, QChar('0')).arg(vs_type, 2, 10, QChar('0')).arg(v_vs.size()+1, 7, 10, QChar('0'));
    vs_unit->_vs_name      = vs_name;
    vs_unit->_vs_order     = v_vs.size();

    v_vs.push_back(vs_unit);

    return vs_unit;
}

void CsmVirtualStatus::WriteToFile(const QString &outputPath)
{
    QString DBM = "ABC";
    //QString file = outputPath + "\\Project\\DataCfg\\" + DBM + "\\Virtual_Status.INI";
    QString file = outputPath + "\\Virtual_Status.INI";
    MyIniFile myfile(file);
    if(myfile.Open(QIODevice::WriteOnly | QIODevice::Truncate))
    {
        // 汇总信息
        myfile.WriteSec("汇总信息");
        myfile.Write("个数", QString::number(m_vs.size()));

        QMap<int, QVector<CsmDataVS*>>::iterator it = m_vs.begin();
        int plugin_count = 1;
        while (it != m_vs.end())
        {
            QString key = QString::number(plugin_count);
            QString val = QString::number(it.key()) + "," + QString::number(DEF_VS_PLUGIN_ID) + "," +  QString::number(it.value().size());
            myfile.Write(key, val);

            it++;
            plugin_count++;
        }

        //

        it = m_vs.begin();
        while (it != m_vs.end())
        {
            QString sec = GetVsTypeName(it.key()) + "\\" + QString::number(it.key()) + "\\" + QString::number(DEF_VS_PLUGIN_ID);
            myfile.WriteSec(sec);

            QVector<CsmDataVS*>& v_digit = it.value();
            for(int i=0; i<v_digit.size(); i++)
            {
                QString key = QString("%1").arg(i+1, -4, 10);
                QString val;
                val += QString("%1,").arg(v_digit[i]->_vs_uuid, 30);
                val += QString("%1,").arg(v_digit[i]->_vs_name, 30 - CommonMethod::ChineseNumber(v_digit[i]->_vs_name));
                val += QString("%1").arg(v_digit[i]->_vs_order, 6);

                myfile.Write(key, val);
            }
            it++;
        }
        myfile.Close();
    }
}

QString CsmVirtualStatus::GetVsTypeName(int vs_type)
{
    if   (vs_type == DEF_VS_PLUGIN_STATUS)           return "接口状态";
    else if(vs_type == DEF_VS_DEV_ALARM_STATUS)      return "设备报警状态";
    else if(vs_type == DEF_VS_DEV_STOPUSE_STATUS)    return "设备停用状态";
    else if(vs_type == DEF_VS_DEV_OVERHAUL_STATUS)   return "设备检修状态";
    else if(vs_type == DEF_VS_DEV_STARE_CTRL_STATUS) return "设备盯控状态";
    else if(vs_type == DEF_VS_DEV_CONFIRM_STATUS)    return "设备确认状态";
    else if(vs_type == DEF_VS_NET_NODE_STATUS)       return "联锁节点网络状态";
    else if(vs_type == DEF_VS_TCC_SPECIAL_STATUS)    return "列控特殊状态";
    else return "未知";
}

void CsmVirtualStatus::GenerateConstVS()
{

}

