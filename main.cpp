/*
Filename: main.cpp
*/
#include "mainwindow.h"
#include "color.h"
#include <QApplication>
int Color::amountOfColors = 0;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
