#ifndef MYINIFILE_H
#define MYINIFILE_H
#include <QFile>
#include <QString>

class MyIniFile
{
public:
    MyIniFile(const QString& file_name);
    ~MyIniFile();

public:
    bool Open(QIODevice::OpenMode flags);
    void Close();
    bool WriteSec(const QString& sec_name);
    bool Write(const QString& key, const QString& value);
    bool WriteLine(const QString& content = "");

private:
    QFile      m_file;

};

#endif // MYINIFILE_H
