#include "TisTisTable.h"
#include "ExcelWrapper.h"
#include "TisCfgGenerator.h"
#include "GroundEquipmentTable.h"
#include "TisCfgData.h"

TisTisTable::TisTisTable()
{

}

void TisTisTable::LoadCfg(const QString &inputFilePath)
{
    QVector<QString> v_files = CfgGenerator::ins()->tis_tis_files();
    foreach (const QString& ele, v_files)
    {
        QString file = inputFilePath + "\\" + ele;

        ExcelBook book;
        if(!book.readExcel(file))
            return;

        ExcelSheet sheet;
        if(!book.GetSheet("区间改方与边界数据表", sheet))
            return;

        int cols = sheet.GetCols();
        int rows = sheet.GetRows();
        if( cols<=0 || rows<=0)
            return;

        int row1 = sheet.GetStartRow("区间口名称");
        int col1 = sheet.GetStartCol("区间口名称");
        if(row1 == -1 || col1 == -1)
            return;

        int col2 = sheet.GetStartCol("边界线路编号");
        if(col2 == -1)
            return;

        int col3 = col2 + 1;
        if(col3 == -1)
            return;

        GroundEquipmentTable * pGroundEquCfg = TisCfgData::Ins()->pGroundEquCfg();
        QMap<QString, QString> mp_equ = pGroundEquCfg->mp_sta_addr();

        for(int i=row1+1; i<rows; i++)
        {
            QString val1;
            QString val2;
            QString val3;

            sheet.GetCellStringValue(i, col1, val1);
            sheet.GetCellStringValue(i, col2, val2);
            sheet.GetCellStringValue(i, col3, val3);
            val3 = mp_equ[val3];

            if(val1.isEmpty() || val2.isEmpty() || val3.isEmpty() || val2.contains("-"))
                continue;

            val3 = "0x" + val3;

            TCC_Border_Unit one_unit;
            one_unit._name = val1;
            one_unit._addr = val3;
            one_unit._order = val2.toInt();

            m_v_Tcc_border_info.push_back(one_unit);
        }
    }
    return;
}

QVector<TCC_Border_Unit> TisTisTable::v_Tcc_border_info() const
{
    return m_v_Tcc_border_info;
}
