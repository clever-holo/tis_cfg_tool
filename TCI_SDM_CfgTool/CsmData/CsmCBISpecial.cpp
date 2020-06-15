#include "CsmCBISpecial.h"
#include "IpsManager.h"
#include "EcidManager.h"
#include "BoardDefine.h"
#include "MyIniFile.h"
#include "CommonMethod.h"
#include "CsmDataDefine.h"
#include "CsmDevice.h"
#include "BoardFactory.h"
#include "TisCfgGenerator.h"

CsmCBISpecial::CsmCBISpecial()
{

}

void CsmCBISpecial::WriteToFile(const QString &outputPath)
{
    QString sta_name = CfgGenerator::ins()->station_name();
    QString file = outputPath + "\\" + sta_name + "\\Project\\SpecialCfg\\SDM\\CBISpecial.INI" ;
    MyIniFile myfile(file);
    if(myfile.Open(QIODevice::WriteOnly | QIODevice::Truncate))
    {
        WriteIps(myfile);
        WriteEcid(&myfile);
        myfile.Close();
    }

}

void CsmCBISpecial::WriteIps(MyIniFile& myfile)
{
    myfile.WriteSec("IPS接口信息");

    IpsManager& ips = Singleton<IpsManager>::Instance();
    QString key1 = "联锁系统接口号";
    QString key2 = "联锁A机接口号";
    QString key3 = "联锁B机接口号";
    QString val1 = QString::number(ips.PluginMain()._plugin_id);
    QString val2 = QString::number(ips.PluginA()._plugin_id);
    QString val3 = QString::number(ips.PluginB()._plugin_id);
    myfile.Write(key1, val1);
    myfile.Write(key2, val2);
    myfile.Write(key3, val3);
    myfile.WriteLine();
    myfile.WriteLine();
    myfile.WriteLine();
}

void CsmCBISpecial::WriteEcid(MyIniFile *myfile)
{
    EcidManager& ecid_manager = Singleton<EcidManager>::Instance();
    int ecid_cnt = ecid_manager.GetEcidCount();

    myfile->WriteSec("ECID基本信息");
    QString key = "总数";
    QString val = QString::number(ecid_cnt);
    myfile->Write(key, val);
    myfile->WriteLine();
    myfile->WriteLine();
    myfile->WriteLine();


    int host_id = 301;
    for(int i=0; i<ecid_cnt; i++)
    {
        ECID* pEcid = ecid_manager.GetEcid(i+1);

        QString sec = QString("ECID接口信息\\%1").arg(i+1);
        myfile->WriteSec(sec);

        QString key = "A机主机号";
        QString val = QString::number(host_id++);
        myfile->Write(key, val);

        key = "B机主机号";
        val = QString::number(host_id++);
        myfile->Write(key, val);

        key = "A机所在机柜号";
        val = QString::number(1);
        myfile->Write(key, val);

        key = "B机所在机柜号";
        val = QString::number(1);
        myfile->Write(key, val);

        key = "主机接口号";
        val = QString::number(pEcid->plugin_main()._plugin_id);
        myfile->Write(key, val);

        key = "A机接口号";
        val = QString::number(pEcid->plugin_A()._plugin_id);
        myfile->Write(key, val);

        key = "B机接口号";
        val = QString::number(pEcid->plugin_B()._plugin_id);
        myfile->Write(key, val);

        key = "A机设备名称";
        val = pEcid->DevA()->_name;
        myfile->Write(key, val);

        key = "A机设备ID";
        val = pEcid->DevA()->_uuid;
        myfile->Write(key, val);

        key = "B机设备名称";
        val = pEcid->DevB()->_name;
        myfile->Write(key, val);

        key = "B机设备ID";
        val = pEcid->DevB()->_uuid;
        myfile->Write(key, val);

        key = "板卡数量";
        val = QString::number(pEcid->GetAllBoard().size());
        myfile->Write(key, val);

        myfile->WriteLine();
        myfile->WriteLine();
        myfile->WriteLine();

        // 生成板卡配置
        WriteBoard(myfile, pEcid);
    }
}

void CsmCBISpecial::WriteBoard(MyIniFile *myfile, const ECID *pEcid)
{
    const QVector<BoardBase *> v_board = pEcid->GetAllBoard();

    int order = 0;
    foreach(const BoardBase* pBoard, v_board)
    {
        order++;

        QString sec = QString("ECID板卡信息\\%1\\%2").arg(pEcid->Order()).arg(order);
        myfile->WriteSec(sec);

        QString key = "板卡类型";
        QString val = BoardFactory::GetCbiTypeName(pBoard->BoardType());
        myfile->Write(key, val);

        key = "A机实际机笼位置";
        val = QString::number(pBoard->Rock_A());
        myfile->Write(key, val);

        key = "A机实际槽道位置";
        val = QString::number(pBoard->Slot_A());
        myfile->Write(key, val);

        key = "B机实际机笼位置";
        val = QString::number(pBoard->Rock_B());
        myfile->Write(key, val);

        key = "B机实际槽道位置";
        val = QString::number(pBoard->Slot_B());
        myfile->Write(key, val);

        key = "A机监测设备名称";
        val = pBoard->BoardDevA()->_name;
        myfile->Write(key, val);

        key = "A机监测设备ID";
        val = pBoard->BoardDevA()->_uuid;
        myfile->Write(key, val);

        key = "B机监测设备名称";
        val = pBoard->BoardDevB()->_name;
        myfile->Write(key, val);

        key = "B机监测设备ID";
        val = pBoard->BoardDevB()->_uuid;
        myfile->Write(key, val);

        key = "板卡灯状态码位数量";
        val = QString::number(BoardFactory::GetMaxLamp(pBoard->BoardType()));
        myfile->Write(key, val);

        key = "采集码位数量";
        val = QString::number(BoardFactory::GetMaxDi(pBoard->BoardType()));
        myfile->Write(key, val);

        key = "驱动码位数量";
        val = QString::number(BoardFactory::GetMaxSbo(pBoard->BoardType()));
        myfile->Write(key, val);

        key = "开关量起始码位偏移";
        const QVector<CsmDataDigit*>& v_digit = pBoard->Digits(pBoard->PluginID_A());
        val = QString::number(v_digit.isEmpty() ? 0 : v_digit.first()->_OrderNo);
        myfile->Write(key, val);

        key = "枚举量起始码位偏移";
        const QVector<CsmDataEnum*>& v_enum = pBoard->Enums(pBoard->PluginID_A());
        val = QString::number(v_enum.isEmpty() ? 0 : v_enum.first()->_OrderNo);
        myfile->Write(key, val);

        const QVector<CsmDataAnalog*>& v_analog = pBoard->Analogs(pBoard->PluginID_A());
        key = "模拟量个数";
        val = QString::number(v_analog.size());
        myfile->Write(key, val);

        int count = 0;
        foreach (const CsmDataAnalog* var, v_analog)
        {
            count++;
            key = QString("analog_%1").arg(count);
            val = QString("%1,%2").arg(var->_TypeID,3).arg(var->_OrderNo, 3);
            myfile->Write(key, val);
        }

        const QVector<CsmDataCurve*>& v_curve = pBoard->Curves(pBoard->PluginID_A());
        key = "曲线量个数";
        val = QString::number(v_curve.size());
        myfile->Write(key, val);

        count = 0;
        foreach (const CsmDataCurve* var, v_curve)
        {
            count++;
            key = QString("curve_%1").arg(count);
            val = QString("%1,%2").arg(var->_TypeID,3).arg(var->_OrderNo, 3);
            myfile->Write(key, val);
        }

        myfile->WriteLine();
        myfile->WriteLine();
        myfile->WriteLine();
    }

    return;
}
