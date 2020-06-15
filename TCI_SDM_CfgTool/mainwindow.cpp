#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <qstring.h>
#include <qfiledialog.h>
#include "TisCfgGenerator.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->LE_Input->setReadOnly(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

/// 点击生成按钮
void MainWindow::on_BTN_Generate_clicked()
{
    CfgGenerator::ins()->setDbm(ui->LE_DBM->text());
    CfgGenerator::ins()->GenerateCfg();
}

/// 设置输入文件夹
void MainWindow::on_Btn_Input_clicked()
{
   QString inputDirPath = QFileDialog::getExistingDirectory(
               this, "choose input directory", "/");

    if (inputDirPath.isEmpty())
    {
        return;
    }
    else {
        ui->LE_Input->setText(inputDirPath);
        ui->LE_Input->setToolTip(inputDirPath);
        ui->LE_Input->setCursorPosition(0);
        CfgGenerator::ins()->setInputPath(inputDirPath);
    }
}

/// 设置输出文件夹
void MainWindow::on_Btn_Output_clicked()
{
    QString outputDirPath = QFileDialog::getExistingDirectory(
                this, "choose output directory", "/");

     if (outputDirPath.isEmpty())
     {
         return;
     }
     else {
         ui->LE_Output->setText(outputDirPath);
         ui->LE_Output->setToolTip(outputDirPath);
         ui->LE_Output->setCursorPosition(0);
         CfgGenerator::ins()->setOutputPath(outputDirPath);
     }
}
