#include "BlockCfg.h"
#include <QFile>
#include <QTextStream>
#include <QRegularExpressionMatchIterator>
#include "TisCfgGenerator.h"



BlockCfg::BlockCfg()
{

}

void BlockCfg::LoadCfg(const QString &inputFilePath)
{
    QVector<QString> v_block = CfgGenerator::ins()->block_files();

    foreach (QString ele, v_block)
    {
        QString file_path = inputFilePath + "\\" + ele;

        QFile file(file_path);
        if(file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QTextStream in_stream(&file);
            in_stream.seek(file.size());//将当前读取文件指针移动到文件末尾
            in_stream.seek(0);//将当前读取文件指针移动到文件开始

            QString sta_name_en = ele.left (ele.indexOf("."));

            QRegularExpression rx("^\\s*\\d+\\s+(\\S+)\\s+0x(\\S+)\\s+\\S+");
            QRegularExpressionMatchIterator reg_it;

            while(!in_stream.atEnd())
            {
                QString line = in_stream.readLine();
                line = line.replace(QRegExp("[\\r\\n]"), "");

                reg_it = rx.globalMatch(line);
                if(reg_it.hasNext())
                {
                    QRegularExpressionMatch mat = reg_it.next();

                    BlockInfo block_info;
                    block_info._block_name = mat.captured(1);
                    block_info._verify_no  = mat.captured(2);
                    m_mp_blockInfo[sta_name_en].push_back(block_info);
                }
            }
        }
    }
}

QMap<QString, QVector<BlockInfo> > BlockCfg::mp_blockInfo() const
{
    return m_mp_blockInfo;
}
