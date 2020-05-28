#include "AdsVarCfg.h"
#include "TisCfgData.h"
#include "InputFileCfg.h"
#include <QStringList>
#include <QFile>
#include <QTextStream>
#include <QRegExp>
#include <QtAlgorithms>

bool comp_adsvar(SingleStationAdsVar p1, SingleStationAdsVar p2)
{
    return p1.station_no < p2.station_no;
}


AdsVarCfg::AdsVarCfg()
{

}

AdsVarCfg::~AdsVarCfg()
{

}

bool AdsVarCfg::LoadAdsVarCfg(const QString &inputFilePath)
{
    QStringList StationNoLst;
    TisCfgData::Ins()->GetInputFileCfg()->GetAdsVarStationLst(StationNoLst);
    int nCount = StationNoLst.size();
    for(int i = 0; i < nCount; i++)
    {
        // 0站没有表示控制码位
        if(StationNoLst.at(i) == "0")
            continue;

        QString file_path = inputFilePath + "\\" + StationNoLst[i] + ".ADSVAR";
        LoadSingleStationAdsVarCfg(file_path, StationNoLst[i]);
    }
    DataModify();

    return true;
}

bool AdsVarCfg::LoadSingleStationAdsVarCfg(const QString &inputFilePath, const QString& station_no)
{
    QFile file(inputFilePath);
    if(file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream in_stream(&file);

        SingleStationAdsVar new_station;
        new_station.station_no = station_no.toInt();

        while(!in_stream.atEnd())
        {
            QString line = in_stream.readLine();
            line = line.replace(QRegExp("[\\r\\n]"), "");
            QStringList sl = line.split(QRegExp("[\\s]+"));
            int count = sl.size();
            if(count != 11)
                continue;

            if(sl[9] == "1")
                new_station.m_mpIndiCode[sl[10].toInt()] = sl[1];
            else if(sl[9] == "2") {
                new_station.m_mpCtrlCode[sl[10].toInt()] = sl[1];
            }
        }
        m_lstAdsVar.push_back(new_station);
    }
    return true;
}

const QVector<SingleStationAdsVar> &AdsVarCfg::GetVarInfo() const
{
    return m_lstAdsVar;
}

void AdsVarCfg::DataModify()
{
    // 按站号从小到大排序
    std::sort(m_lstAdsVar.begin(), m_lstAdsVar.end(), comp_adsvar);

    for(int i=0; i<m_lstAdsVar.size(); i++)
    {
        CompleteVacancy(m_lstAdsVar[i].m_mpIndiCode);
        CompleteVacancy(m_lstAdsVar[i].m_mpCtrlCode);
    }

    // 计算每个站的起始路数
    int start_order = 0;
    for(int i=0; i<m_lstAdsVar.size(); i++)
    {
        m_lstAdsVar[i].start_order = start_order;
        start_order += m_lstAdsVar[i].m_mpCtrlCode.size() + m_lstAdsVar[i].m_mpIndiCode.size();
    }
}

void AdsVarCfg::CompleteVacancy(QMap<int, QString> &mpCode)
{
    int code_count = mpCode.lastKey();
    for(int i=0; i<code_count; i++)
    {
        if(!mpCode.contains(i+1))
        {
            mpCode[i+1] = "ParamZero" + QString("%1").arg(i+1, 0, 10);
        }
    }
}























