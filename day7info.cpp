#include "mainwindow.h"

day7info::day7info(QWidget* parent):QWidget(parent){

    setWindowTitle("近7日天气");

    dates.push_back(new QLabel(CITY,this));
    weathersD.push_back(new QLabel("白天天气",this));
    weathersN.push_back(new QLabel("夜间天气",this));
    TemMaxs.push_back(new QLabel("高温",this));
    TemMins.push_back(new QLabel("低温",this));
    Winds.push_back(new QLabel(" ",this));

    for(int i=0;i<7;i++){
        dates.push_back(new QLabel(this));
        weathersD.push_back(new QLabel(this));
        weathersN.push_back(new QLabel(this));
        TemMaxs.push_back(new QLabel(this));
        TemMins.push_back(new QLabel(this));
        Winds.push_back(new QLabel(this));
    }

    QGridLayout *mainLay=new QGridLayout(this);

    for(int i=0;i<8;i++){ // 共8行（标题行+7天数据）
        mainLay->addWidget(dates[i],0,i);       // 日期行
        mainLay->addWidget(weathersD[i],2,i);   // 白天天气行
        mainLay->addWidget(TemMaxs[i],3,i);     // 高温行
        mainLay->addWidget(TemMins[i],5,i);     // 低温行
        mainLay->addWidget(weathersN[i],6,i);   // 夜间天气行
        mainLay->addWidget(Winds[i],7,i);       // 风信息行
        if(i>1)mainLay->setRowStretch(i,2);
    }

    resize(800,600);
}


void MainWindow::handleWeatherData7d(const QByteArray &data)
{
    QJsonDocument jsonDoc = QJsonDocument::fromJson(data);

    // 获取根对象
    QJsonObject rootObj = jsonDoc.object();

    // 检查API返回状态
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

        d7->dates[i+1]->setText(dayObj["fxDate"].toString().left(10));   // 日期 (YYYY-MM-DD)
        d7->weathersD[i+1]->setText(dayObj["textDay"].toString());
        d7->weathersN[i+1]->setText(dayObj["textNight"].toString());
        d7->TemMaxs[i+1]->setText(dayObj["tempMax"].toString() + "°C");
        d7->TemMins[i+1]->setText(dayObj["tempMin"].toString() + "°C");
        d7->Winds[i+1]->setText(dayObj["windDirNight"].toString()+" "+dayObj["windScaleNight"].toString()+"级");
    }

    SunriseTime->setText(dailyArray[0].toObject()["sunrise"].toString());
    SunsetTime->setText(dailyArray[0].toObject()["sunset"].toString());

    d7->CITY=LocationInfo->text();
}



day7info::~day7info(){

}
