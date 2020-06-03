#include "MyIniFile.h"


MyIniFile::MyIniFile(const QString &file_name)
{
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
    QString str = key + "=" + value + "\r\n";
    m_file.write(str.toLocal8Bit());
    return false;
}