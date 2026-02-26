#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "model_processor.h"
#include "process.h"
#include <QMainWindow>
#include <QFileDialog>
#include <QString>

QT_BEGIN_NAMESPACE
namespace Ui 
{
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

    public:
        MainWindow(model_t& model, QWidget *parent = nullptr);
        ~MainWindow();
        result_t draw();

    private:
        Ui::MainWindow *ui;
        model_t& model;

    private slots:
        result_t ActionLoadFile_triggered();
        result_t ScalePushButton_clicked();
        result_t RotatePushButton_clicked();
        result_t TransferPushButton_clicked();
};
#endif // MAINWINDOW_H
