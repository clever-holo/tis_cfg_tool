#include "CsmUserModi.h"
#include "MyIniFile.h"
#include "CommonMethod.h"
#include "CsmDataDefine.h"
#include "CsmDataManager.h"
#include "CsmCurve.h"
#include "CsmAnalog.h"
#include "TisCfgGenerator.h"

struct AnalogLimit
{
    int     _analog_type;
    int     _min_limit;
    int     _max_limit;
    int     _coef;
    int     _std_val;
    int     _min_alarm;
    int     _max_alarm;
    int     _alarm_param;
};

struct CurveLimit
{
    int     _curve_type;
    int     _min_limit;
    int     _max_limit;
    int     _coef;
};

const AnalogLimit   c_analog_limits[] =
{
    {E_SDDM_ANALOG_DSDL,               0,  200,   1, 120,  50, 170, 55 },
    {E_PDDM4_ANALOG_BSDYDY,            0,  150,   1, 110,  50, 170, 55 },
    {E_PDDM4_ANALOG_BSDL,              0,   20,   1,  15,  10,  17, 55 },
    {E_TCIM_ANALOG_JBXHDY,             0,  100,   1,  15,  10,  17, 55 },
    {E_TCIM_ANALOG_GDDY,               0,  100,   1,  15,  10,  17, 55 },
    {E_TCIM_ANALOG_GDXWJ,              0,  100,   1,  15,  10,  17, 55 },
    {E_PDDM5_ANALOG_SBO_VOLT_C,        0,  300,   1, 220, 100, 170, 55 },
    {E_PDDM5_ANALOG_SBO_VOLT_B,        0,  300,   1, 220, 100, 170, 55 },
    {E_PDDM5_ANALOG_SBO_VOLT_A,        0,  300,   1, 220, 100, 170, 55 },
    {E_PDDM5_ANALOG_EXP_VOLT,          0,  150,   1, 110, 100, 130, 55 },
    {E_PDDM5_ANALOG_SBO_FN_DL,         0,   20,   1,  15,  10,  17, 55 },
    {E_PDDM5_ANALOG_SBO_FW_DL,         0,   20,   1,  15,  10,  17, 55 },
    {E_PDDM5_ANALOG_SBO_DN_DL,         0,   20,   1,  15,  10,  17, 55 },
    {E_PDDM5_ANALOG_SBO_DW_DL,         0,   20,   1,  15,  10,  17, 55 },
    {E_SIOM_ANALOG_DI_SBO_VOLT,     -100,  100,   1,  48,  30,  60, 55 },
    {E_SIOM_ANALOG_SELF_CHECK_VOLT, -100,  100,   1,  48,  30,  60, 55 },
    {E_HIOM_ANALOG_DB_PORT_VOLT,       0,  200,   1, 120,  50, 170, 55 },
    {E_HIOM_ANALOG_FB_PORT_VOLT,       0,  200,   1, 120,  50, 170, 55 },
    {E_HIOM_ANALOG_SYB_PORT_VOLT,      0,  200,   1, 120,  50, 170, 55 },
};

const CurveLimit   c_curve_limits[] =
{
    {E_PDDM4_CURVE_DIRECT_CURR,  0,   20,   1},
    {E_PDDM5_CURVE_CURR_A,       0,   10,   1},
    {E_PDDM5_CURVE_CURR_B,       0,   10,   1},
    {E_PDDM5_CURVE_CURR_C,       0,   10,   1},
    {E_PDDM5_CURVE_PHASE_A,      0,  360,   1},
    {E_PDDM5_CURVE_PHASE_B,      0,  360,   1},
    {E_PDDM5_CURVE_PHASE_C,      0,  360,   1},
};


CsmUserModi::CsmUserModi()
{

}

void CsmUserModi::WriteToFile(const QString &outputPath)
{
    WriteAnalogModi(outputPath);
    WriteCurveModi(outputPath);
}

void CsmUserModi::WriteAnalogModi(const QString &outputPath)
{
    QString sta_name = CfgGenerator::ins()->station_name();
    QString DBM = CfgGenerator::ins()->dbm();
    QString file = outputPath + "\\" + sta_name + "\\user\\DataCfg\\" + DBM + "\\ANALOG_MODI.INI";

    MyIniFile myfile(file);
    if(myfile.Open(QIODevice::WriteOnly | QIODevice::Truncate))
    {
        // 注释
        myfile.WriteLine(";;模拟量\\X\\Y: X=模拟量类型码 Y=接口号 ");
        myfile.WriteLine(";;序号 = 码位, 量程下限, 量程上限, 系数, 标准值, 报警下限, 报警上限, 分级报警参数...");

        myfile.WriteSec("数据版本");
        myfile.Write("版本号", "1");
        myfile.WriteLine();
        myfile.WriteLine();

        //
        CsmAnalog* pAnalog = Singleton<CsmDataManager>::Instance().GetAnalog();
        const QMap<int, QMap<int, QVector<CsmDataAnalog *> > >& m_analog_all = pAnalog->GetAnalogData();

        QMap<int, QMap<int, QVector<CsmDataAnalog *> > >::const_iterator cit = m_analog_all.constBegin();
        while(cit != m_analog_all.constEnd())
        {
            QMap<int, QVector<CsmDataAnalog *> >::const_iterator cit2 = cit.value().constBegin();
            while(cit2 != cit.value().constEnd())
            {
                QString sec = QString("模拟量\\%1\\%2").arg(cit.key()).arg(cit2.key());
                myfile.WriteSec(sec);

                int count = 1;
                QVector<CsmDataAnalog *>::const_iterator cit3 = cit2.value().constBegin();
                while(cit3 != cit2.value().constEnd())
                {
                    int min_limit=0, max_limit=0, coef=1, std_val=0, min_alarm=0, max_alarm=0, alarm_param=0;
                    GetAnalogLimit((*cit3)->_TypeID, min_limit, max_limit, coef, std_val, min_alarm, max_alarm, alarm_param);

                    QString key = QString::number(count);
                    QString val;
                    val += QString("%1,%2,%3,%4,%5,").arg((*cit3)->_OrderNo, 3).arg(min_limit, 4).arg(max_limit,4).arg(coef,4).arg(std_val,4);
                    val += QString("%1,%2,%3, , , , , , ,").arg(min_alarm, 4).arg(max_alarm, 4).arg(alarm_param, 4);
                    myfile.Write(key, val);
                    count++;
                    cit3++;
                }
                myfile.WriteLine();
                myfile.WriteLine();
                myfile.WriteLine();
                cit2++;
            }
            cit++;
        }
        myfile.Close();
    }
}

void CsmUserModi::WriteCurveModi(const QString &outputPath)
{
    QString sta_name = CfgGenerator::ins()->station_name();
    QString DBM = CfgGenerator::ins()->dbm();
    QString file = outputPath + "\\" + sta_name + "\\user\\DataCfg\\" + DBM + "\\CURVE_MODI.INI";

    MyIniFile myfile(file);
    if(myfile.Open(QIODevice::WriteOnly | QIODevice::Truncate))
    {
        // 注释
        myfile.WriteLine(";;曲线\\X\\Y: X=曲线类型码 Y=接口号 序号 = 码位, 量程下限, 量程上限, 系数, 预留信息...");

        myfile.WriteSec("数据版本");
        myfile.Write("版本号", "1");
        myfile.WriteLine();
        myfile.WriteLine();

        //
        CsmCurve* pCurve = Singleton<CsmDataManager>::Instance().GetCurve();
        const QMap<int, QMap<int, QVector<CsmDataCurve *> > >& m_curve_all = pCurve->GetCurveData();

        QMap<int, QMap<int, QVector<CsmDataCurve *> > >::const_iterator cit = m_curve_all.constBegin();
        while(cit != m_curve_all.constEnd())
        {
            QMap<int, QVector<CsmDataCurve *> >::const_iterator cit2 = cit.value().constBegin();
            while(cit2 != cit.value().constEnd())
            {
                QString sec = QString("曲线\\%1\\%2").arg(cit.key()).arg(cit2.key());
                myfile.WriteSec(sec);

                int count = 1;
                QVector<CsmDataCurve *>::const_iterator cit3 = cit2.value().constBegin();
                while(cit3 != cit2.value().constEnd())
                {
                    int min_limit=0, max_limit=0, coef=1;
                    GetCurveLimit((*cit3)->_TypeID, min_limit, max_limit, coef);

                    QString key = QString::number(count);
                    QString val = QString("%1,%2,%3,%4, , , , , ,").arg((*cit3)->_UUID, 15).arg(min_limit, 4).arg(max_limit,4).arg(coef,4);

                    myfile.Write(key, val);
                    count++;
                    cit3++;
                }
                myfile.WriteLine();
                myfile.WriteLine();
                myfile.WriteLine();
                cit2++;
            }
            cit++;
        }
        myfile.Close();
    }
}

void CsmUserModi::GetAnalogLimit(int data_type, int &min_limit, int &max_limit, int &coef, int &std_val, int &min_alarm, int &max_alarm, int &alarm_param)
{
    int cnt = sizeof(c_analog_limits) / sizeof(AnalogLimit);

    for(int i=0; i<cnt; i++)
    {
        if(data_type == c_analog_limits[i]._analog_type)
        {
            min_limit   = c_analog_limits[i]._min_limit;
            max_limit   = c_analog_limits[i]._max_limit;
            coef        = c_analog_limits[i]._coef;
            std_val     = c_analog_limits[i]._std_val;
            min_alarm   = c_analog_limits[i]._min_alarm;
            max_alarm   = c_analog_limits[i]._max_alarm;
            alarm_param = c_analog_limits[i]._alarm_param;

            return;
        }
    }
}

void CsmUserModi::GetCurveLimit(int data_type, int &min_limit, int &max_limit, int &coef)
{
    int cnt = sizeof(c_curve_limits) / sizeof(CurveLimit);

    for(int i=0; i<cnt; i++)
    {
        if(data_type == c_curve_limits[i]._curve_type)
        {
            min_limit   = c_curve_limits[i]._min_limit;
            max_limit   = c_curve_limits[i]._max_limit;
            coef        = c_curve_limits[i]._coef;

            return;
        }
    }
}
