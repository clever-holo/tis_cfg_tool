#include "CommonMethod.h"
#include <qfileinfo.h>

CommonMethod::CommonMethod()
{

}

bool CommonMethod::IsFileExist(const QString &fullPath)
{
    QFileInfo fileInfo(fullPath);
    return fileInfo.exists();
}

int CommonMethod::ChineseNumber(const QString &str)
{
    int cnt = 0;
    foreach(QChar ch, str)
    {
        if (ch.unicode()>0x7F)
            cnt++;
    }
    return cnt;
}
