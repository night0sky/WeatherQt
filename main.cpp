#include "mainwindow.h"
#include <QApplication>
#include <QResource>
#include <QMediaPlayer>
#include <QAudioOutput>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    qputenv("QT_MEDIA_BACKEND", "windows");

    QApplication::setStyle("Fusion");
    QPalette palette;
    palette.setColor(QPalette::Window, QColor(240, 240, 240));
    palette.setColor(QPalette::WindowText, Qt::black);
    qApp->setPalette(palette);


    QResource::registerResource("app_resources.rcc");
    w.show();
    return a.exec();
}
