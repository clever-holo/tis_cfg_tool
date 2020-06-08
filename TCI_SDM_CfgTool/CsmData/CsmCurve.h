#ifndef CSMCURVE_H
#define CSMCURVE_H

#include <QMap>
#include <QString>
#include <QVector>
#include "CsmDataDefine.h"

class CsmCurve
{
public:
    CsmCurve();

public:
    CsmDataCurve *CreateCurve(int analog_type , int plugin_id, const QString& name, int ratio, const QString& unit, int cj_freq, int is_valid);

    void WriteToFile(const QString& outputPath);


private:
    QMap<int, QMap<int, QVector<CsmDataCurve*>>> m_curve;
};

#endif // CSMCURVE_H
