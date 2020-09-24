#ifndef COMMONMETHOD_H
#define COMMONMETHOD_H

#include <qstring.h>

class CommonMethod
{
public:
    CommonMethod();

    /// 判断file/dictionary是否存在
    static bool IsFileExist(const QString& fullPath);

    /// 判断字符串中汉字个数
    static int ChineseNumber(const QString& str);

    /// 拷贝文件
    static bool CopyFileToPath(const QString &sourceDir ,const QString &toDir, bool coverFileIfExist);

    /// 拷贝文件夹
    static bool CopyDirectoryFiles(const QString &fromDir, const QString &toDir, bool coverFileIfExist);
};

#endif // COMMONMETHOD_H
