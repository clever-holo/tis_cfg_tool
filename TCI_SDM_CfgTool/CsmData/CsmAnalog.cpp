#include "CsmAnalog.h"
#include <QChar>
#include "MyIniFile.h"
#include "CommonMethod.h"

#define DEF_ANALOG_DELAYQUEUELENGTH     (10)
#define DEF_ANALOG_FILTERTIMEPARAM      ("0#0#0#0")

CsmAnalog::CsmAnalog()
{

}

CsmDataAnalog *CsmAnalog::CreateAnalog(int analog_type, int plugin_id, const QString &name, int ratio, const QString &unit, int cj_freq, int is_valid)
{
   QMap<int, QVector<CsmDataAnalog*>>& mp_analog = m_analog[analog_type];
   QVector<CsmDataAnalog*>&  v_analog = mp_analog[plugin_id];

    CsmDataAnalog* analog_unit = new CsmDataAnalog();

    analog_unit->_TypeID      = analog_type;
    analog_unit->_PluginID    = plugin_id;
    analog_unit->_UUID        = QString("%1%2%3").arg(plugin_id, 8, 10, QChar('0')).arg(CsmData_Analog, 2, 10, QChar('0')).arg(v_analog.size()+1, 7, 10, QChar('0'));
    analog_unit->_Name        = name;
    analog_unit->_OrderNo     = v_analog.size();
    analog_unit->_Ratio       = ratio;
    analog_unit->_Unit        = unit;
    analog_unit->_CJFreq      = cj_freq;
    analog_unit->_DelayQueueLength = DEF_ANALOG_DELAYQUEUELENGTH;
    analog_unit->_FilterTimeParam  = DEF_ANALOG_FILTERTIMEPARAM;
    analog_unit->_IsValid     = is_valid;
    v_analog.push_back(analog_unit);

    return analog_unit;
}

void CsmAnalog::WriteToFile(const QString &outputPath)
{
    QString DBM = "ABC";
    //QString file = outputPath + "\\Project\\DataCfg\\" + DBM + "\\ANALOG.INI";
    QString file = outputPath + "\\ANALOG.INI";
    MyIniFile myfile(file);
    if(myfile.Open(QIODevice::WriteOnly | QIODevice::Truncate))
    {
        // 汇总信息
        myfile.WriteSec("汇总信息");
        QMap<int, QMap<int, QVector<CsmDataAnalog*>>>::iterator it = m_analog.begin();
        int ananlog_type_count = 1;
        while (it != m_analog.end())
        {
            QString key = QString::number(ananlog_type_count);

            int ananlog_cnt = 0;
            QMap<int, QVector<CsmDataAnalog*>>& plugin_analog = it.value();
            QMap<int, QVector<CsmDataAnalog*>>::iterator it2 = plugin_analog.begin();
            while(it2 != plugin_analog.end())
            {
                ananlog_cnt += it2.value().size();
                it2++;
            }

            QString val = QString::number(it.key()) + "," +  QString::number(it.value().size()) + "," +  QString::number(ananlog_cnt);
            myfile.Write(key, val);

            it++;
            ananlog_type_count++;
        }

        //*/////////////////////////////////////////////////////////////
        it = m_analog.begin();
        while(it != m_analog.end())
        {
            QString sec = "汇总信息\\" + QString::number(it.key());
            myfile.WriteSec(sec);

            int plugin_cnt = 1;
            QMap<int, QVector<CsmDataAnalog*>>& plugin_analog = it.value();
            QMap<int, QVector<CsmDataAnalog*>>::iterator it2 = plugin_analog.begin();
            while(it2 != plugin_analog.end())
            {
                QString key = QString::number(plugin_cnt);
                QString val = QString::number(it2.key()) + "," +  QString::number(it2.value().size());
                 myfile.Write(key, val);

                it2++;
                plugin_cnt++;
            }

            //*/////////////////////////////////////////////////////////////
            it2 = plugin_analog.begin();
            while (it2 != plugin_analog.end())
            {
                QString sec = QString("模拟量\\%1\\%2").arg(it.key()).arg(it2.key());
                myfile.WriteSec(sec);

                QVector<CsmDataAnalog*>& v_analog = it2.value();
                for(int i=0; i<v_analog.size(); i++)
                {
                    QString key = QString("%1").arg(i+1, -4, 10);
                    QString val;
                    val += QString("%1,").arg(v_analog[i]->_UUID, 30);
                    val += QString("%1,").arg(v_analog[i]->_Name, 30 - CommonMethod::ChineseNumber(v_analog[i]->_Name));
                    val += QString("%1,").arg(v_analog[i]->_OrderNo, 6);
                    val += QString("%1,").arg(v_analog[i]->_Ratio, 3);
                    val += QString("%1,").arg(v_analog[i]->_Unit, 3 - CommonMethod::ChineseNumber(v_analog[i]->_Unit));
                    val += QString("%1,").arg(v_analog[i]->_CJFreq, 3);
                    val += QString("%1,").arg(v_analog[i]->_DelayQueueLength, 3);
                    val += QString("%1,").arg(v_analog[i]->_FilterTimeParam, 8);
                    val += QString("%1").arg(v_analog[i]->_IsValid, 3);

                    myfile.Write(key, val);
                }
                it2++;
            }
            it++;
        }
        //
        myfile.Close();
    }
}
