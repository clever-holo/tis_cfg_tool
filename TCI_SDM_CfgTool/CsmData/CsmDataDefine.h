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

enum CsmDevType
{
    CsmDev_Unknow           = 0,

    CsmDev_TIS_SYS          = 1,
    CsmDev_TIS_AB           = 2,

    CsmDev_OC_OC            = 101,
    CsmDev_OC_VIIB          = 102,
    CsmDev_OC_VOOB          = 103,
    CsmDev_OC_SDDM          = 104,
    CsmDev_OC_PDDM46        = 105,
    CsmDev_OC_TCIM25        = 106,
    CsmDev_OC_PDDM5         = 107,
    CsmDev_OC_CDDM          = 108,
    CsmDev_OC_SIOM          = 109,
    CsmDev_OC_HIOM          = 110,
    CsmDev_OC_EIOCOM        = 111,

    CsmDev_Track            = 201,      // 轨道区段

    CsmDev_DC_Switch        = 301,      // 直流转辙机
    CsmDev_AC_Switch        = 302,      // 交流转辙机
    CsmDev_NonStd_ACSwitch  = 303,      // 非标交流转辙机

    CsmDev_Signal           = 401,      // 信号机

    CsnDev_Scattered        = 501,      // 零散设备
};


enum CsmAnalogtype
{
    E_SDDM_ANALOG_DSDL = 0, // 灯丝电流模拟量类型
    E_PDDM4_ANALOG_BSDYDY = 20, // 表示电源电压
    E_PDDM4_ANALOG_BSDL = 21,   // 表示电流
    E_TCIM_ANALOG_JBXHDY = 23,   // 局部信号电压
    E_TCIM_ANALOG_GDDY   = 22,   // 轨道电压
    E_TCIM_ANALOG_GDXWJ  = 24,   // 轨道相位角
    E_PDDM5_ANALOG_SBO_VOLT_C = 27, // C相驱动电压
    E_PDDM5_ANALOG_SBO_VOLT_B = 26, // B相驱动电压
    E_PDDM5_ANALOG_SBO_VOLT_A = 25, // A相驱动电压
    E_PDDM5_ANALOG_EXP_VOLT   = 28, // 表示电压
    E_PDDM5_ANALOG_SBO_FN_DL  = 29, // 反表内部回路电流
    E_PDDM5_ANALOG_SBO_FW_DL  = 30, // 反表外部回路电流
    E_PDDM5_ANALOG_SBO_DN_DL  = 31, // 定表内部回路电流
    E_PDDM5_ANALOG_SBO_DW_DL  = 32, // 定表外部回路电流
    E_SIOM_ANALOG_DI_SBO_VOLT     = 33,  // 驱动/采集电压
    E_SIOM_ANALOG_SELF_CHECK_VOLT = 34,  // 自检电源电压
    E_HIOM_ANALOG_DB_PORT_VOLT   = 35,  // 定表端口采集电压
    E_HIOM_ANALOG_FB_PORT_VOLT   = 36,  // 反表端口采集电压
    E_HIOM_ANALOG_SYB_PORT_VOLT  = 37,  // 手摇把端口采集电压
};

enum CsmCurveType
{
    E_PDDM4_CURVE_DIRECT_CURR = 0,  // 道岔动作电流曲线(直流)
    E_PDDM5_CURVE_CURR_C  = 3,       // 道岔动作C相电流曲线
    E_PDDM5_CURVE_PHASE_C = 6,       // 道岔动作C相相位曲线
    E_PDDM5_CURVE_CURR_B  = 2,       // 道岔动作B相电流曲线
    E_PDDM5_CURVE_PHASE_B = 5,       // 道岔动作B相相位曲线
    E_PDDM5_CURVE_CURR_A  = 1,       // 道岔动作A相电流曲线
    E_PDDM5_CURVE_PHASE_A = 4,       // 道岔动作A相相位曲线
    E_HIOM_CURVE_CURR_A  = 1,       // 道岔动作A相电流曲线
    E_HIOM_CURVE_CURR_B  = 2,       // 道岔动作B相电流曲线
    E_HIOM_CURVE_CURR_C  = 3,       // 道岔动作C相电流曲线
};

enum CsmCJXStatus
{
    CsmCJX_UnExisted = -1,
    CsmCJX_InValid   =  0,   // 无效
    CsmCJX_Valid     =  1,   // 有效
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
