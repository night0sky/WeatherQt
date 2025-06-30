#include "mainwindow.h"
#include <QApplication>
#include <QResource>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    QResource::registerResource("app_resources.rcc");
    w.show();
    return a.exec();
}
