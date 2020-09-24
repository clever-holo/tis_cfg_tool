#include "CsmOtherFile.h"
#include "MyIniFile.h"
#include "CommonMethod.h"
#include "TisCfgGenerator.h"
#include "TisCfgData.h"
#include <QVector>
#include <QMapIterator>
#include <QRegularExpression>
#include "BlockCfg.h"
#include "TisTisTable.h"
#include "TisZpwTable.h"
#include "IFInfoTable.h"

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
    WriteMeter(outputPath);
    WriteSdmGeneral(outputPath);
    WriteCsmInterface(outputPath);
    WriteINTERDATA(outputPath);
    WriteIgnoreAlarm(outputPath);
    WriteTleCfg(outputPath);
    WriteNetLinkDelayeCfg(outputPath);
    CopyFile(outputPath);
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

void CsmOtherFile::WriteMeter(const QString &outputPath)
{
    QString sta_name = CfgGenerator::ins()->station_name();
    QString file = outputPath + "\\" + sta_name + "\\Project\\SpecialCfg\\SDM\\ECMCONFIGFILE.ini";
    MyIniFile myfile(file);
    if(myfile.Open(QIODevice::WriteOnly | QIODevice::Truncate))
    {
        myfile.WriteLine(";定义与METER接口。如果没有接口,置Port=0.");
        myfile.WriteSec("COMPORT_ECM");
        myfile.Write("Port", "2");
        myfile.Write("BaudRate", "19200");
        myfile.Write("MODULE", "01");
        myfile.Write("ADDRESS", "0X0014");
        myfile.Write("DC-RATIO", "45");
        myfile.Write("AC-RATIO", "15");
        myfile.Write("LINES", "2");
        myfile.Write("LINE1", "45");
        myfile.Write("LINE2", "15");
        myfile.Write("STATION", "2");
        myfile.WriteLine(";是否记录LOG记录");
        myfile.Write("DEBUG", "0");
        myfile.WriteLine(";（1表示 1*100 ms ,目前默认值是3 即 3*100 ms）");
        myfile.Write("TIMER", "1");
        myfile.WriteLine();

        myfile.WriteLine(";定义与METER接口。如果没有接口,置Port=0.");
        myfile.WriteSec("COMPORT_2ECM");
        myfile.Write("Port", "4");
        myfile.Write("BaudRate", "19200");
        myfile.Write("MODULE", "01");
        myfile.Write("ADDRESS", "0X0014");
        myfile.Write("DC-RATIO", "45");
        myfile.Write("AC-RATIO", "15");
        myfile.Write("LINES", "2");
        myfile.Write("LINE1", "45");
        myfile.Write("LINE2", "15");
        myfile.Write("STATION", "2");
        myfile.WriteLine(";是否记录LOG记录");
        myfile.Write("DEBUG", "0");
        myfile.WriteLine(";（1表示 1*100 ms ,目前默认值是3 即 3*100 ms）");
        myfile.Write("TIMER", "1");
        myfile.WriteLine();

        myfile.Close();
    }
}

void CsmOtherFile::WriteSdmGeneral(const QString &outputPath)
{
    QString sta_name = CfgGenerator::ins()->station_name();
    QString file = outputPath + "\\" + sta_name + "\\Project\\SpecialCfg\\SDM\\SdmGeneral.ini";
    MyIniFile myfile(file);
    if(myfile.Open(QIODevice::WriteOnly | QIODevice::Truncate))
    {
        ///////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////
        myfile.WriteSec("RUN_FLAG");
        QString key = "SDMstationNo";
        QString val = CfgGenerator::ins()->station_no();
        myfile.Write(key, val);

        key = "SdmHdwNameLeftorRight";
        val = "0";
        myfile.WriteLine(";左边为0，右边为1");
        myfile.Write(key, val);

        key = "TimeSyncSource";
        val = "1";
        myfile.WriteLine(";时间同步数据来源(1-MMI, 2-TSRS),根据本站实际情况进行修改");
        myfile.Write(key, val);

        ///////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////
        myfile.WriteSec("VERSION");

        key = "ECMCONFIGFILE";
        val = "ECMCONFIGFILE.ini";
        myfile.Write(key, val);

        ///
        key = "VARFILE";
        val = "";
        QVector<QString> v_adss = CfgGenerator::ins()->Ads_files();
        foreach (QString ele, v_adss) {
            if(!val.isEmpty())
                val += "#";
            val += "SDM_DEPEND\\" + ele;
        }
        myfile.Write(key, val);

        ///
        key = "BOLFILE";
        val = "";
        QVector<QString> v_vtls =CfgGenerator::ins()->Vtl_files();
        foreach (QString ele, v_vtls) {
            if(!val.isEmpty())
                val += "#";
            val += "SDM_DEPEND\\" + ele;
        }
        myfile.Write(key, val);

        ///
        key = "DMISFILE";
        val = "SDM_DEPEND\\dmis_ctc." + CfgGenerator::ins()->station_no();
        myfile.Write(key, val);

        ///
        key = "RUDPCFGFILE";
        val = "SDM_DEPEND\\SDM_Config.ini";
        myfile.Write(key, val);

        ///
        key = "MRMSCFGFILE";
        val = "SDM_DEPEND\\CVC_MRMS.ini";
        myfile.Write(key, val);

        ///
        key = "NETCFGFILE";
        val = "SDM_DEPEND\\HostCfg.xml";
        myfile.Write(key, val);

        ///
        key = "HDWCFGMAP";
        val = "SDM_DEPEND\\SDMHdwToFrameView.xml";
        myfile.Write(key, val);

        ///
        key = "NVCCOMFILE";
        val = "SDM_DEPEND\\HostCfg.ini";
        myfile.Write(key, val);

        ///
        key = "NETLNKDELAY";
        val = "SDM_DEPEND\\NetLinkDelayTime.ini";
        myfile.Write(key, val);

        ///
        myfile.WriteLine(";监测接口配置");
        key = "CSMCONFIGFILE";
        val = "SDM_DEPEND\\CSMCONFIGFILE.ini";
        myfile.Write(key, val);

        myfile.WriteLine();

        ///////////////////////////////////////////////////////
        /// 驱采报警路径配置
        QVector<QString> v_qcalarm = CfgGenerator::ins()->qcalarm_files();
        foreach (QString ele, v_qcalarm)
        {
            int n_station_no = ele.left(ele.indexOf("_")).toInt();
            if(n_station_no == 0)
                continue;

            myfile.WriteSec(QString::number(n_station_no));

            key = "QCAlarmOccurDelayTime";
            val = "5";
            myfile.Write(key, val);

            key = "QCALARM_CFG_FILE";
            val = "SDM_DEPEND\\" + ele;
            myfile.Write(key, val);

            myfile.WriteLine();
        }

        ///////////////////////////////////////////////////////
        /// 日志开关
        myfile.WriteSec("LOG_CFG");
        myfile.WriteLine(";日志开关");
        myfile.WriteLine("CsmIFLog=FALSE");
        myfile.WriteLine();


        myfile.Close();
    }
}

void CsmOtherFile::WriteCsmInterface(const QString &outputPath)
{
    QString sta_name = CfgGenerator::ins()->station_name();
    QString file = outputPath + "\\" + sta_name + "\\Project\\SpecialCfg\\SDM\\SDM_DEPEND\\CSMCONFIGFILE.ini";
    MyIniFile myfile(file);
    if(myfile.Open(QIODevice::WriteOnly | QIODevice::Truncate))
    {
        myfile.WriteLine();
        myfile.WriteLine(";**************************************");
        myfile.WriteLine(";在SdmGeneral.ini中增加一行接口配置");
        myfile.WriteLine(";CSMCONFIGFILE=SDM_DEPEND\\CSMCONFIGFILE.ini");
        myfile.WriteLine(";**************************************");
        myfile.WriteLine();
        myfile.WriteLine();

        myfile.WriteLine(";************** SDM要打开的串口号  **************");
        myfile.WriteLine(";Ports=7,8,9");
        myfile.WriteLine();

        myfile.WriteLine(";************** 波特率  **************");
        myfile.WriteLine(";BaudRate=38400");
        myfile.WriteLine();

        myfile.WriteLine(";************** 版本号  **************");
        myfile.WriteLine(";Data_Ver=1.0.0.0");
        myfile.WriteLine();

        myfile.WriteLine(";************** 使用指定串口号发送指定类型的消息，格式(串口号, 十进制消息类型)  **************");
        myfile.WriteLine(";Filter=(7,33)(8,161)(8,162)(9,12)(9,51)(9,60)(9,54)");
        myfile.WriteLine();

        myfile.WriteLine(";************** 消息类型定义  **************");
        myfile.WriteLine(";0x21(33) ：站场码位信息");
        myfile.WriteLine(";0x0C(12) ：站间边界信息");
        myfile.WriteLine(";0x33(51) ：临时限速状态信息");
        myfile.WriteLine(";0x3C(60) ：轨道区段编码信息");
        myfile.WriteLine(";0x36(54) ：区间SA状态信息");
        myfile.WriteLine(";0x55(85) ：区间闭塞状态确认信息");
        myfile.WriteLine(";0xA1(161)：道岔动作数据");
        myfile.WriteLine(";0xA2(162)：实时数据");
        myfile.WriteLine();

        myfile.WriteLine();
        myfile.WriteLine(";**************************************");
        myfile.WriteLine(";根据现场机器串口号进行修改");
        myfile.WriteLine(";ECMCONFIGFILE.ini中配置了电流表的串口号，应避免冲突");
        myfile.WriteLine(";**************************************");
        myfile.WriteLine();

        myfile.WriteLine("[COMPORT_ECIDCSM]");
        myfile.WriteLine("Ports=7,8,9");
        myfile.WriteLine("BaudRate=38400");
        myfile.WriteLine("Data_Ver=1.0.0.0");
        myfile.WriteLine("Filter=(7,33)(8,161)(8,162)(9,12)(9,51)(9,60)(9,54)");

        myfile.Close();
    }
}

void CsmOtherFile::WriteINTERDATA(const QString &outputPath)
{
    QString sta_name = CfgGenerator::ins()->station_name();
    QString file = outputPath + "\\" + sta_name + "\\Project\\SpecialCfg\\SDM\\INTERDATA__DIC_PARAM.INI";
    MyIniFile myfile(file);
    if(myfile.Open(QIODevice::WriteOnly | QIODevice::Truncate))
    {

        myfile.WriteLine(";接口解析配置，需手配");
        myfile.WriteLine();

        /// //////////////////////////////////////////////////////////
        myfile.WriteSec("CSM_SECTION_SA");
        myfile.WriteLine(";监测接口配置新加配置段\r\n;区段SA信息，来自XXX.block文件\r\n;序号    闭塞分区名称    验证编号");
        QMap<QString, QVector<BlockInfo> > map_block_info = TisCfgData::Ins()->GetBlockCfg()->mp_blockInfo();
        QMap<QString, QVector<BlockInfo> >::iterator iter = map_block_info.begin();

        int block_index = 1;
        while(iter != map_block_info.end())
        {
            QVector<BlockInfo> v_block = iter.value();
            foreach (BlockInfo ele, v_block)
            {
                QString key = QString("%1").arg(block_index, -4, 10);
                QString val;
                val += QString("%1,").arg(ele._block_name, 10);
                val += QString("%1").arg(ele._verify_no, 10 );
                myfile.Write(key, val);

                block_index++;
            }
            iter++;
        }
        /// //////////////////////////////////////////////////////////
        myfile.WriteLine();
        myfile.WriteSec("CSM_TCC_BORDER_INFO");
        myfile.WriteLine(";监测接口配置");
        myfile.WriteLine(";线路边界信息配置");
        myfile.WriteLine(";来源[xxxTIS-TIS接口表.xls],[地面设备信息表.xls]");
        myfile.WriteLine(";序号 = 方向口名称, 设备地址, 边界线路编号");
        QVector<TCC_Border_Unit> v_tcc_border = TisCfgData::Ins()->pTisTisCfg()->v_Tcc_border_info();
        int n_tcc_vorder_num = v_tcc_border.size();
        for(int i=0; i<n_tcc_vorder_num; i++)
        {
            QString key = QString::number(i+1);
            QString val;
            val += QString("%1,").arg(v_tcc_border[i]._name, 10);
            val += QString("%1,").arg(v_tcc_border[i]._addr, 10);
            val += QString("%1").arg(v_tcc_border[i]._order, 5);
            myfile.Write(key, val);
        }

        /// //////////////////////////////////////////////////////////
        myfile.WriteLine();
        myfile.WriteSec("TIS-ZPW_QJ_TRACK_CIRCUIT");
        myfile.WriteLine(";来源[xxxTIS-轨道电路接口表.xls]");
        QVector<ZPW_QJ_Unit> v_zpw_qj = TisCfgData::Ins()->pTisZpwCfg()->v_ZpwQjInfo();
        int n_zpw_qj_num = v_zpw_qj.size();
        for(int i=0; i<n_zpw_qj_num; i++)
        {
            QString key = QString("%1").arg(v_zpw_qj[i]._val_1, 2);
            QString val;
            val += QString("%1,").arg(v_zpw_qj[i]._val_2, 2);
            val += QString("%1,").arg(v_zpw_qj[i]._val_3, 2);
            val += QString("%1,").arg(v_zpw_qj[i]._val_4, 10);
            val += QString("%1,").arg(v_zpw_qj[i]._val_5, 10);
            val += QString("%1,").arg(v_zpw_qj[i]._val_6, 10);
            val += QString("%1,").arg(v_zpw_qj[i]._val_7, 10);
            val += QString("%1,").arg(v_zpw_qj[i]._val_8, 10);
            val += QString("%1,").arg(v_zpw_qj[i]._val_9, 10);
            val += QString("%1,").arg(v_zpw_qj[i]._val_10, 10);
            val += QString("%1,").arg(v_zpw_qj[i]._val_11, 2);
            val += QString("%1,").arg(v_zpw_qj[i]._val_12, 2);
            val += QString("%1").arg(v_zpw_qj[i]._val_13, 4);
            myfile.Write(key, val);
        }


        /// //////////////////////////////////////////////////////////
        myfile.WriteLine();
        myfile.WriteSec("TIS_FCK_NAME");
        myfile.WriteLine(";发车口区间逻辑检查未初始化报警");
        myfile.WriteLine(";序号=发车口名称");
        myfile.WriteLine(";最多32个发车口");

        QVector<QString> v_fck_names = TisCfgData::Ins()->pIFInfoCfg()->v_FCX_names();
        for(int i=0; i<v_fck_names.size(); i++)
        {
            QString key = QString::number(i+1);
            QString val = v_fck_names[i];
            myfile.Write(key, val);
        }

    }
    myfile.Close();
}

void CsmOtherFile::WriteIgnoreAlarm(const QString &outputPath)
{
    QString sta_name = CfgGenerator::ins()->station_name();
    QString file = outputPath + "\\" + sta_name + "\\Project\\SpecialCfg\\SDM\\SdmAlarmIgnore.ini";
    MyIniFile myfile(file);
    if(myfile.Open(QIODevice::WriteOnly | QIODevice::Truncate))
    {
        myfile.WriteLine(";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;");
        myfile.WriteLine(";; 配置要忽略的报警");
        myfile.WriteLine(";; 如果要屏蔽的报警是多个码位值的逻辑结果，则将这些码位名称全部配上");
        myfile.WriteLine(";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;");
        myfile.WriteLine(";[ignore_alarm]");
        myfile.WriteLine(";bool=name1#name2#name3");
        myfile.WriteLine(";digit=name1#name2#name3");
        myfile.WriteLine();
        myfile.WriteLine();

        myfile.WriteLine(";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;");
        myfile.WriteLine(";;                     配置bool码位报警的报警设备名称");
        myfile.WriteLine(";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;");
        myfile.WriteLine("; 报警码位名称 = 设备名称");
        myfile.WriteLine("[bool_alarm_device]");
        myfile.WriteLine("31363-RSBJ = 青藏高速场	");
        myfile.WriteLine("31363-YPBJ = 青藏高速场");
        myfile.WriteLine("31363-QYPBJ = 青藏高速场");
        myfile.WriteLine("31363-QDYPBJ = 青藏高速场");
        myfile.WriteLine();
        myfile.WriteLine();

        myfile.WriteLine(";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;");
        myfile.WriteLine(";;                             BOOL报警");
        myfile.WriteLine(";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;");
        myfile.WriteLine("[TIS_Alarm_Bool]");
        myfile.WriteLine("count = 4");
        myfile.WriteLine();

        myfile.WriteLine("; 熔丝报警");
        myfile.WriteLine("[TIS_Alarm_Bool\\1]");
        myfile.WriteLine("ID = 13");
        myfile.WriteLine("MatchRule = -RSBJ");
        myfile.WriteLine("AlarmCode = 110003");
        myfile.WriteLine("AlarmHappen  = 1");
        myfile.WriteLine("AlarmRecover = 0");
        myfile.WriteLine();

        myfile.WriteLine("; 站内移频报警");
        myfile.WriteLine("[TIS_Alarm_Bool\\2]");
        myfile.WriteLine("ID = 14");
        myfile.WriteLine("MatchRule = -YPBJ");
        myfile.WriteLine("AlarmCode = 110004");
        myfile.WriteLine("AlarmHappen  = 1");
        myfile.WriteLine("AlarmRecover = 0");
        myfile.WriteLine();

        myfile.WriteLine("; 区间设备故障");
        myfile.WriteLine("[TIS_Alarm_Bool\\3]");
        myfile.WriteLine("ID = 15");
        myfile.WriteLine("MatchRule = -QDYPBJ");
        myfile.WriteLine("AlarmCode = 110005");
        myfile.WriteLine("AlarmHappen  = 0");
        myfile.WriteLine("AlarmRecover = 1");
        myfile.WriteLine();

        myfile.WriteLine("; 区间移频故障");
        myfile.WriteLine("[TIS_Alarm_Bool\\4]");
        myfile.WriteLine("ID = 16");
        myfile.WriteLine("MatchRule = -QYPBJ");
        myfile.WriteLine("AlarmCode = 110006");
        myfile.WriteLine("AlarmHappen  = 0");
        myfile.WriteLine("AlarmRecover = 1");
        myfile.WriteLine();

        myfile.Close();
    }
}

void CsmOtherFile::WriteTleCfg(const QString &outputPath)
{
    QString sta_name = CfgGenerator::ins()->station_name();
    QString file = outputPath + "\\" + sta_name + "\\Project\\TleCfg\\tledata.cfg";
    MyIniFile myfile(file);
    if(myfile.Open(QIODevice::WriteOnly | QIODevice::Truncate))
    {
        myfile.WriteSec("STATION");
        myfile.WriteLine("; 站号=sta文件路径,车站画面宽度,车站画面高度");

        QVector<int> v_sta_no = CfgGenerator::ins()->GetAllStationNo();
        foreach (int sta_no, v_sta_no) {
            QString key = QString::number(sta_no);
            QString val = "sta_file:mor_data\\dmis_ctc." + QString::number(sta_no) + ".sta,width:3200,height:1280";
            myfile.Write(key, val);
        }
        myfile.WriteLine();

        // 多站情况下要增加[SECTION]
        if(v_sta_no.size() > 1)
        {
            myfile.WriteSec("SECTION");
            myfile.WriteLine("; 区段号=区段名,站号列表,区段画面宽度,区段画面高度");
            QString key = QString::number(1);
            QString val = "name:SECTION_NAME,station_list:";

            foreach (int sta_no, v_sta_no) {
                val += QString::number(sta_no) + "/";
            }
            val.remove(QRegularExpression("/$"));
            val += ",width:9600,height:3600";
            myfile.Write(key, val);
        }


        myfile.WriteSec("RUN_FLAG");
        myfile.WriteLine("; 是否处理分路不良信息");
        myfile.Write("Badness_to_be_processed", "0");

        myfile.Close();
    }
}

void CsmOtherFile::WriteNetLinkDelayeCfg(const QString &outputPath)
{
    QString sta_name = CfgGenerator::ins()->station_name();
    QString file = outputPath + "\\" + sta_name + "\\Project\\SpecialCfg\\SDM\\SDM_DEPEND\\NetLinkDelayTime.INI";
    MyIniFile myfile(file);
    if(myfile.Open(QIODevice::WriteOnly | QIODevice::Truncate))
    {
        myfile.WriteLine(";网络状态延时时间配置");
        myfile.WriteLine(";中断延时时间");
        myfile.WriteLine(";超时延时时间");
        myfile.WriteLine();

        myfile.WriteSec("DefaultParam");

        QString key = "ErrorDelayTime";
        QString val = "3";
        myfile.Write(key, val);

        key = "TimeOutValue";
        val = "15";
        myfile.Write(key, val);

        myfile.Close();
    }
}

void CsmOtherFile::CopyFile(const QString &outputPath)
{
    QString inputDir = CfgGenerator::ins()->inputPath();
    QString sta_name = CfgGenerator::ins()->station_name();

    QString fromFile = "";
    QString toFile = "";

    // XXX.ADSVAR
    QVector<QString> v_adss = CfgGenerator::ins()->Ads_files();
    foreach (QString ele, v_adss) {
        fromFile = inputDir + "\\" + ele;
        toFile = outputPath + "\\" + sta_name + "\\Project\\SpecialCfg\\SDM\\SDM_DEPEND\\" + ele;
        CommonMethod::CopyFileToPath(fromFile, toFile, true);
    }

    // XXX.VTL
    QVector<QString> v_vtls = CfgGenerator::ins()->Vtl_files();
    foreach (QString ele, v_vtls) {

        fromFile = inputDir + "\\" + ele;
        toFile = outputPath + "\\" + sta_name + "\\Project\\SpecialCfg\\SDM\\SDM_DEPEND\\" + ele;
        CommonMethod::CopyFileToPath(fromFile, toFile, true);
    }

    // SDMHdwToFrameView.xml
    fromFile = inputDir + "\\SDMHdwToFrameView.xml";
    toFile = outputPath + "\\" + sta_name + "\\Project\\SpecialCfg\\SDM\\SDM_DEPEND\\SDMHdwToFrameView.xml";
    CommonMethod::CopyFileToPath(fromFile, toFile, true);

    // dmis_XXXXX.XXX
    QVector<QString> v_dmis = CfgGenerator::ins()->dmis_files();
    foreach (QString ele, v_dmis) {
        fromFile = inputDir + "\\" + ele;
        toFile = outputPath + "\\" + sta_name + "\\Project\\TleCfg\\mor_data\\" +ele;
        CommonMethod::CopyFileToPath(fromFile, toFile, true);
    }

    // LAYOUTCTRL.CFG
    fromFile = inputDir + "\\LAYOUTCTRL.CFG";
    toFile = outputPath + "\\" + sta_name + "\\Project\\TleCfg\\LAYOUTCTRL.CFG";
    CommonMethod::CopyFileToPath(fromFile, toFile, true);

   // QCAlarm.CFG
   QVector<QString> v_qcalarm = CfgGenerator::ins()->qcalarm_files();
   foreach (QString ele, v_qcalarm)
   {
       fromFile = inputDir + "\\" + ele;
       toFile = outputPath + "\\" + sta_name + "\\Project\\SpecialCfg\\SDM\\SDM_DEPEND\\" + ele;
       CommonMethod::CopyFileToPath(fromFile, toFile, true);
   }
}
