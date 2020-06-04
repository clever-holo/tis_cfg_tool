#include "CsmDigit.h"
#include <QChar>
#include "MyIniFile.h"
#include "CommonMethod.h"

CsmDigit::CsmDigit()
{

}

CsmDigit::~CsmDigit()
{

}

CsmDataDigit CsmDigit::CreateDigit(int plugin_id, const QString &name, int digit_type, int is_reverse, int is_valid, int show_mode, int cj_freq, int stat_meth)
{
    QVector<CsmDataDigit>& v_digit = m_plugin_digit[plugin_id];

    CsmDataDigit digit_unit;
    digit_unit._UUID        = QString("%1%2%3").arg(plugin_id, 8, 10, QChar('0')).arg(CsmData_Digit, 2, 10, QChar('0')).arg(v_digit.size()+1, 7, 10, QChar('0'));
    digit_unit._PluginID    = plugin_id;
    digit_unit._Name        = name;
    digit_unit._OrderNo     = v_digit.size();
    digit_unit._TypeID      = digit_type;
    digit_unit._IsReverse   = is_reverse;
    digit_unit._IsValid     = is_valid;
    digit_unit._ShowMode    = show_mode;
    digit_unit._CJFreq      = cj_freq;
    digit_unit._StatisicMeth= stat_meth;

    v_digit.push_back(digit_unit);

    return digit_unit;
}

void CsmDigit::WriteToFile(const QString &outputPath)
{
    QString DBM = "ABC";
    //QString file = outputPath + "\\Project\\DataCfg\\" + DBM + "\\DIGIT.INI";
    QString file = outputPath + "\\DIGIT.INI";
    MyIniFile myfile(file);
    if(myfile.Open(QIODevice::WriteOnly | QIODevice::Truncate))
    {
        // 汇总信息
        myfile.WriteSec("汇总信息");
        QMap<int, QVector<CsmDataDigit>>::iterator it = m_plugin_digit.begin();
        int plugin_count = 1;
        while (it != m_plugin_digit.end())
        {
            QString key = QString::number(plugin_count);
            QString val = QString::number(it.key()) + "," +  QString::number(it.value().size());
            myfile.Write(key, val);

            it++;
            plugin_count++;
        }

        //

        it = m_plugin_digit.begin();
        while (it != m_plugin_digit.end())
        {
            QString sec = QString("开关量\\%1").arg(it.key());
            myfile.WriteSec(sec);

            QVector<CsmDataDigit>& v_digit = it.value();
            for(int i=0; i<v_digit.size(); i++)
            {
                QString key = QString("%1").arg(i+1, -4, 10);
                QString val;
                val += QString("%1,").arg(v_digit[i]._UUID, 30);
                val += QString("%1,").arg(v_digit[i]._Name, 30 - CommonMethod::ChineseNumber(v_digit[i]._Name));
                val += QString("%1,").arg(v_digit[i]._OrderNo, 6);
                val += QString("%1,").arg(v_digit[i]._TypeID, 3);
                val += QString("%1,").arg(v_digit[i]._IsReverse, 3);
                val += QString("%1,").arg(v_digit[i]._IsValid, 3);
                val += QString("%1,").arg(v_digit[i]._ShowMode, 3);
                val += QString("%1,").arg(v_digit[i]._CJFreq, 3);
                val += QString("%1").arg(v_digit[i]._StatisicMeth, 3);

                myfile.Write(key, val);
            }
            it++;
        }
        myfile.Close();
    }
}
