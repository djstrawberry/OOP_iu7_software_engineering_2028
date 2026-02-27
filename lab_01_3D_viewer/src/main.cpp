#include "mainwindow.h"
#include "model_processor.h"
#include "process.h"
#include <iostream>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;

    w.show();
    return a.exec();
}
