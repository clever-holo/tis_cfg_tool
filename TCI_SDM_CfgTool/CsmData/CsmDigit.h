#ifndef CSMDIGIT_H
#define CSMDIGIT_H

#include <QMap>
#include <QString>
#include <QVector>
#include "CsmDataDefine.h"

class CsmDigit
{
public:
    CsmDigit();
    ~CsmDigit();

public:
    CsmDataDigit* CreateDigit(int plugin_id, const QString& name, int digit_type, int is_reverse, int is_valid, int show_mode, int cj_freq, int stat_meth);
    void WriteToFile(const QString& outputPath);

private:
    QMap<int, QVector<CsmDataDigit*>> m_plugin_digit;
};

#endif // CSMDIGIT_H
