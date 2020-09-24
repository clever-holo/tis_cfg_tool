#ifndef CFGGENERATOR_H
#define CFGGENERATOR_H

#include <qstring.h>
#include <QVector>
#include <QMap>

///
/// \brief 配置生成器：控制配置生成的主流程
///

#include <QObject>

class CfgGenerator : public QObject
{
    Q_OBJECT
private:
    CfgGenerator();
    static CfgGenerator* m_instance;

public:
    static CfgGenerator* ins();
    virtual ~CfgGenerator();


public:
    void GenerateCfg();

    QString inputPath() const;
    void setInputPath(const QString &inputPath);

    QString outputPath() const;
    void setOutputPath(const QString &outputPath);

    QString dbm() const;
    void setDbm(const QString &dbm);

    QString station_name() const;
    void setStation_name(const QString &station_name);

    QString station_no() const;
    void setStation_no(const QString &station_no);

    QVector<int> GetAllStationNo() const;
    QMap<int, QString> map_station_no2name() const {return m_map_station_no2name;}
    QMap<QString, int> map_station_name2no() const {return m_map_station_name2no;}

    QString codeXls()     const {return m_codeXls;}
    QString ip_internal() const {return m_ip_internal;}
    QString ip_external() const {return m_ip_external;}
    QVector<QString> Ads_files()        const {return m_ads_files;}
    QVector<QString> Vtl_files()        const {return m_vtl_files;}
    QVector<QString> dmis_files()       const {return m_dmis_files;}
    QVector<QString> block_files()      const {return m_block_files;}
    QVector<QString> tis_tis_files()    const {return m_tis_tis_files;}
    QVector<QString> tis_zpw_files()    const {return m_tis_zpw_files;}
    QVector<QString> qcalarm_files()    const {return m_qcalarm_files;}
    QVector<QString> if_info_files()    const {return m_if_info_files;}
    QVector<QString> ground_equ_files() const {return m_ground_equ_files;}



protected:
    void FindInputFileImpl(const QString &str_base_path, const QString &str_relative_path);
    void ParseFileType(const QString &str_relative_path, const QString &file_name);
    void ParseStationInfo();

public slots:
    void slot_InputFileSelected(const QString& inputPath);
    void slot_OutputFileSelected(const QString& OutputPath);
    void slot_DbmEdited(const QString& dbm);
    void slot_BeginGenerator();

private:
    QString m_inputPath;
    QString m_outputPath;
    QString m_dbm;
    QString m_station_name;         // 主站站号，从接口码位表读取
    QString m_station_no;           // 主站名称, 从接口码位表读取

    QString             m_ip_internal;       // 内部ip地址分配表
    QString             m_ip_external;       // 外部ip地址分配表
    QString             m_codeXls;           // 接口码位表
    QVector<QString>    m_ads_files;         // adsvar
    QVector<QString>    m_vtl_files;         // bool表达式
    QVector<QString>    m_dmis_files;        // dmis文件
    QVector<QString>    m_block_files;       // block文件，监测接口SA消息用
    QVector<QString>    m_ground_equ_files;  // 地面设备信息表，监测接口站间边界消息用（目前文件个数为1个）
    QVector<QString>    m_tis_tis_files;     // XXXTIS-TIS接口表.xls，监测接口站间边界消息用（目前文件个数为1个）
    QVector<QString>    m_tis_zpw_files;     // XXXTIS-轨道电路接口表.xls，监测接口站间边界消息用（目前文件个数为1个）
    QVector<QString>    m_if_info_files;     // 接口信息配置表XXX.xlsx, 接口信息配置表
    QVector<QString>    m_qcalarm_files;     // 驱采不一致报警配置，数据中的QCAlarm.CFG应重命名XXX_QCAlarm.CFG,XXX为站号

    QMap<int, QString>  m_map_station_no2name;
    QMap<QString, int>  m_map_station_name2no;
    QVector<int>        m_all_station_no;
    QVector<QString>    m_all_station_name;
};

#endif // CFGGENERATOR_H
