#include "CsmEcidHdw.h"
#include "EcidManager.h"
#include "BoardDefine.h"
#include "MyIniFile.h"
#include "CommonMethod.h"
#include "CsmDataDefine.h"
#include "BoardFactory.h"
#include "TisCfgData.h"
#include "TisCfgGenerator.h"

CsmEcidHdw::CsmEcidHdw()
{

}

void CsmEcidHdw::WriteToFile(const QString &outputPath)
{
    EcidManager& ecid_manager = Singleton<EcidManager>::Instance();
    int ecid_cnt = ecid_manager.GetEcidCount();

    for(int i=0; i<ecid_cnt; i++)
    {
        ECID* pEcid = ecid_manager.GetEcid(i+1);
        WriteSingleEcid(pEcid, outputPath);
    }
}

void CsmEcidHdw::WriteSingleEcid(const ECID *pEcid, const QString &outputPath)
{
    QString sta_name = CfgGenerator::ins()->station_name();
    QString file = outputPath + "\\" + sta_name + "\\Project\\SpecialCfg\\SDM\\SDM_DEPEND\\ECID\\" + QString("ECID%1.HDW_QDZ").arg(pEcid->Order());

    MyIniFile myfile(file);
    if(myfile.Open(QIODevice::WriteOnly | QIODevice::Truncate))
    {
        QString sec = "HOST";
        myfile.WriteSec(sec);

        QString key = "STATION_NAME";
        QString val = CfgGenerator::ins()->station_name();
        myfile.Write(key, val);

        key = "version";
        val = "V1.0.0";
        myfile.Write(key, val);

        key = "STATION_ID";
        val = TisCfgData::Ins()->GetStano();
        myfile.Write(key, val);

        key = "ECID_ID";
        val = QString("ECID%1").arg(pEcid->Order());
        myfile.Write(key, val);

        myfile.WriteLine();
        myfile.WriteLine();
        myfile.WriteLine();

        // 板卡的信息暂时先放在板卡类里实现
        const QVector<BoardBase *> v_board = pEcid->GetAllBoard();
        foreach(const BoardBase* pBoard, v_board)
        {
            pBoard->WriteEcidHdw(&myfile);
        }

        myfile.Close();
    }
}
