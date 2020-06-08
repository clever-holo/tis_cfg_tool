#ifndef ECIDMANAGER_H
#define ECIDMANAGER_H

#include "Singleton.h"
#include "EcidDefine.h"
#include "CodeTable.h"


class EcidManager
{
protected:
    EcidManager();
    ~EcidManager();
    friend class Singleton<EcidManager>;

public:
    void LoadEcidInfo(const CodeTableCfg* pCodeTable);
    ECID* GetEcid(int ecid_order);
    void GenerateData();

protected:
    void AddBoard(BoardBase* ptr_board);
    ECID* AddEcid(int ecid_order);
private:
    QVector<ECID*> m_lstECID;
};

#endif // ECIDMANAGER_H
