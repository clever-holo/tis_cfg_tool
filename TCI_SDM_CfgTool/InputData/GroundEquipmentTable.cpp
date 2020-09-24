#include "GroundEquipmentTable.h"
#include "TisCfgGenerator.h"
#include "ExcelWrapper.h"

GroundEquipmentTable::GroundEquipmentTable()
{

}

void GroundEquipmentTable::LoadCfg(const QString& inputFilePath)
{
    QVector<QString> v_files = CfgGenerator::ins()->ground_equ_files();
    foreach (const QString& ele, v_files)
    {
        QString file = inputFilePath + "\\" + ele;

        ExcelBook book;
        if(!book.readExcel(file))
            return;

        ExcelSheet sheet;
        if(!book.GetSheet("车站设备", sheet))
            return;

        int cols = sheet.GetCols();
        int rows = sheet.GetRows();
        if( cols<=0 || rows<=0)
            return;

        int station_row = sheet.GetStartRow("车站名称");
        int station_col = sheet.GetStartCol("车站名称");
        if(station_col == -1 || station_row == -1)
            return;

        int addr_col = sheet.GetStartCol("TIS安全协议校验源地址");
        if(addr_col == -1)
            return;

        for(int i=station_row+1; i<rows; i++)
        {
            QString sta_name;
            QString addr;
            sheet.GetCellStringValue(i, station_col, sta_name);
            sheet.GetCellStringValue(i, addr_col, addr);


            if(sta_name.isEmpty() || addr.isEmpty())
                continue;

            m_mp_sta_addr[sta_name] = addr;
        }
    }
    return;
}

QMap<QString, QString> GroundEquipmentTable::mp_sta_addr() const
{
    return m_mp_sta_addr;
}
