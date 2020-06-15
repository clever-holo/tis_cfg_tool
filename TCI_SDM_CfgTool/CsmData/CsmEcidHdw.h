#ifndef CSMECIDHDW_H
#define CSMECIDHDW_H
#include <QString>

class ECID;
class CsmEcidHdw
{
public:
    CsmEcidHdw();

public:
    void WriteToFile(const QString& outputPath);

protected:
    void WriteSingleEcid(const ECID* pEcid, const QString& outputPath);
};

#endif // CSMECIDHDW_H
