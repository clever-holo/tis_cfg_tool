#include "EcidManager.h"
#include "BoardFactory.h"

EcidManager::EcidManager()
{

}

EcidManager::~EcidManager()
{

}

void EcidManager::LoadEcidInfo(const CodeTableCfg *pCodeTable)
{
    if(pCodeTable == nullptr)
        return;

    int board_count = pCodeTable->GetBoardCount();
    for(int i=0; i<board_count; i++)
    {
        const BoardInfo* pBoardInfo = pCodeTable->GetBoard(i);
        if(pBoardInfo != nullptr)
        {            
            BoardBase* pBoardbase = BoardFactory::CreateBoard(pBoardInfo);
            AddBoard(pBoardbase);
        }
    }
}

ECID *EcidManager::GetEcid(int ecid_order)
{
    for(int i=0; i<m_lstECID.size(); i++)
    {
        if(m_lstECID[i]->Order() == ecid_order)
            return m_lstECID[i];
    }
    return nullptr;
}

//
void EcidManager::GenerateData()
{
    // 每个Ecid生成Data
    foreach (ECID* pEcid, m_lstECID) {
        pEcid->GenerateData();
    }
}

int EcidManager::GetEcidCount()
{
    return m_lstECID.size();
}

void EcidManager::AddBoard(BoardBase *ptr_board)
{
    ECID* pEcid = GetEcid(ptr_board->EcidOrder());
    if(pEcid == nullptr)
        pEcid = AddEcid(ptr_board->EcidOrder());

    pEcid->AddBoard(ptr_board);
}

ECID *EcidManager::AddEcid(int ecid_order)
{
    ECID* pecid = new ECID(ecid_order);
    m_lstECID.push_back(pecid);
    return pecid;
}
