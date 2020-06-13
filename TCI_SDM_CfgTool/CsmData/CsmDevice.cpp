#include "CsmDevice.h"
#include "CsmPlugin.h"
#include "CsmDataManager.h"
#include "MyIniFile.h"

#define DEF_DEV_UUID_HEAD    "10086"

CsmDevice::CsmDevice()
{

}

CsmDataDev *CsmDevice::CreateDev(int dev_full_type, const QString &name, const QString &vs_order, const QString &comm_order)
{
    static int dev_count = 0;
    dev_count++;

    int main_type = dev_full_type / 100;
    int sub_type  = dev_full_type % 100;

    QVector<CsmDataDev*>& v_dev = m_dev[main_type][sub_type];

    CsmDataDev* dev_unit = new CsmDataDev();
    dev_unit->_uuid             = DEF_DEV_UUID_HEAD + QString("%1").arg(dev_count, 8, 10, QChar('0'));
    dev_unit->_name             = name;
    dev_unit->_tle_name         = name;
    dev_unit->_dev_full_type    = dev_full_type;
    dev_unit->_logic_type       = "";
    dev_unit->_logic_group      = "";
    dev_unit->_vs_order         = vs_order;
    dev_unit->_comm_order       = comm_order;
    dev_unit->_comm_rel         = "";
    v_dev.push_back(dev_unit);

    return dev_unit;
}

void CsmDevice::WriteToFile(const QString &outputPath)
{
    QString DBM = "ABC";
    //QString file = outputPath + "\\Project\\DataCfg\\" + DBM + "\\REAL_EQU.INI";
    QString file = outputPath + "\\REAL_EQU.INI";
    MyIniFile myfile(file);
    if(myfile.Open(QIODevice::WriteOnly | QIODevice::Truncate))
    {
        //*/////////////////////////////////////////////////////////////
        // 注释
        myfile.WriteLine(";;汇总信息：序号 = 主类型码, 子类型个数");
        myfile.WriteLine(";;汇总信息\\X: X=主类型号 序号 = 子类型号, 设备个数, 设备最大采集项数");
        myfile.WriteLine(";;设备采集信息\\X\\Y\\Z: X=主类型号 Y=子类型号 Z=设备号");
        myfile.WriteLine(";;序号 = UUID, 数据类别（0开关1模拟2曲线4枚举）, 数据类型号, 接口号, 码位, 采集项使用模式, 接口标识号, 逻辑子号");

        //*/////////////////////////////////////////////////////////////
        // [汇总信息]
        myfile.WriteSec("汇总信息");
        myfile.Write("主类型总数", QString::number(m_dev.size()));

        QMap<int, QMap<int, QVector<CsmDataDev*>>>::iterator it = m_dev.begin();
        int main_type_count = 1;
        while (it != m_dev.end())
        {
            QString key = QString("%1").arg(main_type_count, -2);
            QString val = QString("%1,%2").arg(it.key(), 4).arg(it.value().size(), 6);
            myfile.Write(key, val);

            main_type_count++;
            it++;
        }
        myfile.WriteLine();
        myfile.WriteLine();
        myfile.WriteLine();

        //*/////////////////////////////////////////////////////////////
        // [汇总信息\X]
        it = m_dev.begin();
        while(it != m_dev.end())
        {
            QString sec = "汇总信息\\" + QString::number(it.key());
            myfile.WriteSec(sec);

            int sub_cnt = 1;
            QMap<int, QVector<CsmDataDev*>>& plugin_analog = it.value();
            QMap<int, QVector<CsmDataDev*>>::iterator it2 = plugin_analog.begin();
            while(it2 != plugin_analog.end())
            {
                int single_dev_cj_cnt = 0;
                QVector<CsmDataDev*>& v_dev_data = it2.value();
                for(int i=0; i<v_dev_data.size(); i++) {
                    single_dev_cj_cnt = std::max(single_dev_cj_cnt, v_dev_data[i]->CjCount());
                }
                QString key = QString("%1").arg(sub_cnt, -2);
                QString val = QString("%1,%2,%3").arg(it2.key(), 4).arg(it2.value().size(), 6).arg(single_dev_cj_cnt, 6);
                 myfile.Write(key, val);

                it2++;
                sub_cnt++;
            }
            it++;

            myfile.WriteLine();
            myfile.WriteLine();
            myfile.WriteLine();
        }

        //*/////////////////////////////////////////////////////////////
        // [设备基础信息\X\Y\Z]、 [设备采集信息\X\Y\Z]
        it = m_dev.begin();
        while(it != m_dev.end())
        {
            QMap<int, QVector<CsmDataDev*>>& plugin_analog = it.value();
            QMap<int, QVector<CsmDataDev*>>::iterator it2 = plugin_analog.begin();
            it2 = plugin_analog.begin();
            while (it2 != plugin_analog.end())
            {
                QVector<CsmDataDev*>& v_dev_data = it2.value();
                for(int i=0; i<v_dev_data.size(); i++)
                {
                    QString sec = QString("设备基础信息\\%1\\%2\\%3").arg(it.key()).arg(it2.key()).arg(i+1);
                    myfile.WriteSec(sec);
                    myfile.Write("设备ID",         v_dev_data[i]->_uuid);
                    myfile.Write("设备名",         v_dev_data[i]->_name);
                    myfile.Write("TLE设备名",      v_dev_data[i]->_tle_name);
                    myfile.Write("设备类型码",      QString::number(v_dev_data[i]->_dev_full_type));
                    myfile.Write("逻辑分类类型1",   v_dev_data[i]->_logic_type);
                    myfile.Write("逻辑分组号",      v_dev_data[i]->_logic_group);
                    myfile.Write("虚拟状态量码位",   v_dev_data[i]->_vs_order);
                    myfile.Write("通信接口码位",     v_dev_data[i]->_comm_order);
                    myfile.Write("通信逻辑关联码位", v_dev_data[i]->_comm_rel);

                    WriteDevCJInfo(myfile, it.key(), it2.key(), i+1, v_dev_data[i]);

                    myfile.WriteLine();
                    myfile.WriteLine();
                    myfile.WriteLine();
                }
                it2++;
            }
            it++;
        }
        myfile.Close();
    }
}

void CsmDevice::WriteDevCJInfo(MyIniFile &file, int main_dev_type, int sub_dev_type, int dev_order, CsmDataDev *pdata)
{
    QString sec = QString("设备采集信息\\%1\\%2\\%3").arg(main_dev_type).arg(sub_dev_type).arg(dev_order);
    file.WriteSec(sec);

    int cj_cnt = 0;
    QVector<CsmDataDigit*>& v_digit = pdata->_cj_info._v_digit;
    for(int i=0; i<v_digit.size(); i++)
    {
        cj_cnt++;
        WriteDevCJInfo2(file, cj_cnt, v_digit[i]->_UUID, CsmData_Digit, v_digit[i]->_TypeID, v_digit[i]->_PluginID, v_digit[i]->_OrderNo);
    }

    QVector<CsmDataEnum*>& v_enum = pdata->_cj_info._v_enum;
    for(int i=0; i<v_enum.size(); i++)
    {
        cj_cnt++;
        WriteDevCJInfo2(file, cj_cnt, v_enum[i]->_UUID, CsmData_Enum, v_enum[i]->_TypeID, v_enum[i]->_PluginID, v_enum[i]->_OrderNo);
    }

    QVector<CsmDataAnalog*>& v_analog = pdata->_cj_info._v_analog;
    for(int i=0; i<v_analog.size(); i++)
    {
        cj_cnt++;
        WriteDevCJInfo2(file, cj_cnt, v_analog[i]->_UUID, CsmData_Analog, v_analog[i]->_TypeID, v_analog[i]->_PluginID, v_analog[i]->_OrderNo);
    }

    QVector<CsmDataCurve*>& v_curve = pdata->_cj_info._v_curve;
    for(int i=0; i<v_curve.size(); i++)
    {
        cj_cnt++;
        WriteDevCJInfo2(file, cj_cnt, v_curve[i]->_UUID, CsmData_Curve, v_curve[i]->_TypeID, v_curve[i]->_PluginID, v_curve[i]->_OrderNo);
    }
}

void CsmDevice::WriteDevCJInfo2(MyIniFile &file, int cj_cnt, const QString& uuid, CsmDataType data_type, int data_subType, int plugin_id, int data_order)
{
    QString key = QString("%1").arg(cj_cnt, -3);
    QString value;
    value += QString("%1,").arg(uuid, 20);
    value += QString("%1,").arg(data_type, 2);
    value += QString("%1,").arg(data_subType, 3);
    value += QString("%1,").arg(plugin_id, 10);
    value += QString("%1,").arg(data_order, 6);
    value += QString("%1,").arg(1, 2);
    value += QString("%1,").arg(Singleton<CsmDataManager>::Instance().GetPlugin()->GetPluginType(plugin_id), 3);
    value += QString("%1").arg(0, 2);
    file.Write(key, value);
}
