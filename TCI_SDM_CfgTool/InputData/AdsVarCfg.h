#ifndef ADSVARCFG_H
#define ADSVARCFG_H

#include <QMap>
#include <QString>
#include <QVector>

struct SingleStationAdsVar
{
    int station_no;
    int start_order;
    QMap<int, QString> m_mpIndiCode;
    QMap<int, QString> m_mpCtrlCode;
};


class AdsVarCfg
{
public:
    AdsVarCfg();
    ~AdsVarCfg();

public:
    bool LoadAdsVarCfg(const QString& inputFilePath);
    bool LoadSingleStationAdsVarCfg(const QString& inputFilePath, const QString &station_no);

    const QVector<SingleStationAdsVar> &GetVarInfo() const;

    void GetAllStationNo(QVector<int>& v_sta_no) const;

private:
    // 数据修饰
    void DataModify();

    // 补全空缺
    void CompleteVacancy(QMap<int, QString>& mpCode);
private:
    QVector<SingleStationAdsVar> m_lstAdsVar;
};

#endif // ADSVARCFG_H
