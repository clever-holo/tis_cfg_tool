#include "IFInfoTable.h"
#include "TisCfgGenerator.h"
#include "TisCfgData.h"
#include "ExcelWrapper.h"

IFInfoTable::IFInfoTable()
{

}

void IFInfoTable::LoadCfg(const QString &inputFilePath)
{
    QVector<QString> table_names = CfgGenerator::ins()->if_info_files();

    if(table_names.size() == 0)
    {
        // Log
        return;
    }

    QMap<int, OneStationIF> mp_sta_if;
    foreach (const QString& var, table_names)
    {
        QString file_name = inputFilePath + "\\" + var;
        OneStationIF one_sta;
        if(LoadOneTable(file_name, one_sta))
        {
            mp_sta_if[one_sta._sta_no] = one_sta;
        }
    }

    if(mp_sta_if.isEmpty())
    {
        return;
    }

    MergeFckName(mp_sta_if);
}

QVector<QString> IFInfoTable::v_FCX_names() const
{
    return m_v_FCX_names;
}

bool IFInfoTable::LoadOneTable(const QString &file_name, OneStationIF &one_sta)
{
    ExcelBook book;
    if(!book.readExcel(file_name))
    {
        return false;
    }

    return LoadBaseInfo(&book, one_sta) && LoadFckInfo(&book, one_sta);
}

bool IFInfoTable::LoadBaseInfo(ExcelBook *book, OneStationIF &one_sta)
{
    QMap<QString, int> name2no = CfgGenerator::ins()->map_station_name2no();

    ExcelSheet sheet;
    if(!book->GetSheet("系统基本信息", sheet))
    {
        return false;
    }

    int cols = sheet.GetCols();
    int rows = sheet.GetRows();
    if( cols<=0 || rows<=0)
        return false;

    int row1 = sheet.GetStartRow("车站名称");
    int col1 = sheet.GetStartCol("车站名称");
    if(row1 == -1 || col1 == -1)
    {
        return false;
    }

    QString local_sta_name;
    sheet.GetMergeCellStringValue(row1 + 1, col1, local_sta_name);
    if(!local_sta_name.isEmpty())
    {
        one_sta._sta_no = name2no[local_sta_name];
    }
    else
    {
        return false;
    }

    int row2 = sheet.GetStartRow("控制车站");
    int col2 = sheet.GetStartCol("控制车站");
    if(row2 == -1 || col2 == -2)
    {
        return false;
    }

    for(int row_i = row2 + 1; row_i < rows; row_i++)
    {
        QString ctrl_sta_name;
        sheet.GetMergeCellStringValue(row_i, col2, ctrl_sta_name);
        if(!ctrl_sta_name.isEmpty())
        {
            one_sta._sub_sta_no.append(name2no[ctrl_sta_name]);
        }
        else
        {
            break;
        }
    }
    return true;
}

bool IFInfoTable::LoadFckInfo(ExcelBook *book, OneStationIF &one_sta)
{
    ExcelSheet sheet;
    if(!book->GetSheet("规则软件交互_区间闭塞分区、信号机", sheet))
    {
        return false;
    }

    int cols = sheet.GetCols();
    int rows = sheet.GetRows();
    if( cols<=0 || rows<=0)
        return false;

    int row1 = sheet.GetStartRow("区间名称");
    int col1 = sheet.GetStartCol("区间名称");
    if(row1 == -1 || col1 == -1)
    {
        return false;
    }

    for(int row_i = row1 + 1; row_i < rows; row_i++)
    {
        QString fck_name;
        sheet.GetMergeCellStringValue(row_i, col1, fck_name);
        fck_name = fck_name.trimmed();

        if(!fck_name.isEmpty())
        {
            one_sta._FXK_names.append(QString::number(one_sta._sta_no) + "-" + fck_name);
        }
        else
        {
            break;
        }
    }

    if(one_sta._FXK_names.isEmpty())
    {
        return false;
    }
    return true;
}

void IFInfoTable::MergeFckName(QMap<int, OneStationIF> &mp_sta_info)
{
    int main_sta_no =CfgGenerator::ins()->station_no().toInt();

    if(!mp_sta_info.contains(main_sta_no))
    {
        return;
    }

    QVector<int> v_sorted_sta_no;
    v_sorted_sta_no.append(main_sta_no);
    v_sorted_sta_no.append(mp_sta_info[main_sta_no]._sub_sta_no);

    foreach (int var, v_sorted_sta_no)
    {
        m_v_FCX_names.append(mp_sta_info[var]._FXK_names);
    }

    if(m_v_FCX_names.size() > 32)
    {
        // erro log
        m_v_FCX_names.clear();
    }
    return;
}
