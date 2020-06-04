#include "CsmEnum.h"
#include <QChar>
#include "MyIniFile.h"
#include "CommonMethod.h"

CsmEnum::CsmEnum()
{

}

CsmEnum::~CsmEnum()
{

}

CsmDataEnum CsmEnum::CreateEnum(int plugin_id, const QString &name, int enum_type, int is_valid, int cj_freq)
{
    QVector<CsmDataEnum>& v_enum = m_plugin_enum[plugin_id];

    CsmDataEnum enum_unit;
    enum_unit._UUID        = QString("%1%2%3").arg(plugin_id, 8, 10, QChar('0')).arg(CsmData_Enum, 2, 10, QChar('0')).arg(v_enum.size(), 7, 10, QChar('0'));
    enum_unit._PluginID    = plugin_id;
    enum_unit._Name        = name;
    enum_unit._OrderNo     = v_enum.size();
    enum_unit._TypeID      = enum_type;
    enum_unit._CJFreq      = cj_freq;
    enum_unit._IsValid     = is_valid;
    v_enum.push_back(enum_unit);

    return enum_unit;
}


void CsmEnum::WriteToFile(const QString &outputPath)
{
    QString DBM = "ABC";
    //QString file = outputPath + "\\Project\\DataCfg\\" + DBM + "\\DIGIT.INI";
    QString file = outputPath + "\\ENUM.INI";
    MyIniFile myfile(file);
    if(myfile.Open(QIODevice::WriteOnly | QIODevice::Truncate))
    {
        // 汇总信息
        myfile.WriteSec("汇总信息");
        QMap<int, QVector<CsmDataEnum>>::iterator it = m_plugin_enum.begin();
        int plugin_count = 1;
        while (it != m_plugin_enum.end())
        {
            QString key = QString::number(plugin_count);
            QString val = QString::number(it.key()) + "," +  QString::number(it.value().size());
            myfile.Write(key, val);

            it++;
            plugin_count++;
        }

        //
        it = m_plugin_enum.begin();
        while (it != m_plugin_enum.end())
        {
            QString sec = QString("枚举量\\%1").arg(it.key());
            myfile.WriteSec(sec);

            QVector<CsmDataEnum>& v_enum = it.value();
            for(int i=0; i<v_enum.size(); i++)
            {
                QString key = QString("%1").arg(i+1, -4, 10);
                QString val;
                val += QString("%1,").arg(v_enum[i]._UUID,   30);
                val += QString("%1,").arg(v_enum[i]._Name,   30 - CommonMethod::ChineseNumber(v_enum[i]._Name));
                val += QString("%1,").arg(v_enum[i]._OrderNo, 6);
                val += QString("%1,").arg(v_enum[i]._TypeID,  3);
                val += QString("%1,").arg(v_enum[i]._IsValid, 3);
                val += QString("%1,").arg(v_enum[i]._CJFreq,  3);

                myfile.Write(key, val);
            }
            it++;
        }
        myfile.Close();
    }
}
