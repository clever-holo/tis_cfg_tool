#ifndef COMMMANAGER_H
#define COMMMANAGER_H

#include <QVector>
#include "CommHost.h"
#include "Singleton.h"

class CommManager
{
public:
    CommManager();
    ~CommManager();

    friend class Singleton<CommManager>;

public:
    void LoadHostCfg(const QString& file_path);

protected:
    QVector<CommHost*> m_CommHost;


};

#endif // COMMMANAGER_H
