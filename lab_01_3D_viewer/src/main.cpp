#include "mainwindow.h"
#include "model.h"
#include "process.h"
#include <iostream>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    model_t model;
    init_model(model);

    MainWindow w(model);

    w.show();
    return a.exec();
}
