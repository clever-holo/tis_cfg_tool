#ifndef CSMUSERMODI_H
#define CSMUSERMODI_H
#include <QString>

class CsmUserModi
{
public:
    CsmUserModi();

public:
    void WriteToFile(const QString& outputPath);

protected:
    void WriteAnalogModi(const QString& outputPath);
    void WriteCurveModi(const QString& outputPath);

    void GetAnalogLimit(int data_type, int& min_limit, int& max_limit, int& coef, int& std_val, int& min_alarm, int& max_alarm, int& alarm_param);
    void GetCurveLimit(int data_type, int& min_limit, int& max_limit, int& coef);
};

#endif // CSMUSERMODI_H
