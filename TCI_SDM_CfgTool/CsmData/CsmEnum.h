#ifndef CSMENUM_H
#define CSMENUM_H

#include <QMap>
#include <QString>
#include <QVector>
#include "CsmDataDefine.h"

class CsmEnum
{
public:
    CsmEnum();
    ~CsmEnum();

public:
    CsmDataEnum *CreateEnum(int plugin_id, const QString& name, int enum_type, int is_valid, int cj_freq);
    void WriteToFile(const QString &outputPath);


private:
    QMap<int, QVector<CsmDataEnum*>> m_plugin_enum;
};

#endif // CSMENUM_H
