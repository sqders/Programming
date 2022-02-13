#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QCoreApplication::addLibraryPath("W:/qt1/6.0.2/mingw81_64/plugins");
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
