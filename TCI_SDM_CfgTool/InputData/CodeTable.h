#ifndef EXCELMANAGER_H
#define EXCELMANAGER_H

#include "ExcelWrapper.h"
#include <QVector>
#include <QMap>

enum BOARD_TYPE
{
    BOARD_TYPE_UNKNOWN,

};

struct BoardInOut
{
    QVector<QString>    _input;
    QVector<QString>    _output;
};

struct BoardInfo
{
    QString _bp;
    QString _slot;
    QMap<QString, QVector<QString>> _mpPort;
};

// 读取并储存码表信息
class CodeTableCfg
{
public:
    CodeTableCfg();
    void LoadIFCodeTableCfg(const QString& inputFilePath);
    int  GetBoardCount() const;
    const BoardInfo* GetBoard(int index) const;
    const  QMap<QString, BoardInOut>& GetInOut() const;

private:
    bool LoadInputAndOutput(const ExcelBook &book);
    bool LoadBoard(const ExcelBook& book);
    bool LoadBoardInOneRack(const ExcelSheet &sheet, int row_min, int col_min, int row_max, int col_max, QVector<BoardInfo>& vBoardInfo);

private:
    ExcelBook m_excelbook;

    QMap<QString, BoardInOut> m_mpBoardInOut;
    QVector<BoardInfo>        m_vBoardInfo;
};

#endif // EXCELMANAGER_H
