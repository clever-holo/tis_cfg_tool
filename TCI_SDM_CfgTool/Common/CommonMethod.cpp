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
