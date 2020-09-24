#include "IPTable.h"
#include "TisCfgGenerator.h"


// ////////////////////////////////////////////////
NetHost *NetHost::CreatenetHost(NetHostType type, const QString& host_name)
{
    NetHost* host = NULL;
    switch (type) {
    case HostType_SDM:
        host = new SdmHost();
        break;
    case HostType_IPS:
        host = new IpsHost();
        break;
    case HostType_MMI:
        host = new MmiHost();
        break;
    case HostType_OC:
        host = new OcHost();
        break;
    case HostType_OC_LEU:
        host = new OcLeuHost();
        break;
    case HostType_RSSP1:
        host = new Rssp1Host();
        break;
    default:
        host = NULL;
        break;
    }

    if(host)
    {
        host->setHost_name(host_name);
    }

    return host;
}

NetHostType NetHost::ParseHostType(const QString &host_name)
{
    if      (host_name.contains("IPS"))        return HostType_IPS;
    else if (host_name.contains("SDM"))        return HostType_SDM;
    else if (host_name.contains("MMI"))        return HostType_MMI;
    else if (host_name.contains("OC"))         return HostType_OC;
    else if (host_name.contains("OC-LEU"))     return HostType_OC_LEU;
    else if (!host_name.isEmpty())             return HostType_RSSP1;
    else                                       return HostType_NULL;
}

QString NetHost::host_name() const
{
    return m_host_name;
}

void NetHost::setHost_name(const QString &host_name)
{
    m_host_name = host_name;
}


// ////////////////////////////////////////////////
IPTable::IPTable()
{

}

void IPTable::LoadCfg(const QString &inputFilePath)
{
    LoadInternal(inputFilePath);
    LoadExternal(inputFilePath);
}

void IPTable::LoadInternal(const QString &inputFilePath)
{
    QString xls = inputFilePath + "\\" + CfgGenerator::ins()->ip_internal();

    if(m_excelbook.readExcel(xls))
    {
        ExcelSheet sheet;
        if(m_excelbook.GetSheet("IPS-200-SDM", sheet))
            LoadOneSheet(sheet);

        if(m_excelbook.GetSheet("IPS-200-MMI", sheet))
            LoadOneSheet(sheet);

        if(m_excelbook.GetSheet("IPS-200-OC", sheet))
            LoadOneSheet(sheet);

        if(m_excelbook.GetSheet("OC-SDM", sheet))
            LoadOneSheet(sheet);

        if(m_excelbook.GetSheet("IPS-200-OC-LEU", sheet))
            LoadOneSheet(sheet);

    }
}

void IPTable::LoadExternal(const QString &inputFilePath)
{

}

void IPTable::LoadOneSheet(const ExcelSheet &sheet)
{
    int cols = sheet.GetCols();
    int rows = sheet.GetRows();
    if( cols<=0 || rows<=0)
        return;

    int start_col = sheet.GetStartCol("设备名称");
    if(start_col == -1)
        return;

    QVector<int> all_row = sheet.GetRowIndex(start_col, "设备名称");
    int start_row = all_row[0] + 1;

    for(int i = start_row; i < rows; i++)
    {
        QString host_name = "";
        sheet.GetMergeCellStringValue(i, start_col, host_name);
        Addhost(host_name);
    }
}

void IPTable::Addhost(const QString &host_name)
{
    foreach (NetHost* ele, m_net_hosts) {
        if(ele->host_name() == host_name)
            return;
    }

    NetHostType host_type = NetHost::ParseHostType(host_name);
    NetHost* net_host = NetHost::CreatenetHost(host_type, host_name);

    if(net_host)
    {
        m_net_hosts.push_back(net_host);
    }


}



