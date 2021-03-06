#-------------------------------------------------
#
# Project created by QtCreator 2020-04-03T16:16:01
#
#-------------------------------------------------

QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TCI_SDM_CfgTool
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# Enable libxl library [Li Shaoxian 2019-10-29]
INCLUDEPATH += ./libxl/include_cpp/
INCLUDEPATH += ./InputData/
INCLUDEPATH += ./CsmData/
INCLUDEPATH += ./Common/
INCLUDEPATH += ./Translate/
INCLUDEPATH += ./Comm/
INCLUDEPATH += ./CsmIF/

LIBS += -L$$PWD/libxl/lib/ -llibxl


CONFIG(release, debug|release){
    DLLDESTDIR += $$PWD/../Publish/$$TARGET/Bin/
} else {
    DLLDESTDIR += $$PWD/../Publish/$$TARGET/BinD/
}

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    TisCfgGenerator.cpp \
    TisCfgData.cpp \
    InputData/CodeTable.cpp \
    InputData/AdsVarCfg.cpp \
    BoardFactory.cpp \
    CsmData/CsmDataManager.cpp \
    Common/CommonMethod.cpp \
    Translate/EcidManager.cpp \
    Common/ExcelWrapper.cpp \
    Translate/BoardDefine.cpp \
    Translate/EcidDefine.cpp \
    CsmData/CsmDigit.cpp \
    CsmData/CsmEnum.cpp \
    CsmData/CsmAnalog.cpp \
    CsmData/CsmCurve.cpp \
    CsmData/CsmPlugin.cpp \
    Translate/IpsManager.cpp \
    Common/MyIniFile.cpp \
    InputData/PanelLampcfg.cpp \
    CsmData/CsmVirtualStatus.cpp \
    CsmData/CsmDevice.cpp \
    CsmData/CsmCBISpecial.cpp \
    CsmData/CsmEcidHdw.cpp \
    CsmData/CsmUserModi.cpp \
    CsmData/CsmOtherFile.cpp \
    InputData/IPTable.cpp \
    InputData/BlockCfg.cpp \
    InputData/GroundEquipmentTable.cpp \
    InputData/TisTisTable.cpp \
    InputData/TisZpwTable.cpp \
    InputData/IFInfoTable.cpp \
    CsmIF/CsmIFCfg.cpp \
    CsmIF/CsmIF_StationInfo.cpp


HEADERS += \
        mainwindow.h \
    TisCfgGenerator.h \
    TisCfgData.h \
    InputData/CodeTable.h \
    InputData/AdsVarCfg.h \
    BoardFactory.h \
    CsmData/CsmDataManager.h \
    Common/CommonMethod.h \
    Translate/EcidManager.h \
    Common/ExcelWrapper.h \
    Translate/BoardDefine.h \
    Translate/EcidDefine.h \
    Common/Singleton.h \
    CsmData/CsmDigit.h \
    CsmData/CsmEnum.h \
    CsmData/CsmAnalog.h \
    CsmData/CsmCurve.h \
    CsmData/CsmPlugin.h \
    CsmData/CsmDataDefine.h \
    Translate/IpsManager.h \
    Common/MyIniFile.h \
    InputData/PanelLampCfg.h \
    CsmData/CsmVirtualStatus.h \
    CsmData/CsmDevice.h \
    CsmData/CsmCBISpecial.h \
    CsmData/CsmEcidHdw.h \
    CsmData/CsmUserModi.h \
    CsmData/CsmOtherFile.h \
    InputData/IPTable.h \
    InputData/BlockCfg.h \
    InputData/GroundEquipmentTable.h \
    InputData/TisTisTable.h \
    InputData/TisZpwTable.h \
    InputData/IFInfoTable.h \
    CsmIF/CsmIFCfg.h \
    CsmIF/CsmIF_StationInfo.h



FORMS += \
        mainwindow.ui
