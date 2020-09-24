#include "mainwindow.h"
#include <QApplication>
#include "TisCfgGenerator.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    QObject::connect(&w, MainWindow::sig_InputDirSelected,  CfgGenerator::ins(), CfgGenerator::slot_InputFileSelected);
    QObject::connect(&w, MainWindow::sig_OutputDirSelected, CfgGenerator::ins(), CfgGenerator::slot_OutputFileSelected);
    QObject::connect(&w, MainWindow::sig_DbmEdited,         CfgGenerator::ins(), CfgGenerator::slot_DbmEdited);
    QObject::connect(&w, MainWindow::sig_BeginGenerator,    CfgGenerator::ins(), CfgGenerator::slot_BeginGenerator);


    return a.exec();
}
