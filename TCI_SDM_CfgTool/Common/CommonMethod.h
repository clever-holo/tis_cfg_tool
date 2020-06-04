#ifndef COMMONMETHOD_H
#define COMMONMETHOD_H

#include <qstring.h>

class CommonMethod
{
public:
    CommonMethod();

    /// 判断file/dictionary是否存在
    static bool IsFileExist(const QString& fullPath);

    ///
    static int ChineseNumber(const QString& str);
};

#endif // COMMONMETHOD_H
