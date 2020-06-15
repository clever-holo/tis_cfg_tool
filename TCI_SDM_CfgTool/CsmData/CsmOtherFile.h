#ifndef CSMOTHERFILE_H
#define CSMOTHERFILE_H

#include <QString>

class CsmOtherFile
{
public:
    CsmOtherFile();

    void WriteToFile(const QString& outputPath);

protected:
    void WriteStationInfo(const QString& outputPath);
    void WriteStationRun(const QString &outputPath);
    void WriteStationRunHmi(const QString &outputPath);
    void WriteStationRunSpecial(const QString &outputPath);
    void WriteStationSaveParam(const QString &outputPath);
};

#endif // CSMOTHERFILE_H
