#include "PanelLampCfg.h"
#include <QSettings>

PanelLampCfg::PanelLampCfg()
{

}

void PanelLampCfg::LoadPanelLamp(const QString &inputFile)
{
    QSettings setting(inputFile, QSettings::IniFormat);

    QStringList all = setting.childGroups();

    foreach (const QString & sec, all) {

        setting.beginGroup(sec);

        int max = setting.value("MAX").toInt();
        for(int i=0; i<max; i++)
        {
            QString val = setting.value(QString::number(i+1)).toString().trimmed();
            if(!val.isEmpty())
                m_panel_lamp[sec].push_back(val);
        }
        setting.endGroup();
    }
}

const QMap<QString, QVector<QString> > &PanelLampCfg::GetPanelLamp() const
{
    return m_panel_lamp;
}
