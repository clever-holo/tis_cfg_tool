#ifndef TISZPWTABLE_H
#define TISZPWTABLE_H

#include <QString>
#include <QVector>

/// 区间轨道电路信息表
struct ZPW_QJ_Unit
{
    QString     _val_1;
    QString     _val_2;
    QString     _val_3;
    QString     _val_4;
    QString     _val_5;
    QString     _val_6;
    QString     _val_7;
    QString     _val_8;
    QString     _val_9;
    QString     _val_10;
    QString     _val_11;
    QString     _val_12;
    QString     _val_13;
};

class TisZpwTable
{
public:
    TisZpwTable();

public:
    void LoadCfg(const QString &inputFilePath);

    QVector<ZPW_QJ_Unit> v_ZpwQjInfo() const;

private:
    QVector<ZPW_QJ_Unit>    m_v_ZpwQjInfo;
};

#endif // TISZPWTABLE_H
