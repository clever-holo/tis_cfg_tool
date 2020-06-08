#ifndef CSMDEVICE_H
#define CSMDEVICE_H

#include <QString>
#include <QVector>
#include <QMap>
#include "CsmDataDefine.h"

class CsmDataDev;
class MyIniFile;

struct Dev_CJ
{
    QVector<CsmDataDigit*>  _v_digit;
    QVector<CsmDataEnum*>   _v_enum;
    QVector<CsmDataAnalog*> _v_analog;
    QVector<CsmDataCurve*>  _v_curve;
};

struct CsmDataDev
{
    QString         _uuid;
    QString         _name;
    QString         _tle_name;
    int             _dev_full_type;
    QString         _logic_type;
    QString         _logic_group;
    QString         _vs_order;
    QString         _comm_order;
    QString         _comm_rel;

    Dev_CJ          _cj_info;

    void AddCJInfo(CsmDataDigit*  pdata) { _cj_info._v_digit.push_back(pdata);}
    void AddCJInfo(CsmDataEnum*   pdata) { _cj_info._v_enum.push_back(pdata);}
    void AddCJInfo(CsmDataAnalog* pdata) { _cj_info._v_analog.push_back(pdata);}
    void AddCJInfo(CsmDataCurve*  pdata) { _cj_info._v_curve.push_back(pdata);}
    int  CjCount(){return _cj_info._v_digit.size() + _cj_info._v_enum.size() + _cj_info._v_analog.size() + _cj_info._v_curve.size();}
};

class CsmDevice
{
public:
    CsmDevice();

public:
    CsmDataDev* CreateDev(int dev_full_type, const QString& name, const QString& vs_order, const QString& comm_order);
    void WriteToFile(const QString& outputPath);

protected:
    void WriteDevCJInfo(MyIniFile& file, int main_dev_type, int sub_dev_type, int dev_order,  CsmDataDev* pdata);
    void WriteDevCJInfo2(MyIniFile &file, int cj_cnt, const QString& uuid, CsmDataType data_type, int data_subType, int plugin_id, int data_order);
private:
    QMap<int, QMap<int, QVector<CsmDataDev*>>>    m_dev;
};

#endif // CSMDEVICE_H
