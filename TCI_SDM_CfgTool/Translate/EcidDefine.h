#ifndef ECIDDEFINE_H
#define ECIDDEFINE_H

#include <QString>
#include <QVector>
#include "CsmDataDefine.h"
#include "CsmPlugin.h"
#include "CsmDigit.h"
#include "CsmEnum.h"

class BoardBase;
class CsmDataDev;

class ECID
{
public:
    ECID(int order);

public:
    bool AddBoard(BoardBase* board);
    void GenerateData();
    int Order() const;

    PluginInfo plugin_main() const;
    PluginInfo plugin_A() const;
    PluginInfo plugin_B() const;

    const CsmDataDev *DevA() const;
    const CsmDataDev *DevB() const;

    const QVector<BoardBase *> GetAllBoard() const;

private:
    void setOrder(int Order);
    void GeneratePlugin();
    void GenerateDev();

private:
    int m_Order;
    PluginInfo  m_plugin_main;
    PluginInfo  m_plugin_A;
    PluginInfo  m_plugin_B;

    QVector<BoardBase*>     m_lstBoard;

    CsmDataDev*     m_ecid_dev_A;
    CsmDataDev*     m_ecid_dev_B;
};



#endif // ECIDDEFINE_H
