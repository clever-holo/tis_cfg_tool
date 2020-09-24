#ifndef GROUNDEQUIPMENTTABLE_H
#define GROUNDEQUIPMENTTABLE_H

#include <QString>
#include <QMap>


class GroundEquipmentTable
{
public:
    GroundEquipmentTable();

public:
    void LoadCfg(const QString &inputFilePath);


    QMap<QString, QString> mp_sta_addr() const;

private:
    QMap<QString, QString>  m_mp_sta_addr;
};

#endif // GROUNDEQUIPMENTTABLE_H
