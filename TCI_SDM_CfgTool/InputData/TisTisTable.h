#ifndef TISTISTABLE_H
#define TISTISTABLE_H

#include <QString>
#include <QVector>

struct TCC_Border_Unit
{
    QString  _name;
    QString  _addr;
    int      _order;
};


class TisTisTable
{
public:
    TisTisTable();

public:
    void LoadCfg(const QString &inputFilePath);

    QVector<TCC_Border_Unit> v_Tcc_border_info() const;

private:
    QVector<TCC_Border_Unit>   m_v_Tcc_border_info;
};

#endif // TISTISTABLE_H
