#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_BTN_Generate_clicked();

    void on_Btn_Input_clicked();

    void on_Btn_Output_clicked();

    void on_LE_DBM_textChanged(const QString &arg1);

signals:
    void sig_InputDirSelected(const QString& input_dir);
    void sig_OutputDirSelected(const QString& output_dir);
    void sig_DbmEdited(const QString& dbm);
    void sig_BeginGenerator();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
