#ifndef CSMIF_STATIONINFO_H
#define CSMIF_STATIONINFO_H

#include <QString>

class MyIniFile;
class CsmIF_StationInfo
{
public:
    CsmIF_StationInfo();


public:
    void OutPutFile(const QString &str_output_path);

protected:
    void OutPutVersion();
    void OutPutStaCode();
    void OutPutStaCode2(const QMap<int, QString>& mp_var);
    void OutPutIpsBoard();
    void CloseFile();

private:

    MyIniFile* myfile;
    int        m_counter;
};

#endif // CSMIF_STATIONINFO_H
