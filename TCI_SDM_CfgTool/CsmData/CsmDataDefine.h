#ifndef CSMDATADEFINE_H
#define CSMDATADEFINE_H

#include <QString>

enum CsmDataType
{
    CsmData_Invalid = -1,
    CsmData_Digit   = 0,        // 开关量
    CsmData_Analog,             // 模拟量
    CsmData_Curve,              // 曲线
    CsmData_String,             // 字符串
    CsmData_Enum,               // 枚举
    CsmData_Blob,               // 二进制
    CsmData_Test,               // 测试量
    CsmData_Virtual_Enum,       // 虚拟枚举
    CsmData_Struct,             // 结构型
    CsmData_Counter,            // 计数量
    CsmData_Proc_Calculation,   // 过程计算量
    CsmData_Proc_Statistic,     // 过程统计量
    CsmData_Virtual_Status,     // 虚拟状态量
};

enum CsmCJXStatus
{
    CsmCJX_UnExisted = -1,
    CsmCJX_InValid  =  0,   // 无效
    CsmCJX_Valid    =  1,   //有效
};

struct CsmDataDigit
{
    int				_PluginID;			//接口ID
    QString         _UUID;
    QString         _Name;
    int				_OrderNo;			//存储路数
    int				_TypeID;			//数据类型ID
    int             _IsReverse;
    int             _IsValid;
    int             _ShowMode;
    int             _CJFreq;
    int             _StatisicMeth;
};

struct CsmDataEnum
{
    int				_PluginID;			//接口ID
    QString         _UUID;
    QString         _Name;
    int				_OrderNo;			//存储路数
    int				_TypeID;			//数据类型ID
    int             _IsValid;
    int             _CJFreq;
};

struct CsmDataAnalog
{
    int				_TypeID;			 //模拟量类型
    int				_PluginID;			 //接口ID
    QString         _UUID;               //UUID
    QString         _Name;               //name
    int				_OrderNo;			 //存储路数
    int             _Ratio;              //倍率
    QString         _Unit;               //单位
    int             _CJFreq;             //采集频率
    int             _DelayQueueLength;   //延迟队列长度
    QString         _FilterTimeParam;    //过滤时间参数
    int             _IsValid;            //是否有效
};

struct CsmDataCurve
{
    int				_TypeID;			 //模拟量类型
    int				_PluginID;			 //接口ID
    QString         _UUID;               //UUID
    QString         _Name;               //name
    int				_OrderNo;			 //存储路数
    int             _Ratio;              //倍率
    QString         _Unit;               //单位
    int             _CJFreq;             //采集频率
    int             _Address;            //地址号
    int             _IsValid;            //是否有效
};

#endif // CSMDATADEFINE_H
