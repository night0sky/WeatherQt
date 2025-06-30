#include "mainwindow.h"

day7info::day7info(QWidget* parent):QWidget(parent){

    setWindowTitle("近7日天气");
    setStyleSheet("background-color: #F5F7FA;");

    // 创建标题行标签
    dateTitle = new QLabel("",this);
    QLabel *dayWeatherTitle = new QLabel("白天天气", this);
    QLabel *nightWeatherTitle = new QLabel("夜间天气", this);
    QLabel *highTempTitle = new QLabel("最高温度", this);
    QLabel *lowTempTitle = new QLabel("最低温度", this);
    QLabel *windTitle = new QLabel("风力", this);

    windTitle->setAlignment(Qt::AlignCenter);

    // 设置标题样式
    QString titleStyle = "QLabel { text-align: center;font-weight: bold; color: #2C3E50; background-color: #E1EAF7; padding: 8px; border-radius: 4px; }";
    dateTitle->setStyleSheet(titleStyle);
    dayWeatherTitle->setStyleSheet(titleStyle);
    nightWeatherTitle->setStyleSheet(titleStyle);
    highTempTitle->setStyleSheet(titleStyle);
    lowTempTitle->setStyleSheet(titleStyle);
    windTitle->setStyleSheet(titleStyle);

    for(int i=0;i<7;i++){
        QLabel *date = new QLabel(this);
        date->setAlignment(Qt::AlignCenter);
        date->setStyleSheet("QLabel { background-color: white;color: #333333; padding: 8px; border-radius: 4px; }");
        dates.push_back(date);

        QLabel *dayWeather = new QLabel(this);
        dayWeather->setAlignment(Qt::AlignCenter);
        dayWeather->setStyleSheet("QLabel { background-color: #E8F4FD;color: #326B8A; padding: 8px; border-radius: 4px; }");
        weathersD.push_back(dayWeather);

        QLabel *nightWeather = new QLabel(this);
        nightWeather->setAlignment(Qt::AlignCenter);
        nightWeather->setStyleSheet("QLabel { background-color: #EDEDFA;color: #A3A3D2; padding: 8px; border-radius: 4px; }");
        weathersN.push_back(nightWeather);

        QLabel *highTemp = new QLabel(this);
        highTemp->setAlignment(Qt::AlignCenter);
        highTemp->setStyleSheet("QLabel { background-color: #FFEBEE; color: #E53935; padding: 8px; border-radius: 4px; }");
        TemMaxs.push_back(highTemp);

        QLabel *lowTemp = new QLabel(this);
        lowTemp->setAlignment(Qt::AlignCenter);
        lowTemp->setStyleSheet("QLabel { background-color: #E3F2FD; color: #1976D2; padding: 8px; border-radius: 4px; }");
        TemMins.push_back(lowTemp);

        QLabel *wind = new QLabel(this);
        wind->setAlignment(Qt::AlignCenter);
        wind->setStyleSheet("QLabel { background-color: #E8F5E9; color: #388E3C; padding: 8px; border-radius: 4px; }");
        Winds.push_back(wind);
    }

    QGridLayout *mainLay = new QGridLayout(this);
    mainLay->setSpacing(10);
    mainLay->setContentsMargins(15, 15, 15, 15);

    // 添加标题行
    mainLay->addWidget(dateTitle, 0, 0);
    mainLay->addWidget(dayWeatherTitle, 0, 1);
    mainLay->addWidget(nightWeatherTitle, 0, 2);
    mainLay->addWidget(highTempTitle, 0, 3);
    mainLay->addWidget(lowTempTitle, 0, 4);
    mainLay->addWidget(windTitle, 0, 5);

    // 添加数据行
    for(int i=0; i<7; i++){
        mainLay->addWidget(dates[i], i+1, 0);
        mainLay->addWidget(weathersD[i], i+1, 1);
        mainLay->addWidget(weathersN[i], i+1, 2);
        mainLay->addWidget(TemMaxs[i], i+1, 3);
        mainLay->addWidget(TemMins[i], i+1, 4);
        mainLay->addWidget(Winds[i], i+1, 5);
    }

    // 设置列宽比例
    mainLay->setColumnStretch(0, 1);
    mainLay->setColumnStretch(1, 2);
    mainLay->setColumnStretch(2, 2);
    mainLay->setColumnStretch(3, 1);
    mainLay->setColumnStretch(4, 1);
    mainLay->setColumnStretch(5, 2);

    // 设置行高
    for(int i=0; i<8; i++){
        mainLay->setRowMinimumHeight(i, 40);
    }

    // 设置字体
    QFont titleFont;
    titleFont.setPointSize(12);
    titleFont.setBold(true);

    QFont dataFont;
    dataFont.setPointSize(11);

    dateTitle->setFont(titleFont);
    dayWeatherTitle->setFont(titleFont);
    nightWeatherTitle->setFont(titleFont);
    highTempTitle->setFont(titleFont);
    lowTempTitle->setFont(titleFont);
    windTitle->setFont(titleFont);

    for(int i=0; i<7; i++){
        dates[i]->setFont(dataFont);
        weathersD[i]->setFont(dataFont);
        weathersN[i]->setFont(dataFont);
        TemMaxs[i]->setFont(dataFont);
        TemMins[i]->setFont(dataFont);
        Winds[i]->setFont(dataFont);
    }

    resize(900, 500); // 调整窗口大小
}


void MainWindow::handleWeatherData7d(const QByteArray &data)
{
    QJsonDocument jsonDoc = QJsonDocument::fromJson(data);

    // 获取根对象
    QJsonObject rootObj = jsonDoc.object();

    if (rootObj["code"].toString() != "200") {
        qDebug() << "API error:" << rootObj["code"].toString();
        return;
    }

    // 获取daily数组
    QJsonArray dailyArray = rootObj["daily"].toArray();
    if (dailyArray.size() < 7) {
        qDebug() << "Invalid daily data size:" << dailyArray.size();
        return;
    }


    // 提取7天数据
    for (int i = 0; i < 7; ++i) {
        QJsonObject dayObj = dailyArray[i].toObject();

        d7->dates[i]->setText(dayObj["fxDate"].toString().left(10));   // 日期 (YYYY-MM-DD)
        d7->weathersD[i]->setText(dayObj["textDay"].toString());
        d7->weathersN[i]->setText(dayObj["textNight"].toString());
        d7->TemMaxs[i]->setText(dayObj["tempMax"].toString() + "°C");
        d7->TemMins[i]->setText(dayObj["tempMin"].toString() + "°C");
        d7->Winds[i]->setText(dayObj["windDirDay"].toString()+" "+dayObj["windScaleDay"].toString()+"级");

    }

    SunriseTime->setText(dailyArray[0].toObject()["sunrise"].toString());
    SunsetTime->setText(dailyArray[0].toObject()["sunset"].toString());
    TemMM->setText(dailyArray[0].toObject()["tempMin"].toString()+"℃ ~ "+dailyArray[0].toObject()["tempMax"].toString()+"℃");
    d7->dateTitle->setText(LocationInfo->text());
}



day7info::~day7info(){

}
