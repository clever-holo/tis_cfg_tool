#ifndef PANELLAMPCFG_H
#define PANELLAMPCFG_H

#include <QMap>
#include <QString>
#include <QVector>


class PanelLampCfg
{
public:
    PanelLampCfg();

public:
    void LoadPanelLamp(const QString& inputFile);

    const QMap<QString, QVector<QString>>& GetPanelLamp() const;

private:
    QMap<QString, QVector<QString>>     m_panel_lamp;
};

#endif // PANELLAMPCFG_H
