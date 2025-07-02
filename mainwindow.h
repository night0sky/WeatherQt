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
#include <QGroupBox>
#include <QListWidget>
#include <QSettings>
#include <QScrollBar>
#include <QSlider>
#include <QFileDialog>
#include <QFileInfo>
#include <QTime>
#include <QStyle>
#include <QDir>
#include <QCloseEvent>
#include <QToolTip>
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
    void handleWeatherData(const QByteArray &data);
    void handleWeatherData7d(const QByteArray &date);
    void handleLifeIndexData(const QByteArray &data);
    void handleAirData(const QByteArray &data);
    void reSetInfo();
    void saveFavorites();
    void loadFavorites();
    QString getCityCode(const QString& cityName);
    QString getAirColor(int aqi);

private slots:
    void addToFavorites();
    void removeFromFavorites();
    void onFavoriteClicked(QListWidgetItem *item);

public:
    ApiCaller *m_apiCaller;
    ApiCaller *d7_apiCaller;
    ApiCaller *Life_apiCaller;
    ApiCaller *Air_apiCaller;
    QLineEdit *LocationInfo;
    QLabel *Temper;
    QLabel *weather;
    QLabel *SunriseTime;
    QLabel *SunsetTime;
    QLabel *Feeling;
    QLabel *windInfo;
    QLabel *Wetness;
    QLabel *Pressure;
    QLabel *Air;
    QLabel *TemMM;
    QLabel *Sports;
    QLabel *CarWash;
    QLabel *Clothes;
    QLabel *Comfort;
    QLabel *ColdAttack;
    QLabel *UVray;
    QLabel *Drying;
    day7info *d7=nullptr;
    QTimer *timer;
    QListWidget *favoritesList;
    QPushButton *addFavoriteBtn;
    QPushButton *removeFavoriteBtn;
    QSettings *settings;

    QString AirColor;
    int aqi;
};
#endif // MAINWINDOW_H
