#ifndef EXCELBOOK_H
#define EXCELBOOK_H

#include <QString>
#include "libxl.h"


class ExcelSheet;

///
/// \brief The ExcelBook class
///
class ExcelBook
{
public:
    ExcelBook();
    ~ExcelBook(){}
public:

    bool readExcel(const QString &filePath);

    // 根据标签寻找表
    bool GetSheet(QString sheetName, ExcelSheet& outSheet) const;

    //
    bool GetSheetNames(QVector<QString>& sheetNames) const;

private:
    libxl::Book* m_book;
    bool         m_bLoad;
};



///
/// \brief The ExcelSheet class
///
class ExcelSheet
{
public:
    ExcelSheet();

public:

    void SetSheet(libxl::Sheet* sheet);

    int  GetRows() const;
    int  GetCols() const;

    libxl::CellType GetCellType(int row,int col) const;

    int  GetStartCol(libxl::CellType cellType) const;
    int  GetStartRow(libxl::CellType cellType) const;

    int  GetStartCol(const QString& target) const;

    QVector<int> GetRowIndex(int col, const QString& target) const;

    bool GetMergeCellStringValue(int row, int col, QString& outValue) const;
    bool GetCellStringValue(int row, int col, QString& outValue)const;
    bool GetCellNumberValue(int row, int col, double& outValue) const;
    bool GetCellNumberValue(int row, int col, int& outValue) const;

private:
    libxl::Sheet* m_sheet;

};

#endif // EXCELBOOK_H
