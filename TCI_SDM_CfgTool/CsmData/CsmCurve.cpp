#include "CsmCurve.h"
#include <QChar>
#include "MyIniFile.h"
#include "CommonMethod.h"
#include "TisCfgGenerator.h"

#define DEF_CURVE_ADDRESS  (1010)

CsmCurve::CsmCurve()
{

}

CsmDataCurve *CsmCurve::CreateCurve(int analog_type, int plugin_id, const QString &name, int ratio, const QString &unit, int cj_freq, int is_valid)
{
     QMap<int, QVector<CsmDataCurve*>>& mp_curve = m_curve[analog_type];
     QVector<CsmDataCurve*>&  v_curve = mp_curve[plugin_id];

     CsmDataCurve *curve_unit = new CsmDataCurve();

     curve_unit->_TypeID      = analog_type;
     curve_unit->_PluginID    = plugin_id;
     curve_unit->_UUID        = QString("%1%2%3%4").arg(plugin_id, 8, 10, QChar('0')).arg(CsmData_Curve, 2, 10, QChar('0')).arg(analog_type,3,10,QChar('0')).arg(v_curve.size()+1, 7, 10, QChar('0'));
     curve_unit->_Name        = name;
     curve_unit->_OrderNo     = v_curve.size();
     curve_unit->_Ratio       = ratio;
     curve_unit->_Unit        = unit;
     curve_unit->_CJFreq      = cj_freq;
     curve_unit->_Address     = DEF_CURVE_ADDRESS;
     curve_unit->_IsValid     = is_valid;
     v_curve.push_back(curve_unit);

     return curve_unit;
}

void CsmCurve::WriteToFile(const QString &outputPath)
{
    QString sta_name = CfgGenerator::ins()->station_name();
    QString DBM = CfgGenerator::ins()->dbm();
    QString file = outputPath + "\\" +  sta_name + "\\Project\\DataCfg\\" + DBM + "\\CURVE.INI";
    MyIniFile myfile(file);
    if(myfile.Open(QIODevice::WriteOnly | QIODevice::Truncate))
    {
        // 注释
        myfile.WriteLine(";;汇总信息: 序号 = 曲线类型码, 接口个数, 曲线总数");
        myfile.WriteLine(";;汇总信息\\X: X=曲线类型码 序号 = 接口号, 曲线个数");
        myfile.WriteLine(";;曲线\\X\\Y: X=曲线类型码 Y=接口号");
        myfile.WriteLine(";;序号 = UUID, 曲线名称, 码位, 倍率, 单位, 采集频率, 地址号, 是否有效");
        myfile.WriteLine();
        myfile.WriteLine();

        // 汇总信息
        myfile.WriteSec("汇总信息");
        QMap<int, QMap<int, QVector<CsmDataCurve*>>>::iterator it = m_curve.begin();
        int curve_type_count = 1;
        while (it != m_curve.end())
        {
            QString key = QString::number(curve_type_count);

            int curve_cnt = 0;
            QMap<int, QVector<CsmDataCurve*>>& plugin_curve = it.value();
            QMap<int, QVector<CsmDataCurve*>>::iterator it2 = plugin_curve.begin();
            while(it2 != plugin_curve.end())
            {
                curve_cnt += it2.value().size();
                it2++;
            }

            QString val = QString::number(it.key()) + "," +  QString::number(it.value().size()) + "," +  QString::number(curve_cnt);
            myfile.Write(key, val);

            it++;
            curve_type_count++;
        }

        //*/////////////////////////////////////////////////////////////
        it = m_curve.begin();
        while(it != m_curve.end())
        {
            QString sec = "汇总信息\\" + QString::number(it.key());
            myfile.WriteSec(sec);

            int plugin_cnt = 1;
            QMap<int, QVector<CsmDataCurve*>>& plugin_curve = it.value();
            QMap<int, QVector<CsmDataCurve*>>::iterator it2 = plugin_curve.begin();
            while(it2 != plugin_curve.end())
            {
                QString key = QString::number(plugin_cnt);
                QString val = QString::number(it2.key()) + "," +  QString::number(it2.value().size());
                 myfile.Write(key, val);

                it2++;
                plugin_cnt++;
            }

            //*/////////////////////////////////////////////////////////////
            it2 = plugin_curve.begin();
            while (it2 != plugin_curve.end())
            {
                QString sec = QString("曲线\\%1\\%2").arg(it.key()).arg(it2.key());
                myfile.WriteSec(sec);

                QVector<CsmDataCurve*>& v_curve = it2.value();
                for(int i=0; i<v_curve.size(); i++)
                {
                    QString key = QString("%1").arg(i+1, -4, 10);
                    QString val;
                    val += QString("%1,").arg(v_curve[i]->_UUID, 30);
                    val += QString("%1,").arg(v_curve[i]->_Name, 30 - CommonMethod::ChineseNumber(v_curve[i]->_Name));
                    val += QString("%1,").arg(v_curve[i]->_OrderNo, 6);
                    val += QString("%1,").arg(v_curve[i]->_Ratio, 3);
                    val += QString("%1,").arg(v_curve[i]->_Unit, 3 - CommonMethod::ChineseNumber(v_curve[i]->_Unit));
                    val += QString("%1,").arg(v_curve[i]->_CJFreq, 3);
                    val += QString("%1,").arg(v_curve[i]->_Address, 7);
                    val += QString("%1").arg(v_curve[i]->_IsValid, 3);

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

const QMap<int, QMap<int, QVector<CsmDataCurve *> > > CsmCurve::GetCurveData() const
{
    return m_curve;
}
