#include "CsmOtherFile.h"
#include "MyIniFile.h"
#include "CommonMethod.h"
#include "TisCfgGenerator.h"

CsmOtherFile::CsmOtherFile()
{

}

void CsmOtherFile::WriteToFile(const QString &outputPath)
{
    WriteStationInfo(outputPath);
    WriteStationRun(outputPath);
    WriteStationRunHmi(outputPath);
    WriteStationRunSpecial(outputPath);
    WriteStationSaveParam(outputPath);
}

void CsmOtherFile::WriteStationInfo(const QString &outputPath)
{
    QString sta_name = CfgGenerator::ins()->station_name();
    QString file = outputPath + "\\" + sta_name + "\\Project\\StationInfo.ini";
    MyIniFile myfile(file);
    if(myfile.Open(QIODevice::WriteOnly | QIODevice::Truncate))
    {
        QString sta_name = CfgGenerator::ins()->station_name();
        QString sta_no   = CfgGenerator::ins()->station_no();
        QString DBM = CfgGenerator::ins()->dbm();

        myfile.WriteSec("本站");
        myfile.Write("本站汉字名", sta_name);
        myfile.Write("本站电报码", DBM);
        myfile.Write("本站地址码", sta_no);
        myfile.Write("车站类型", "集中站");
        myfile.WriteLine();
        myfile.WriteLine();

        myfile.WriteSec("数据版本");
        myfile.Write("版本号", "1");

        myfile.Close();
    }
}

void CsmOtherFile::WriteStationRun(const QString &outputPath)
{
    QString sta_name = CfgGenerator::ins()->station_name();
    QString file = outputPath + "\\" + sta_name + "\\Project\\StationRun.ini";
    MyIniFile myfile(file);
    if(myfile.Open(QIODevice::WriteOnly | QIODevice::Truncate))
    {
        myfile.WriteSec("StationRun");
        myfile.Write("RunMode", "TCI_SDM");
        myfile.Write("StationMainIP", "127.0.0.1");
        myfile.Close();
    }
}

void CsmOtherFile::WriteStationRunHmi(const QString &outputPath)
{
    QString sta_name = CfgGenerator::ins()->station_name();
    QString file = outputPath + "\\" + sta_name + "\\Project\\StationRunHmi.ini";
    MyIniFile myfile(file);
    if(myfile.Open(QIODevice::WriteOnly | QIODevice::Truncate))
    {
        myfile.WriteSec("HmiGroup_0");
        myfile.Write("1", "CSMHmi");
        myfile.Close();
    }
}

void CsmOtherFile::WriteStationRunSpecial(const QString &outputPath)
{
    QString sta_name = CfgGenerator::ins()->station_name();
    QString file = outputPath + "\\" + sta_name + "\\Project\\StationRunSpecial.ini";
    MyIniFile myfile(file);
    if(myfile.Open(QIODevice::WriteOnly | QIODevice::Truncate))
    {
        myfile.WriteSec("SpecialGroup_0");
        myfile.Write("1", "CSMSpecialProc_TCI_200_SDM");
        myfile.Close();
    }
}

void CsmOtherFile::WriteStationSaveParam(const QString &outputPath)
{
    QString sta_name = CfgGenerator::ins()->station_name();
    QString file = outputPath + "\\" + sta_name + "\\Project\\ParamCfg\\StationSaveParam.ini";
    MyIniFile myfile(file);
    if(myfile.Open(QIODevice::WriteOnly | QIODevice::Truncate))
    {
        myfile.WriteLine("####################################################################################################");
        myfile.WriteLine("#配置站机软件存储参数，包括存储路径和保留历史数据时间长度等");
        myfile.WriteLine("#");
        myfile.WriteLine("# 可设置共通参数");
        myfile.WriteLine("#     [Common_Setting]------------------------可设置SavePath(存储路径)");
        myfile.WriteLine("#");
        myfile.WriteLine("# 按存储类型设置参数,如：");
        myfile.WriteLine("#     [Digit_Setting]-------------------------可设置SavePath(存储路径)/TimeMode_SaveTime_Day(存储天数)");
        myfile.WriteLine("# 未设置时使用默认值");
        myfile.WriteLine("####################################################################################################");
        myfile.WriteLine();
        myfile.WriteLine("####################################################################################################");
        myfile.WriteLine("# 例:设定共通存储路径");
        myfile.WriteLine("#[Common_Setting]");
        myfile.WriteLine("#SavePath = D:\\CSMData");
        myfile.WriteLine("####################################################################################################");
        myfile.WriteLine();
        myfile.WriteLine("####################################################################################################");
        myfile.WriteLine("# 例:设定开关量存储路径和存储时间");
        myfile.WriteLine("#[Digit_Setting]");
        myfile.WriteLine("#SavePath       = E:\\TData");
        myfile.WriteLine("#TimeMode_SaveTime_Month = 3");
        myfile.WriteLine();
        myfile.WriteLine("####################################################################################################");

        myfile.WriteSec("Digit_Setting");
        myfile.Write("TimeMode_SaveTime_Day", "365");
        myfile.WriteLine();

        myfile.WriteSec("Enum_Setting");
        myfile.Write("TimeMode_SaveTime_Day", "365");
        myfile.WriteLine();

        myfile.WriteSec("VirtualStatus_Setting");
        myfile.Write("TimeMode_SaveTime_Day", "365");
        myfile.WriteLine();

        myfile.WriteSec("DcCurve_Setting");
        myfile.Write("TimeMode_SaveTime_Day", "365");
        myfile.WriteLine();

        myfile.WriteSec("Alarm_Setting");
        myfile.Write("TimeMode_SaveTime_Day", "365");
        myfile.WriteLine();

        myfile.WriteSec("NormalEventData_Setting");
        myfile.Write("TimeMode_SaveTime_Day", "365");
        myfile.WriteLine();

        myfile.Close();
    }
}
