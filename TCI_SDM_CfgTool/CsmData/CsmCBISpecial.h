#ifndef CSMCBISPECIAL_H
#define CSMCBISPECIAL_H
#include <QString>

class ECID;
class MyIniFile;

class CsmCBISpecial
{
public:
    CsmCBISpecial();

public:
    void WriteToFile(const QString& outputPath);

protected:
    void WriteIps(MyIniFile &myfile);
    void WriteEcid(MyIniFile* myfile);
    void WriteBoard(MyIniFile* myfile, const ECID* pEcid);
};

#endif // CSMCBISPECIAL_H
