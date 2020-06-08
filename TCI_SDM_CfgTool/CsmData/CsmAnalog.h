#ifndef CSMANALOG_H
#define CSMANALOG_H

#include <QMap>
#include <QString>
#include <QVector>
#include "CsmDataDefine.h"

class CsmAnalog
{
public:
    CsmAnalog();

public:
    CsmDataAnalog *CreateAnalog(int analog_type , int plugin_id, const QString& name,
                                int ratio, const QString& unit, int cj_freq, int is_valid);

    void WriteToFile(const QString& outputPath);


private:
    QMap<int, QMap<int, QVector<CsmDataAnalog*>>> m_analog;

};

#endif // CSMANALOG_H
