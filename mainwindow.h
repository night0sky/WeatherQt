#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QObject>
#include <QLineEdit>
#include <QLabel>
#include <QFrame>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QWidget>
#include <QGridLayout>
#include <QVector>
#include <QCoreApplication>
#include <QDebug>
#include <QUrlQuery>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QtCore/QByteArray>
#include <QMessageBox>
#include <QMap>
#include <QFile>
#include <QTimer>
#include "Api.h"
#include "day7info.h"




class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public:
    void open7();
    void openLiving();
    void handleWeatherData(const QByteArray &data);
    void handleWeatherData7d(const QByteArray &date);
    void handleApiError(const QString &error);
    void reSetInfo();
    QString getCityCode(const QString& cityName);

public:
    ApiCaller *m_apiCaller;
    ApiCaller *d7_apiCaller;
    QLineEdit *LocationInfo;
    QLabel *Temper;
    QLabel *weather;
    QLabel *SunriseTime;
    QLabel *SunsetTime;
    QLabel *Feeling;
    QLabel *windInfo;
    QLabel *Wetness;
    QLabel *Pressure;
    QLabel *TemMM;
    day7info *d7=nullptr;

private:
    QTimer *timer;
};
#endif // MAINWINDOW_H
