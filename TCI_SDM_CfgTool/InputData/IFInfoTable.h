#ifndef IFINFOTABLE_H
#define IFINFOTABLE_H

#include <QString>
#include <QVector>

struct OneStationIF
{
    int                 _sta_no;         // 本站站号
    QVector<int>        _sub_sta_no;     // 被控站站号
    QVector<QString>    _FXK_names;      // 发车口名
};

class ExcelBook;
class IFInfoTable
{
public:
    IFInfoTable();

public:
    void LoadCfg(const QString &inputFilePath);

    QVector<QString> v_FCX_names() const;


protected:
    bool LoadOneTable(const QString& file_name, OneStationIF& one_sta);
    bool LoadBaseInfo(ExcelBook* book, OneStationIF& one_sta);
    bool LoadFckInfo(ExcelBook* book, OneStationIF& one_sta);

    void MergeFckName(QMap<int, OneStationIF>& mp_sta_info);

private:
    QVector<QString> m_v_FCX_names;
};

#endif // IFINFOTABLE_H
