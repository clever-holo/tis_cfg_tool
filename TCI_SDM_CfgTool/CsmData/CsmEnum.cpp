#include "CsmEnum.h"
#include <QChar>

CsmEnum::CsmEnum()
{

}

CsmEnum::~CsmEnum()
{

}

CsmDataEnum CsmEnum::CreateEnum(int plugin_id, const QString &name, int enum_type, int is_valid, int cj_freq)
{
    QVector<CsmDataEnum>& v_enum = m_plugin_enum[plugin_id];

    CsmDataEnum enum_unit;
    enum_unit._UUID        = QString("%1%2%3").arg(plugin_id, 8, 10, QChar('0')).arg(CsmData_Enum, 2, 10, QChar('0')).arg(v_enum.size(), 7, 10, QChar('0'));
    enum_unit._PluginID    = plugin_id;
    enum_unit._Name        = name;
    enum_unit._OrderNo     = v_enum.size();
    enum_unit._TypeID      = enum_type;
    enum_unit._CJFreq      = cj_freq;
    enum_unit._IsValid     = is_valid;

    v_enum.push_back(enum_unit);

    return enum_unit;
}
