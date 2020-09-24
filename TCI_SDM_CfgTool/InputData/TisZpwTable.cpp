#include "TisZpwTable.h"
#include "ExcelWrapper.h"
#include "TisCfgGenerator.h"

TisZpwTable::TisZpwTable()
{

}

void TisZpwTable::LoadCfg(const QString &inputFilePath)
{
    QVector<QString> v_files = CfgGenerator::ins()->tis_zpw_files();
    foreach (const QString& ele, v_files)
    {
        QString file = inputFilePath + "\\" + ele;

        ExcelBook book;
        if(!book.readExcel(file))
            return;

        ExcelSheet sheet;
        if(!book.GetSheet("区间轨道电路信息表", sheet))
            return;

        int cols = sheet.GetCols();
        int rows = sheet.GetRows();
        if( cols<=0 || rows<=0)
            return;

        int row1 = sheet.GetStartRow("序号");
        int col1 = sheet.GetStartCol("序号");
        if(row1 == -1 || col1 == -1)
            return;


        for(int i=row1+1; i<rows; i++)
        {
            QString val_1, val_2, val_3, val_4, val_5, val_6, val_7, val_8, val_9, val_10, val_11, val_12, val_13;

            sheet.GetCellStringValue(i, col1+0, val_1);
            sheet.GetCellStringValue(i, col1+1, val_2);
            sheet.GetCellStringValue(i, col1+2, val_3);
            sheet.GetCellStringValue(i, col1+3, val_4);
            sheet.GetCellStringValue(i, col1+4, val_5);
            sheet.GetCellStringValue(i, col1+5, val_6);
            sheet.GetCellStringValue(i, col1+6, val_7);
            sheet.GetCellStringValue(i, col1+7, val_8);
            sheet.GetCellStringValue(i, col1+8, val_9);
            sheet.GetCellStringValue(i, col1+9, val_10);
            sheet.GetCellStringValue(i, col1+10, val_11);
            sheet.GetCellStringValue(i, col1+11, val_12);
            sheet.GetCellStringValue(i, col1+12, val_13);

            if(val_1.toInt()<=0)
                continue;

            ZPW_QJ_Unit one_unit;
            one_unit._val_1 = val_1;
            one_unit._val_2 = val_2;
            one_unit._val_3 = val_3;
            one_unit._val_4 = val_4;
            one_unit._val_5 = val_5;
            one_unit._val_6 = val_6;
            one_unit._val_7 = val_7;
            one_unit._val_8 = val_8;
            one_unit._val_9 = val_9;
            one_unit._val_10 = val_10;
            one_unit._val_11 = val_11;
            one_unit._val_12 = val_12;
            one_unit._val_13 = val_13;


            m_v_ZpwQjInfo.push_back(one_unit);
        }
    }
    return;
}

QVector<ZPW_QJ_Unit> TisZpwTable::v_ZpwQjInfo() const
{
    return m_v_ZpwQjInfo;
}
