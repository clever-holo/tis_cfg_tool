#include "TisCfgGenerator.h"
#include <QDir>
#include <QFileInfoList>
#include "CommonMethod.h"
#include "TisCfgData.h"
#include "IpsManager.h"
#include "EcidManager.h"
#include "CsmDataManager.h"
#include <QRegularExpression>
#include <QTextStream>
#include <QMessageBox>
#include <QTime>
#include <QApplication>
#include "CsmIFCfg.h"

CfgGenerator* CfgGenerator::m_instance = nullptr;

CfgGenerator::CfgGenerator()
{

}

CfgGenerator* CfgGenerator::ins()
{
    if(m_instance == nullptr)
        m_instance = new CfgGenerator();
    return m_instance;
}

CfgGenerator::~CfgGenerator()
{

}

QString CfgGenerator::inputPath() const
{
    return m_inputPath;
}

void CfgGenerator::setInputPath(const QString &inputPath)
{
    m_inputPath = inputPath;
    FindInputFileImpl(m_inputPath + "\\", "");
    ParseStationInfo();
}

QString CfgGenerator::outputPath() const
{
    return m_outputPath;
}

void CfgGenerator::setOutputPath(const QString &outputPath)
{
    m_outputPath = outputPath;
}

QString CfgGenerator::dbm() const
{
    return m_dbm;
}

void CfgGenerator::setDbm(const QString &dbm)
{
    m_dbm = dbm;
}

QString CfgGenerator::station_name() const
{
    return m_station_name;
}

void CfgGenerator::setStation_name(const QString &station_name)
{
    m_station_name = station_name;
}

QString CfgGenerator::station_no() const
{
    return m_station_no;
}

void CfgGenerator::setStation_no(const QString &station_no)
{
    m_station_no = station_no;
}

void CfgGenerator::FindInputFileImpl(const QString &str_base_path, const QString &str_relative_path)
{
    QString my_path = str_base_path + str_relative_path;
    QDir sourceDir(my_path);

    QFileInfoList fileInfoList = sourceDir.entryInfoList();
    foreach(QFileInfo fileInfo, fileInfoList)
    {
        if(fileInfo.fileName() == "." || fileInfo.fileName() == "..")
            continue;

        if(fileInfo.isFile())
        {
            QString file_name = fileInfo.fileName();
            ParseFileType(str_relative_path, file_name);
        }
        else
        {
            FindInputFileImpl(str_base_path, str_relative_path + fileInfo.fileName() + "\\");
        }
    }
}

void CfgGenerator::ParseFileType(const QString &str_relative_path, const QString &file_name)
{
    if(file_name.endsWith(".ADSVAR"))
    {
        m_ads_files.append(str_relative_path + file_name);
    }
    else if(file_name.endsWith(".VTL"))
    {
        m_vtl_files.append(str_relative_path + file_name);
    }
    else if(file_name.contains("接口码位表") && (file_name.endsWith(".xls") || file_name.endsWith(".xlsx")))
    {
        m_codeXls = str_relative_path + file_name;
    }
    else if(file_name.contains("dmis"))
    {
        m_dmis_files.append(str_relative_path + file_name);
    }
    else if(file_name.contains("内部IP地址分配表"))
    {
        m_ip_internal = str_relative_path + file_name;
    }
    else if(file_name.contains("信号安全数据网IP地址分配表"))
    {
        m_ip_external = str_relative_path + file_name;
    }
    else if(file_name.endsWith(".BLOCK", Qt::CaseInsensitive))
    {
        m_block_files.append(str_relative_path + file_name);
    }
    else if(file_name.contains("地面设备信息表")&& (file_name.endsWith(".xls") || file_name.endsWith(".xlsx")))
    {
        m_ground_equ_files.append(str_relative_path + file_name);
    }
    else if(file_name.contains("TIS-TIS接口表")&& (file_name.endsWith(".xls") || file_name.endsWith(".xlsx")))
    {
        m_tis_tis_files.append(str_relative_path + file_name);
    }
    else if(file_name.contains("TIS-轨道电路接口表")&& (file_name.endsWith(".xls") || file_name.endsWith(".xlsx")))
    {
        m_tis_zpw_files.append(str_relative_path + file_name);
    }
    else if(file_name.endsWith("QCAlarm.CFG", Qt::CaseInsensitive))
    {
        m_qcalarm_files.append(str_relative_path + file_name);
    }
    else if(file_name.contains("接口信息配置表")&& (file_name.endsWith(".xls") || file_name.endsWith(".xlsx")))
    {
        m_if_info_files.append(str_relative_path + file_name);
    }
}

// 从vtl文件中读取站号和站名
void CfgGenerator::ParseStationInfo()
{
    foreach (const QString& vtl, m_vtl_files)
    {
        QString vtl_path = m_inputPath + "\\" + vtl;

        QFile file(vtl_path);
        if (file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QTextStream stream(&file);

            QString line_in;
            stream.seek(file.size());//将当前读取文件指针移动到文件末尾
            stream.seek(0);//将当前读取文件指针移动到文件开始

            QString station_name = "";
            int     station_no = 0;
            QRegularExpression rx_name("^\\*+\\s+车站名称:\\s+([\u4e00-\u9fa5_a-zA-Z0-9]+)\\s+\\*+");
            QRegularExpression rx_no("^\\*+\\s+站号:\\s+(\\d+)\\s+\\*+");
            QRegularExpressionMatchIterator reg_it;

            bool name_ok = false;
            bool no_ok   = false;

            while( !stream.atEnd())
            {
                line_in = stream.readLine();

                reg_it = rx_name.globalMatch(line_in);
                if(reg_it.hasNext())
                {
                    station_name = reg_it.next().captured(1);
                    name_ok = true;
                }

                reg_it = rx_no.globalMatch(line_in);
                if(reg_it.hasNext())
                {
                    station_no = reg_it.next().captured(1).toInt();
                    no_ok = true;
                }

                if(name_ok && no_ok)
                    break;
            }

            if(name_ok && no_ok)
            {
                m_map_station_no2name[station_no] = station_name;
                m_map_station_name2no[station_name] = station_no;
            }

            file.close();
        }
    }
}

void CfgGenerator::slot_InputFileSelected(const QString &inputPath)
{
    setInputPath(inputPath);
}

void CfgGenerator::slot_OutputFileSelected(const QString &OutputPath)
{
    setOutputPath(OutputPath);
}

void CfgGenerator::slot_DbmEdited(const QString &dbm)
{
    setDbm(dbm);
}

void CfgGenerator::slot_BeginGenerator()
{
    GenerateCfg();
}

QVector<int> CfgGenerator::GetAllStationNo() const
{
    QVector<int> v_sta_no;
    QMapIterator<int, QString> it(m_map_station_no2name);
    while(it.hasNext())
        v_sta_no.push_back(it.next().key());

    return v_sta_no;
}

void CfgGenerator::GenerateCfg()
{
    // 输入路径不存在
    if(!CommonMethod::IsFileExist(m_inputPath))        
        return;

    // 输出路径不存在
    if(!CommonMethod::IsFileExist(m_outputPath))    
        return;

    QTime time;
    time.start();

    // 加载配置文件
    TisCfgData::Ins()->Init(m_inputPath);

    // 生成IPS开关量和枚举量
    Singleton<IpsManager>::Instance().GenerateCsmData();

    // 转换接口码位表配置
    Singleton<EcidManager>::Instance().LoadEcidInfo(TisCfgData::Ins()->GetCodeTableCfg());

    // 生成ECID的Data
    Singleton<EcidManager>::Instance().GenerateData();

    // 输出配置（文件）
    Singleton<CsmDataManager>::Instance().WriteToFile(m_outputPath);

    // 输出监测配置
    CsmIFCfg::ins()->GenerateCsmIF(m_outputPath);

    int time_len = time.elapsed() / 1000;
    QMessageBox::information(nullptr, "title", "配置转换完成,用时" + QString::number(time_len) + "秒", QMessageBox::Ok, QMessageBox::Ok);
    qApp->quit();
}
