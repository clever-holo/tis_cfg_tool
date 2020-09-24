#include "ExcelWrapper.h"
#include <QDebug>
#include <QVector>

ExcelBook::ExcelBook()
{
    m_book = NULL;
    m_bLoad = false;
}

bool ExcelBook::readExcel(const QString &filePath)
{
    if(m_book != NULL)
    {
        m_book->release();
        m_book = NULL;
    }

    if(filePath.endsWith("xls",Qt::CaseInsensitive))//判断是否是.xls文件，不区分大小写
    {
        m_book = xlCreateBook();
    }
    else if(filePath.endsWith("xlsx",Qt::CaseInsensitive))//判断是否是.xlsx文件，不区分大小写
    {
        m_book = xlCreateXMLBook();
    }

    //加载excel文件，toLocal8Bit是为了支持中文命名的文件
    if(m_book && m_book->load(filePath.toLocal8Bit()))
    {
        m_bLoad = true;
    }
    else
    {
        // 弹窗提示
        m_bLoad = false;
    }

    return m_bLoad;
}

// 根据标签寻找表
 bool ExcelBook::GetSheet(QString sheetName, ExcelSheet& outSheet) const
{
   int sheetCount = m_book->sheetCount();
   for (int i = 0; i < sheetCount; ++i)
   {
       libxl::Sheet* curSheet = m_book->getSheet(i);
       if (curSheet && sheetName == QString::fromLocal8Bit(curSheet->name()).trimmed())
       {
           outSheet.SetSheet(curSheet);
           return true;
       }
   }
   return false;
}

//
bool ExcelBook::GetSheetNames(QVector<QString>& sheetNames) const
{
    int sheetCount = m_book->sheetCount();
    for (int i = 0; i < sheetCount; ++i)
    {
        libxl::Sheet* curSheet = m_book->getSheet(i);
        if (curSheet)
        {
            sheetNames.push_back(QString::fromLocal8Bit(curSheet->name()).trimmed());
        }
    }
    return true;
}


//////////////////////////////////////////////////////////////////////
///                          ExcelSheet                            ///
//////////////////////////////////////////////////////////////////////

ExcelSheet::ExcelSheet()
{
    m_sheet = NULL;
}

void ExcelSheet::SetSheet(libxl::Sheet* sheet)
{
    m_sheet = sheet;
}

// 获取行数
int  ExcelSheet::GetRows() const
{
    return m_sheet ? m_sheet->lastRow() : 0;
}

// 获取列数
int  ExcelSheet::GetCols() const
{
    return m_sheet ? m_sheet->lastCol() : 0;
}

// 获取出现某类数据的最小列
int ExcelSheet::GetStartCol(libxl::CellType cellType) const
{
    if(m_sheet)
    {
        for(int col = 0; col < GetCols(); col++)
        {
            for(int row = 0; row < GetRows(); row++)
            {
                if(cellType == GetCellType(row, col))
                    return col;
            }
        }
    }
    return -1;
}

int ExcelSheet::GetStartRow(libxl::CellType cellType) const
{
    if(m_sheet)
    {
        for(int row = 0; row < GetRows(); row++)
        {
            for(int col = 0; col < GetCols(); col++)
            {
                if(cellType == GetCellType(row, col))
                    return row;
            }
        }
    }
    return -1;
}

// 出现target的最小列
int ExcelSheet::GetStartCol(const QString& target) const
{
    if(m_sheet)
    {
        QString cellVal;
        for(int col = 0; col < GetCols(); col++)
        {
            for(int row = 0; row < GetRows(); row++)
            {
                GetCellStringValue(row, col, cellVal);
                if(target == cellVal)
                    return col;
            }
        }
    }
    return -1;
}

// 出现target的最小行
int ExcelSheet::GetStartRow(const QString &target) const
{
    if(m_sheet)
    {
        QString cellVal;
        for(int col = 0; col < GetCols(); col++)
        {
            for(int row = 0; row < GetRows(); row++)
            {
                GetCellStringValue(row, col, cellVal);
                if(target == cellVal)
                    return row;
            }
        }
    }
    return -1;
}


QVector<int> ExcelSheet::GetRowIndex(int col, const QString& target) const
{
    QVector<int> vRs;
    if(m_sheet && col>=0 && col<GetCols())
    {
        QString cellVal;
        for(int row = 0; row < GetRows(); row++)
        {
            GetCellStringValue(row, col, cellVal);
            if(target == cellVal)
            {
                vRs.push_back(row);
            }
        }
    }
    return vRs;
}


// 获取单元格数据类型
libxl::CellType ExcelSheet::GetCellType(int row,int col) const
{
    return m_sheet ? m_sheet->cellType(row, col) : libxl::CELLTYPE_ERROR;
}

// 获取合并单元格中的字符串
// 对于合并区域，只有左上角有值，其它为空白
bool ExcelSheet::GetMergeCellStringValue(int row, int col, QString& outValue) const
{

    if(m_sheet)
    {
        int rowFirst, rowLast, colFirst, colLast;
        if(m_sheet->getMerge(row, col, &rowFirst, &rowLast, &colFirst, &colLast))
        {
            return GetCellStringValue(rowFirst, colFirst, outValue);        // 合并单元格要读取左上角的单元格的值
        }
        return GetCellStringValue(row, col, outValue);
    }
    return false;
}

// 获取字符串
bool ExcelSheet::GetCellStringValue(int row, int col, QString& outValue) const
{
    outValue.clear();
    if(m_sheet)
    {
        libxl::CellType cellType = m_sheet->cellType(row, col);
        if(cellType == libxl::CELLTYPE_STRING)
        {
           outValue = QString::fromLocal8Bit(m_sheet->readStr(row, col)).trimmed().replace("\r", "").replace("\n", "");
           return true;
        }
        else if(cellType == libxl::CELLTYPE_NUMBER)
        {
           outValue = QString::number(m_sheet->readNum(row, col));
           return true;
        }
    }
    return false;
}

// 获取浮点数
bool ExcelSheet::GetCellNumberValue(int row, int col, double& outValue) const
{
    if(m_sheet)
    {
        libxl::CellType cellType = m_sheet->cellType(row, col);
        if(cellType == libxl::CELLTYPE_STRING)
        {
           outValue = QString::fromLocal8Bit(m_sheet->readStr(row, col)).trimmed().toDouble();
           return true;
        }
        else if(cellType == libxl::CELLTYPE_NUMBER)
        {
           outValue = m_sheet->readNum(row, col);
           return true;
        }
    }

    return false;
}

// 获取整数
bool ExcelSheet::GetCellNumberValue(int row, int col, int& outValue) const
{
    if(m_sheet)
    {
        libxl::CellType cellType = m_sheet->cellType(row, col);
        if(cellType == libxl::CELLTYPE_STRING)
        {
           outValue = QString::fromLocal8Bit(m_sheet->readStr(row, col)).trimmed().toInt();
           return true;
        }
        else if(cellType == libxl::CELLTYPE_NUMBER)
        {
           outValue = (int) m_sheet->readNum(row, col);
           return true;
        }
    }

    return false;
}
