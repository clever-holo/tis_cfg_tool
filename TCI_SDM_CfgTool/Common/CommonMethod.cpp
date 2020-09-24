#include "CommonMethod.h"
#include <qfileinfo.h>
#include <QFile>
#include <QDir>
#include <QRegularExpression>

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

//拷贝文件：
bool CommonMethod::CopyFileToPath(const QString &sourceDir ,const QString &toDir, bool coverFileIfExist)
{
    QString toDirTemp = toDir;
    toDirTemp.replace("\\","/");
    if (sourceDir == toDirTemp){
        return true;
    }
    if (!QFile::exists(sourceDir)){
        return false;
    }
    QDir *createfile     = new QDir;
    bool exist = createfile->exists(toDirTemp);
    if (exist){
        if(coverFileIfExist){
            createfile->remove(toDirTemp);
        }
    }//end if

    // 如果上级路径不存在，则创建
    QString filePath = toDirTemp.left (toDirTemp.lastIndexOf (QRegularExpression("[\\\\/]")));
    QDir tempDir;
    if(!tempDir.exists(filePath))
    {
       tempDir.mkpath(filePath);
    }

    // copy
    if(!QFile::copy(sourceDir, toDirTemp))
    {
        return false;
    }
    return true;
}

//拷贝文件夹：
bool CommonMethod::CopyDirectoryFiles(const QString &fromDir, const QString &toDir, bool coverFileIfExist)
{
    QDir sourceDir(fromDir);
    QDir targetDir(toDir);
    if(!targetDir.exists()){    /**< 如果目标目录不存在，则进行创建 */
        if(!targetDir.mkdir(targetDir.absolutePath()))
            return false;
    }

    QFileInfoList fileInfoList = sourceDir.entryInfoList();
    foreach(QFileInfo fileInfo, fileInfoList){
        if(fileInfo.fileName() == "." || fileInfo.fileName() == "..")
            continue;

        if(fileInfo.isDir()){    /**< 当为目录时，递归的进行copy */
            if(!CopyDirectoryFiles(fileInfo.filePath(),
                targetDir.filePath(fileInfo.fileName()),
                coverFileIfExist))
                return false;
        }
        else{            /**< 当允许覆盖操作时，将旧文件进行删除操作 */
            if(coverFileIfExist && targetDir.exists(fileInfo.fileName())){
                targetDir.remove(fileInfo.fileName());
            }

            /// 进行文件copy
            if(!QFile::copy(fileInfo.filePath(),
                targetDir.filePath(fileInfo.fileName()))){
                    return false;
            }
        }
    }
    return true;
}
