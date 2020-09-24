#include "CommManager.h"
#include <QFile>
#include <QApplication>

CommManager::CommManager()
{

}

CommManager::~CommManager()
{

}

void CommManager::LoadHostCfg(const QString &file_path)
{
    QFile file(QApplication::applicationDirPath() + "/demo.xml");

    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        return;
    }
}
