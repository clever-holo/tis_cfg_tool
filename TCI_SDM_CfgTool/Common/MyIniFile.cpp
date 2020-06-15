#include "MyIniFile.h"
#include <QDir>
#include <QRegularExpression>

MyIniFile::MyIniFile(const QString &file_name)
{
    QString filePath = file_name.left (file_name.lastIndexOf (QRegularExpression("[\\\\/]")));
    QDir tempDir;
    if(!tempDir.exists(filePath))
    {
       tempDir.mkpath(filePath);
    }
    m_file.setFileName(file_name);
}

MyIniFile::~MyIniFile()
{

}

bool MyIniFile::Open(QIODevice::OpenMode flags)
{
    return m_file.open(flags);
}

void MyIniFile::Close()
{
    m_file.close();
}

bool MyIniFile::WriteSec(const QString &sec_name)
{
    if(m_file.isWritable())
    {
        QString sec = "[" + sec_name + "]\r\n";
        m_file.write(sec.toLocal8Bit());
        return true;
    }
    return false;
}

bool MyIniFile::Write(const QString &key, const QString &value)
{
    if(m_file.isWritable())
    {
        QString str = key + "=" + value + "\r\n";
        m_file.write(str.toLocal8Bit());
        return true;
    }
    return false;
}

bool MyIniFile::WriteLine(const QString &content)
{
    if(m_file.isWritable())
    {
        QString str = content + "\r\n";
        m_file.write(str.toLocal8Bit());
        return true;
    }
    return false;
}
