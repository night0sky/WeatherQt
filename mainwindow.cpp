#include "mainwindow.h"
#include "day7info.h"
#include "LivingText.h"
#include "Api.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    //宇航天气欢迎您  //用我名字取的
    setWindowTitle("宇航天气");

    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);


    QFrame *leftFrame = new QFrame(centralWidget);
    QFrame *centerFrame = new QFrame(centralWidget);
    QFrame *rightFrame = new QFrame(centralWidget);

    // 左窗口控件
    LocationInfo = new QLineEdit("东莞",leftFrame);
    QLabel *Sunrise = new QLabel("日出", leftFrame);
    SunriseTime = new QLabel(leftFrame);
    QLabel *Sunset = new QLabel("日落", leftFrame);
    SunsetTime = new QLabel(leftFrame);
    QPushButton *reSet=new QPushButton("刷新",leftFrame);

    // 中窗口控件
    QLabel *background = new QLabel(centerFrame);
    Temper = new QLabel("加载中...", centerFrame);
    weather = new QLabel("天气", centerFrame);

    QFrame *FeelingFrame=new QFrame(centerFrame);
    QFrame *WindInfoFrame=new QFrame(centerFrame);
    QFrame *WetpercentFrame=new QFrame(centerFrame);
    QFrame *PressureFrame=new QFrame(centerFrame);

    TemMM=new QLabel(centerFrame);
    Feeling=new QLabel(FeelingFrame);
    windInfo=new QLabel(WindInfoFrame);
    Wetness=new QLabel(WetpercentFrame);
    Pressure=new QLabel(PressureFrame);

    // 右窗口控件
    QLabel *TimeNow = new QLabel("",rightFrame);
    QPushButton *day7infoB = new QPushButton("近7日天气", rightFrame);
    QPushButton *moreLiving = new QPushButton("更多生活相关", rightFrame);



    // 左窗口布局
    QVBoxLayout *leftLay = new QVBoxLayout(leftFrame);
    leftLay->addWidget(LocationInfo);
    leftLay->addStretch(1);
    leftLay->addWidget(Sunrise);
    leftLay->addWidget(SunriseTime);
    leftLay->addWidget(Sunset);
    leftLay->addWidget(SunsetTime);
    leftLay->addStretch(2);
    leftLay->addWidget(reSet);

    // 中窗口布局
    QVBoxLayout *centerLay = new QVBoxLayout(centerFrame);
    QHBoxLayout *centerLayA=new QHBoxLayout;
    QHBoxLayout *centerLayX=new QHBoxLayout;
    QHBoxLayout *centerLayY=new QHBoxLayout;


    centerLayA->addWidget(Temper);
    centerLayA->addStretch(1);
    centerLayA->addWidget(weather);
    centerLayA->setStretch(0, 1);
    centerLayA->setStretch(1, 1);


    QFont bigFont;
    bigFont.setPointSize(48);

    QFont midFont;
    midFont.setPointSize(30);

    Temper->setFont(bigFont);
    Temper->setAlignment(Qt::AlignCenter);

    weather->setFont(bigFont);
    weather->setAlignment(Qt::AlignRight);

    TemMM->setFont(bigFont);
    TemMM->setAlignment(Qt::AlignCenter);

    Feeling->setFont(midFont);
    windInfo->setFont(midFont);
    Wetness->setFont(midFont);
    Pressure->setFont(midFont);

    windInfo->setAlignment(Qt::AlignRight);

    centerLayX->addWidget(Feeling);
    centerLayX->addWidget(windInfo);

    centerLayY->addWidget(Wetness);
    centerLayY->addWidget(Pressure);

    centerLay->addLayout(centerLayA);
    centerLay->addWidget(TemMM);
    centerLay->addStretch(2);
    centerLay->addLayout(centerLayX);
    centerLay->addLayout(centerLayY);

    // 右窗口布局
    QVBoxLayout *rightLay = new QVBoxLayout(rightFrame);
    rightLay->addWidget(TimeNow);
    rightLay->addStretch(2);
    rightLay->addWidget(day7infoB);
    rightLay->addWidget(moreLiving);

    // 主窗口整体布局
    QHBoxLayout *wholeLay = new QHBoxLayout(centralWidget);
    wholeLay->addWidget(leftFrame);
    wholeLay->addWidget(centerFrame);
    wholeLay->addWidget(rightFrame);
    wholeLay->setStretch(0, 2);
    wholeLay->setStretch(1, 5);
    wholeLay->setStretch(2, 2);

    // 设置窗口初始大小
    resize(800, 500);


    connect(day7infoB,&QPushButton::clicked,this,&MainWindow::open7);
    connect(moreLiving,&QPushButton::clicked,this,&MainWindow::openLiving);
    connect(reSet,&QPushButton::clicked,this,&MainWindow::reSetInfo);


    m_apiCaller = new ApiCaller(this);
    connect(m_apiCaller, &ApiCaller::requestCompleted, this, &MainWindow::handleWeatherData);
    connect(m_apiCaller, &ApiCaller::requestFailed, this, &MainWindow::handleApiError);

    d7_apiCaller=new ApiCaller(this);
    connect(d7_apiCaller,&ApiCaller::requestCompleted, this, &MainWindow::handleWeatherData7d);

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, [TimeNow](){
        TimeNow->setText(QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss"));
    });
    timer->start(1000);

}




void MainWindow::open7(){
    if (d7) {
        d7->close();
        delete d7;
    }
    d7 = new day7info(nullptr);
    d7->show();
    // 请求7天天气预报
    QString city = getCityCode(LocationInfo->text());
    if(city.isEmpty()) {
        city = "101010100"; // 默认北京
    }
    QUrl url7("https://na5n8kmhfn.re.qweatherapi.com/v7/weather/7d?location="+city+"&key=34755a3426cd4aa9aef0d34160985cc5");
    d7_apiCaller->sendGetRequest(url7);
}


void MainWindow::openLiving(){
    LivingT *LivingW=new LivingT(nullptr);
    LivingW->show();
}

void MainWindow::reSetInfo(){
    QString city =getCityCode(LocationInfo->text());
    if(city.isEmpty()) {
        QMessageBox::warning(this, "错误", "未找到城市代码");
        city = "101010100"; //默认北京
    }
    QUrl url("https://na5n8kmhfn.re.qweatherapi.com/v7/weather/now?location="+city+"&key=34755a3426cd4aa9aef0d34160985cc5");
    m_apiCaller->sendGetRequest(url);
    if (d7) {
        QUrl url7("https://na5n8kmhfn.re.qweatherapi.com/v7/weather/7d?location="+city+"&key=34755a3426cd4aa9aef0d34160985cc5");
        d7_apiCaller->sendGetRequest(url7);
    }
}



void MainWindow::handleWeatherData(const QByteArray &data)
{
    qDebug()<<"yesyes";
    QJsonDocument doc = QJsonDocument::fromJson(data);
    if (!doc.isNull() && doc.isObject()) {
        QJsonObject json = doc.object();

        if (json.contains("now") && json["now"].isObject()) {
            QJsonObject nowObj = json["now"].toObject();

            if (nowObj.contains("temp")) {
                QString tempStr = nowObj["temp"].toString();
                bool ok;
                int temp = tempStr.toInt(&ok);
                if (ok) {
                    Temper->setText(QString::number(temp) + "°C");
                } else {
                    Temper->setText(tempStr + "°C");
                }
            }


            QString weatherText = nowObj["text"].toString();
            weather->setText(weatherText);

            QString FeelingT="体感："+nowObj["feelsLike"].toString()+"°C";
            Feeling->setText(FeelingT);

            QString Windinfom=nowObj["windDir"].toString()+" "+nowObj["windScale"].toString()+"级";
            windInfo->setText(Windinfom);

            QString wetnessT="湿度:"+nowObj["humidity"].toString()+"%";
            Wetness->setText(wetnessT);

            //百帕->kPa
            QString pressureT=QString::number(nowObj["pressure"].toString().toDouble()/10.0)+"kPa";
            Pressure->setText(pressureT);

        } else {
            QMessageBox::warning(this, "数据错误", "缺少'now'对象");
        }
    }
}



void MainWindow::handleApiError(const QString &error)
{
    QMessageBox::critical(this, "API错误", "获取天气数据失败: " + error);
}


QString MainWindow::getCityCode(const QString &cityName)
{
    static QHash<QString, QString> cityCodeMap;
    static bool isLoaded = false;

    if (!isLoaded) {
        QString filePath =":/CityCode.json";
        QFile file(filePath);

        if (!file.open(QIODevice::ReadOnly)) {
            qCritical() << "无法打开城市代码文件:" << filePath;
            return "";
        }

        QJsonParseError parseError;
        QJsonDocument doc = QJsonDocument::fromJson(file.readAll(), &parseError);
        file.close();

        if (parseError.error != QJsonParseError::NoError) {
            qCritical() << "城市代码JSON解析错误:" << parseError.errorString()
                    << "位置:" << parseError.offset;
            return "";
        }

        if (doc.isObject()) {
            QJsonObject obj = doc.object();
            for (auto it = obj.begin(); it != obj.end(); ++it) {
                cityCodeMap[it.key()] = it.value().toString();
            }
            isLoaded = true;
        } else {
            qWarning() << "城市代码文件格式无效";
            return "";
        }
    }

    auto it = cityCodeMap.find(cityName.trimmed());
    if (it != cityCodeMap.end()) {
        return it.value();
    }

    return "";
}


MainWindow::~MainWindow(){
    if(d7)delete d7;
}


