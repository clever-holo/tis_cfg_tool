#ifndef ECIDDEFINE_H
#define ECIDDEFINE_H

#include <QString>
#include <QVector>
#include "CsmDataDefine.h"
#include "CsmPlugin.h"
#include "CsmDigit.h"
#include "CsmEnum.h"

class BoardBase;

class ECID
{
public:
    ECID(int order);

public:
    bool AddBoard(BoardBase* board);
    void GenerateData();
    void GeneratePlugin();
    int Order() const;

    PluginInfo plugin_main() const;

    PluginInfo plugin_A() const;

    PluginInfo plugin_B() const;

private:
    void setOrder(int Order);

private:
    int m_Order;
    PluginInfo  m_plugin_main;
    PluginInfo  m_plugin_A;
    PluginInfo  m_plugin_B;

    QVector<BoardBase*>     m_lstBoard;
};



#endif // ECIDDEFINE_H
