#ifndef BLOCKCFG_H
#define BLOCKCFG_H

#include <QMap>
#include <QVector>
#include <QString>


struct BlockInfo
{
    QString     _block_name;
    QString     _verify_no;
};


class BlockCfg
{
public:
    BlockCfg();

public:
    void LoadCfg(const QString &inputFilePath);


    QMap<QString, QVector<BlockInfo> > mp_blockInfo() const;

private:
    QMap<QString, QVector<BlockInfo>>  m_mp_blockInfo;
};

#endif // BLOCKCFG_H
