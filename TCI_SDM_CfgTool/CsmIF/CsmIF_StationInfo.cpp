#include "CsmIF_StationInfo.h"
#include "MyIniFile.h"
#include "TisCfgData.h"
#include "AdsVarCfg.h"

CsmIF_StationInfo::CsmIF_StationInfo()
{
    myfile = nullptr;
    m_counter = 0;
}

void CsmIF_StationInfo::OutPutFile(const QString &str_output_path)
{
    QString file = str_output_path + "监测接口站场码位顺序表.ini";
    myfile = new MyIniFile(file);

    if(myfile->Open(QIODevice::WriteOnly | QIODevice::Truncate))
    {
        OutPutVersion();
        OutPutStaCode();
        OutPutIpsBoard();


    }
    CloseFile();
}

void CsmIF_StationInfo::OutPutVersion()
{
    myfile->WriteSec("版本定义");
    myfile->WriteSec("协议版本=1.0");
    myfile->WriteSec("数据版本=1.0.5");
    myfile->WriteLine();
}

void CsmIF_StationInfo::OutPutStaCode()
{
    myfile->WriteSec("码位");
    AdsVarCfg* pVarCfg = TisCfgData::Ins()->GetAdsVarCfg();
    const QVector<SingleStationAdsVar>& var_info = pVarCfg->GetVarInfo();

    for(int i=0; i<var_info.size(); i++)
    {
        const SingleStationAdsVar& singles_station = var_info[i];
        myfile->WriteLine(";表示码位");
        OutPutStaCode2(singles_station.m_mpIndiCode);

        myfile->WriteLine(";控制码位");
        OutPutStaCode2(singles_station.m_mpCtrlCode);
    }
    myfile->WriteLine();
}

void CsmIF_StationInfo::OutPutStaCode2(const QMap<int, QString> &mp_var)
{
    QMap<int, QString>::const_iterator it = mp_var.begin();
    for(; it != mp_var.end(); it++)
    {
        m_counter++;
        QString key = QString("%1").arg(m_counter, -4);
        QString val = QString("%1").arg(it.value(), -30);
        myfile->Write(key, val);
    }

    while(m_counter % 8 != 0)
    {
        m_counter++;
        QString key = QString("%1").arg(m_counter, -4);
        QString val = QString("%1").arg("Dummy", -30);
        myfile->Write(key, val);
    }
}

void CsmIF_StationInfo::OutPutIpsBoard()
{
    myfile->WriteLine(";IPS板卡状态");

    const int c_bytes = 4;  // 占用4个字节
    const int c_board_cnt = 12;
    const QString ips_board[] =
    {
        "A系MPU1状态",
        "B系MPU1状态",
        "A系MPU2状态",
        "B系MPU2状态",
        "A系MNCU状态",
        "B系MNCU状态",
        "A系MCU状态",
        "B系MCU状态",
        "A系MNCU2状态",
        "B系MNCU2状态",
        "A系MCU2状态",
        "B系MCU2状态"
    };

    for(int i=0; i<c_board_cnt; i++)
    {
        m_counter++;
        QString key = QString("%1").arg(m_counter, -4);
        QString val = QString("%1").arg(ips_board[i], -30);
        myfile->Write(key, val);
    }

    int dummy_cnt = c_bytes * 8 - c_board_cnt;
    for(int i=0; i < dummy_cnt; i++ )
    {
        m_counter++;
        QString key = QString("%1").arg(m_counter, -4);
        QString val = QString("%1").arg("Dummy", -30);
        myfile->Write(key, val);
    }
    myfile->WriteLine();
}

void CsmIF_StationInfo::CloseFile()
{
    if(myfile != nullptr)
    {
        myfile->Close();
        delete myfile;
        myfile = nullptr;
    }
}
