#ifndef CFGGENERATOR_H
#define CFGGENERATOR_H

#include <qstring.h>

///
/// \brief 配置生成器：控制配置生成的主流程
///
class CfgGenerator
{
private:
    CfgGenerator();
    static CfgGenerator* m_instance;

public:
    static CfgGenerator* ins();

public:
    void GenerateCfg();

    QString inputPath() const;
    void setInputPath(const QString &inputPath);

    QString outputPath() const;
    void setOutputPath(const QString &outputPath);

    QString dbm() const;
    void setDbm(const QString &dbm);

    QString station_name() const;
    void setStation_name(const QString &station_name);

    QString station_no() const;
    void setStation_no(const QString &station_no);

private:
    QString m_inputPath;
    QString m_outputPath;
    QString m_dbm;
    QString m_station_name;
    QString m_station_no;
};

#endif // CFGGENERATOR_H
