#include "CsmDigit.h"
#include <QChar>

CsmDigit::CsmDigit()
{

}

CsmDigit::~CsmDigit()
{

}

CsmDataDigit CsmDigit::CreateDigit(int plugin_id, const QString &name, int digit_type, int is_reverse, int is_valid, int show_mode, int cj_freq, int stat_meth)
{
    QVector<CsmDataDigit>& v_digit = m_plugin_digit[plugin_id];

    CsmDataDigit digit_unit;
    digit_unit._UUID        = QString("%1%2%3").arg(plugin_id, 8, 10, QChar('0')).arg(CsmData_Digit, 2, 10, QChar('0')).arg(v_digit.size()+1, 7, 10, QChar('0'));
    digit_unit._PluginID    = plugin_id;
    digit_unit._Name        = name;
    digit_unit._OrderNo     = v_digit.size();
    digit_unit._TypeID      = digit_type;
    digit_unit._IsReverse   = is_reverse;
    digit_unit._IsValid     = is_valid;
    digit_unit._ShowMode    = show_mode;
    digit_unit._CJFreq      = cj_freq;
    digit_unit._StatisicMeth= stat_meth;

    v_digit.push_back(digit_unit);

    return digit_unit;
}
