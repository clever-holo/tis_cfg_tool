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

private:
    QString m_inputPath;
    QString m_outputPath;
};

#endif // CFGGENERATOR_H
