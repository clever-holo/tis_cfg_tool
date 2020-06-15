#include "CodeTable.h"
#include <cstddef>
#include <QMessageBox>
#include <TisCfgGenerator.h>



CodeTableCfg::CodeTableCfg()
{

}

void CodeTableCfg::LoadIFCodeTableCfg(const QString &inputFilePath)
{
    if(m_excelbook.readExcel(inputFilePath))
    {
       LoadInputAndOutput(m_excelbook);
       LoadBoard(m_excelbook);
    }
}

int CodeTableCfg::GetBoardCount() const
{
    return m_vBoardInfo.size();
}

const BoardInfo *CodeTableCfg::GetBoard(int index) const
{
    if(index < 0 || index >= GetBoardCount())
        return nullptr;
    return &m_vBoardInfo[index];
}

const QMap<QString, BoardInOut> &CodeTableCfg::GetInOut() const
{
    return m_mpBoardInOut;
}

bool CodeTableCfg::LoadInputAndOutput(const ExcelBook& book)
{
    ExcelSheet sheet;
    bool ret = book.GetSheet("ECID板卡码位映射", sheet);
    if(!ret)
        return false;

    int cols = sheet.GetCols();
    int rows = sheet.GetRows();
    if( cols<=0 || rows<=0)
        return false;

    int start_row = sheet.GetStartRow(libxl::CELLTYPE_STRING);
    int start_col = sheet.GetStartCol(libxl::CELLTYPE_STRING);

    if(start_row >= rows || start_col >= cols)
        return false;

    QString board_name = "";
    QString inout_name    = "";
    QString inout_type    = "";
    for(int col = start_col; col < cols; col++)
    {
       ret =  sheet.GetMergeCellStringValue(start_row, col, board_name);      // board name
       ret &= sheet.GetMergeCellStringValue(start_row + 1, col, inout_type);     // input or output
       if(ret)
       {
           // board name
           if(!m_mpBoardInOut.contains(board_name))
               m_mpBoardInOut.insert(board_name, BoardInOut());

           // input and outpit
           if(inout_type == "INPUT" || inout_type == "OUTPUT")
           {
               QVector<QString>& v_name = inout_type == "INPUT" ? m_mpBoardInOut[board_name]._input :  m_mpBoardInOut[board_name]._output;
               for(int row = start_row + 2; row < rows; row++)
               {
                   ret = sheet.GetCellStringValue(row, col, inout_name);
                   if(ret && !inout_name.isEmpty())
                   {
                       v_name.push_back(inout_name);
                   }
               }
           }
           else
           {
               m_mpBoardInOut.remove(board_name);
           }
       }
    }
    return true;
}

bool CodeTableCfg::LoadBoard(const ExcelBook &book)
{
    // find station sheet (which contains boards info)
    QVector<QString> sheetNames;
    book.GetSheetNames(sheetNames);

    QString staSheet = "";
    for(int i=0; i<sheetNames.size(); i++)
    {
        if( (sheetNames[i].contains("(") && sheetNames[i].contains(")"))
          ||(sheetNames[i].contains("（") && sheetNames[i].contains("）")))
        {
            staSheet = sheetNames[i];
        }
    }
    if(staSheet.isEmpty())
    {
        return false; // erro
    }
    m_sta_name = staSheet.section(QRegExp("[()（）]"), 0, 0);
    m_sta_no   = staSheet.section(QRegExp("[()（）]"), 1, 1);

    CfgGenerator::ins()->setStation_name(m_sta_name);
    CfgGenerator::ins()->setStation_no(m_sta_no);

    // load station sheet
    ExcelSheet sheet;
    bool ret = book.GetSheet(staSheet, sheet);
    if(!ret)
        return false;

    int start_col = sheet.GetStartCol("序号");
    QVector<int> rows = sheet.GetRowIndex(start_col, "序号");
    for(int i=0; i<rows.size(); i++)
    {
        int row_max = i == rows.size()-1 ? sheet.GetRows() : (rows[i+1] - 1);
        LoadBoardInOneRack(sheet, rows[i], start_col+1, row_max, sheet.GetCols(), m_vBoardInfo);
    }
    return true;
}


bool CodeTableCfg::LoadBoardInOneRack(const ExcelSheet& sheet, int row_min, int col_min, int row_max, int col_max, QVector<BoardInfo>& vBoardInfo)
{
    if(row_min < 0 || col_min < 0 || row_max > sheet.GetRows() || col_max > sheet.GetCols())
        return false;

    QString strBP;
    sheet.GetMergeCellStringValue(row_min - 1, col_min, strBP);
    QString curSlot = "";                                    // 当前槽道 (每个板卡占一个槽道)
    QMap<QString, QVector<QString>> curMapPort;              // 当前读到的端口
    for(int col = col_min; col < col_max; col++)
    {
        // 获取槽道信息
        QString slot = "";
        sheet.GetMergeCellStringValue(row_min, col, slot);
        if(slot != curSlot)
        {
           // 读到一个新板卡，将上一个板卡的信息储存
           if(!curSlot.isEmpty() && !curMapPort.isEmpty())
           {
               BoardInfo board_info;
               board_info._bp   = strBP;
               board_info._slot = curSlot;
               board_info._mpPort = curMapPort;
               vBoardInfo.push_back(board_info);
           }
           // 更新
            curSlot = slot;
            curMapPort.clear();
        }
        if(curSlot.isEmpty())
            continue;

        // 获取板卡名字（正常板卡只有1个名字，SIOM板卡有2个）
        QString board_name = "";
        sheet.GetMergeCellStringValue(row_min + 1, col, board_name);
        if(board_name.isEmpty())
            continue;

        if(curMapPort.count(board_name))
            continue;

        // 板卡每个端口采集的名称
        QVector<QString> vPort;
        QString port;
        for(int row = row_min + 2; row < row_max; row++)
        {
            sheet.GetMergeCellStringValue(row, col, port);
            vPort.push_back(port);
        }
        curMapPort.insert(board_name, vPort);
    }
    // 储存最后一个槽道
    if(!curSlot.isEmpty() && !curMapPort.isEmpty())
    {
        BoardInfo board_info;
        board_info._slot = curSlot;
        board_info._mpPort = curMapPort;
        vBoardInfo.push_back(board_info);
    }
    return true;
}

QString CodeTableCfg::sta_no() const
{
    return m_sta_no;
}

QString CodeTableCfg::sta_name() const
{
    return m_sta_name;
}
