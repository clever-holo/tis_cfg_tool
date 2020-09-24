#include "CsmIFCfg.h"


CsmIFCfg* CsmIFCfg::m_instance = nullptr;

CsmIFCfg::CsmIFCfg()
{

}

CsmIFCfg* CsmIFCfg::ins()
{
    if(m_instance == nullptr)
        m_instance = new CsmIFCfg();
    return m_instance;
}

CsmIFCfg::~CsmIFCfg()
{

}

void CsmIFCfg::GenerateCsmIF(const QString &str_output_path)
{
    m_output_path = str_output_path + "\\CsmIF\\";
    
    // 
    WriteStationInfo_StationCode();
}

void CsmIFCfg::WriteStationInfo_StationCode()
{
    m_sta_info.OutPutFile(m_output_path);
}
