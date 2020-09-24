#ifndef COMMHOST_H
#define COMMHOST_H


// 通信节点主机类型
enum CommHostType
{
    HostType_NULL = 0,
    HostType_IPS,
    HostType_SDM,
    HostType_MMI,
    HostType_OC,
    HostType_OC_LEU,
    HostType_RSSP1,		/// 外部RSSP1通信节点
    HostType_RESERVE,
};


// 通信节点主机
class CommHost
{
public:
    CommHost();
};



#endif // COMMHOST_H
