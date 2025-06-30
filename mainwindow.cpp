#include "mainwindow.h"
#include "day7info.h"
#include "Api.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    d7=nullptr;

    //宇航天气欢迎您  //用我名字取的
    setWindowTitle("宇航天气");

    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);


    QFrame *leftFrame = new QFrame(centralWidget);
    QFrame *centerFrame = new QFrame(centralWidget);
    QFrame *rightFrame = new QFrame(centralWidget);

    leftFrame->setFrameShape(QFrame::StyledPanel);
    leftFrame->setStyleSheet("background-color: #F8F8F8; border-radius: 8px;");
    centerFrame->setFrameShape(QFrame::StyledPanel);
    centerFrame->setStyleSheet("background-color: white; border-radius: 8px;");
    rightFrame->setFrameShape(QFrame::StyledPanel);
    rightFrame->setStyleSheet("background-color: #F8F8F8; border-radius: 8px;");

    // 左窗口控件
    LocationInfo = new QLineEdit("东莞",leftFrame);
    LocationInfo->setAlignment(Qt::AlignCenter);
    LocationInfo->setStyleSheet("background: white; color: black; border: 1px solid #D0D0D0; border-radius: 4px; padding: 4px;");

    QLabel *Sunrise = new QLabel("日出", leftFrame);
    SunriseTime = new QLabel(leftFrame);
    Sunrise->setStyleSheet("color: #555;");
    SunriseTime->setStyleSheet("font-weight: bold; color: #FF8C00;");


    QLabel *Sunset = new QLabel("日落", leftFrame);
    SunsetTime = new QLabel(leftFrame);
    Sunset->setStyleSheet("color: #555;");
    SunsetTime->setStyleSheet("font-weight: bold; color: #FF4500;");

    QPushButton *reSet=new QPushButton("刷新",leftFrame);
    reSet->setStyleSheet("QPushButton { background-color: #4A90E2; color: white; border-radius: 4px; padding: 6px; }""QPushButton:hover { background-color: #3A7BC8; }");

    // 设置城市代码映射
    settings = new QSettings("MyCompany", "AstroWeather", this);

    // 收藏列表相关控件
    QLabel *favoritesLabel = new QLabel("收藏城市", leftFrame);
    favoritesLabel->setStyleSheet("color: #555; font-weight: bold;");

    favoritesList = new QListWidget(leftFrame);
    favoritesList->setStyleSheet(
        "QListWidget {background-color: #F0F0F0;color: #00008B;border: 1px solid #D0D0D0;border-radius: 4px;padding: 4px;}"
        "QListWidget::item {padding: 6px;border-bottom: 1px solid #F0F0F0;}"
        "QListWidget::item:selected {background-color: #E3F2FD;color: #1976D2;}"
    );
    favoritesList->setMaximumHeight(150);

    addFavoriteBtn = new QPushButton("添加收藏", leftFrame);
    addFavoriteBtn->setStyleSheet(
        "QPushButton {background-color: #4CAF50;color: white;border-radius: 4px;padding: 4px;min-width: 70px;}"
        "QPushButton:hover {background-color: #43A047;}"
    );

    removeFavoriteBtn = new QPushButton("删除收藏", leftFrame);
    removeFavoriteBtn->setStyleSheet(
        "QPushButton {background-color: #F44336;color: white;border-radius: 4px;padding: 4px;min-width: 70px;}"
        "QPushButton:hover {background-color: #E53935;}"
    );





    // 中窗口控件
    Temper = new QLabel("加载中...", centerFrame);
    Temper->setStyleSheet("color: #2C3E50; font-weight: bold;");

    weather = new QLabel("天气", centerFrame);
    weather->setStyleSheet("color: #2C3E50; font-weight: bold;");

    QGroupBox *detailGroup = new QGroupBox("天气详情", centerFrame);

    detailGroup->
        setStyleSheet
        ("QGroupBox { border: 1px solid #E0E0E0; border-radius: 6px; margin-top: 10px; }"
        "QGroupBox::title { subcontrol-origin: margin; padding: 0 5px; color: #3498DB; }"
    );

    TemMM=new QLabel(centerFrame);
    TemMM->setStyleSheet("color: #7F8C8D;");

    Feeling=new QLabel(detailGroup);
    Feeling->setStyleSheet("color: #3498DB;");

    windInfo=new QLabel(detailGroup);
    windInfo->setStyleSheet("color: #27AE60;");

    Wetness=new QLabel(detailGroup);
    Wetness->setStyleSheet("color: #2980B9;");

    Pressure=new QLabel(detailGroup);
    Pressure->setStyleSheet("color: #8E44AD;");

    // 右窗口控件
    QLabel *TimeNow = new QLabel("",rightFrame);
    TimeNow->setStyleSheet("font-size: 16px; color: #2C3E50; font-weight: bold;");
    Sports=new QLabel(rightFrame);

    QGroupBox *lifeIndexGroup = new QGroupBox("生活指数", rightFrame);
    lifeIndexGroup->setStyleSheet(
        "QGroupBox {border: 1px solid #E0E0E0;border-radius: 8px;margin-top: 10px;background-color: #F0F8FF;}"
        "QGroupBox::title {subcontrol-origin: margin;padding: 0 8px;color: #4682B4;font-weight: bold;}"
    );

    // 初始化生活指数标签
    Sports = new QLabel("运动指数: 加载中...", lifeIndexGroup);
    CarWash = new QLabel("洗车指数: 加载中...", lifeIndexGroup);
    Clothes = new QLabel("穿衣指数: 加载中...", lifeIndexGroup);
    Comfort = new QLabel("舒适度指数: 加载中...", lifeIndexGroup);
    UVray = new QLabel("紫外线指数: 加载中...", lifeIndexGroup);
    Drying = new QLabel("晾晒指数: 加载中...", lifeIndexGroup);

    // 设置生活指数标签样式
    QString labelStyle = "QLabel {color: #2E8B57;padding: 5px;font-size: 13px;border-radius: 4px;background-color: rgba(255, 255, 255, 0.7);margin: 2px}";
    Sports->setStyleSheet(labelStyle);
    CarWash->setStyleSheet(labelStyle);
    Clothes->setStyleSheet(labelStyle);
    Comfort->setStyleSheet(labelStyle);
    UVray->setStyleSheet(labelStyle);
    Drying->setStyleSheet(labelStyle);


    QPushButton *day7infoButton = new QPushButton("近7日天气", rightFrame);
    day7infoButton->setStyleSheet(
        "QPushButton {background-color: #27AE60;color: white;border-radius: 6px;padding: 10px;font-weight: bold;min-height: 40px;}"
        "QPushButton:hover {background-color: #219653;}"
        "QPushButton:pressed {background-color: #1E8449;}"
    );

    // 左窗口布局
    QVBoxLayout *leftLay = new QVBoxLayout(leftFrame);
    leftLay->setContentsMargins(15, 15, 15, 15);
    leftLay->setSpacing(10);

    QHBoxLayout *favoritesBtnLayout = new QHBoxLayout;
    favoritesBtnLayout->addWidget(addFavoriteBtn);
    favoritesBtnLayout->addWidget(removeFavoriteBtn);


    leftLay->addWidget(LocationInfo);
    leftLay->addSpacing(20);

    QGridLayout *sunLayout = new QGridLayout;
    sunLayout->addWidget(Sunrise, 0, 0);
    sunLayout->addWidget(SunriseTime, 0, 1);
    sunLayout->addWidget(Sunset, 1, 0);
    sunLayout->addWidget(SunsetTime, 1, 1);
    leftLay->addLayout(sunLayout);

    leftLay->addSpacing(10);
    leftLay->addWidget(favoritesLabel);
    leftLay->addWidget(favoritesList);
    leftLay->addLayout(favoritesBtnLayout);
    leftLay->addSpacing(20);

    leftLay->addWidget(reSet, 0, Qt::AlignCenter);

    // 中窗口布局
    QVBoxLayout *centerLay = new QVBoxLayout(centerFrame);
    centerLay->setContentsMargins(20, 20, 20, 20);
    centerLay->setSpacing(15);

    // 顶部天气信息
    centerLay->addWidget(Temper, 0, Qt::AlignCenter);
    centerLay->addSpacing(5);

    centerLay->addWidget(weather, 0, Qt::AlignCenter);
    centerLay->addSpacing(10);

    centerLay->addWidget(TemMM, 0, Qt::AlignCenter);
    centerLay->addSpacing(20);

    // 天气详情布局
    QGridLayout *detailLayout = new QGridLayout(detailGroup);
    detailLayout->setContentsMargins(15, 15, 15, 15);
    detailLayout->setSpacing(15);

    detailLayout->addWidget(Feeling, 0, 0, Qt::AlignLeft);
    detailLayout->addWidget(windInfo, 0, 1, Qt::AlignLeft);
    detailLayout->addWidget(Wetness, 1, 0, Qt::AlignLeft);
    detailLayout->addWidget(Pressure, 1, 1, Qt::AlignLeft);

    // 添加垂直弹簧使详情框不会拉伸
    QSpacerItem *verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
    centerLay->addItem(verticalSpacer);

    detailGroup->setLayout(detailLayout);
    centerLay->addWidget(detailGroup, 1);

    centerLay->addStretch(1);


    // 右窗口布局
    QVBoxLayout *rightLay = new QVBoxLayout(rightFrame);
    rightLay->setContentsMargins(15, 15, 15, 15);
    rightLay->setSpacing(20);

    QVBoxLayout *lifeIndexLayout = new QVBoxLayout(lifeIndexGroup);
    lifeIndexLayout->setContentsMargins(12, 20, 12, 12);
    lifeIndexLayout->setSpacing(8);
    lifeIndexLayout->addWidget(Sports);
    lifeIndexLayout->addWidget(CarWash);
    lifeIndexLayout->addWidget(Clothes);
    lifeIndexLayout->addWidget(Comfort);
    lifeIndexLayout->addWidget(UVray);
    lifeIndexLayout->addWidget(Drying);


    QFrame *timeFrame = new QFrame(rightFrame);
    timeFrame->setStyleSheet("background-color: #E3F2FD; border-radius: 8px;");
    QVBoxLayout *timeLayout = new QVBoxLayout(timeFrame);
    timeLayout->addWidget(TimeNow, 0, Qt::AlignCenter);
    timeLayout->setContentsMargins(10, 10, 10, 10);

    rightLay->addWidget(timeFrame);
    rightLay->addWidget(lifeIndexGroup);
    rightLay->addStretch(1);
    rightLay->addWidget(day7infoButton);


    // 主窗口整体布局
    QHBoxLayout *wholeLay = new QHBoxLayout(centralWidget);
    wholeLay->setContentsMargins(15, 15, 15, 15);
    wholeLay->setSpacing(15);
    wholeLay->addWidget(leftFrame);
    wholeLay->addWidget(centerFrame);
    wholeLay->addWidget(rightFrame);
    wholeLay->setStretch(0, 2);
    wholeLay->setStretch(1, 5);
    wholeLay->setStretch(2, 2);

    // 设置窗口初始大小
    resize(900, 550);

    //字体
    QFont bigFont;
    bigFont.setPointSize(36);
    bigFont.setBold(true);
    Temper->setFont(bigFont);
    Temper->setAlignment(Qt::AlignCenter);

    QFont midFont;
    midFont.setPointSize(24);
    weather->setFont(midFont);
    weather->setAlignment(Qt::AlignCenter);

    QFont smallFont;
    smallFont.setPointSize(14);
    Feeling->setFont(smallFont);
    windInfo->setFont(smallFont);
    Wetness->setFont(smallFont);
    Pressure->setFont(smallFont);
    TemMM->setFont(smallFont);

    connect(day7infoButton,&QPushButton::clicked,this,&MainWindow::open7);
    connect(reSet,&QPushButton::clicked,this,&MainWindow::reSetInfo);

    loadFavorites();

    // 连接信号槽
    connect(addFavoriteBtn, &QPushButton::clicked, this, &MainWindow::addToFavorites);
    connect(removeFavoriteBtn, &QPushButton::clicked, this, &MainWindow::removeFromFavorites);
    connect(favoritesList, &QListWidget::itemClicked, this, &MainWindow::onFavoriteClicked);

    m_apiCaller = new ApiCaller(this);
    Life_apiCaller=new ApiCaller(this);
    connect(m_apiCaller, &ApiCaller::requestCompleted, this, &MainWindow::handleWeatherData);
    connect(Life_apiCaller, &ApiCaller::requestCompleted, this, &MainWindow::handleLifeIndexData);

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


void MainWindow::reSetInfo(){
    QString city =getCityCode(LocationInfo->text().trimmed());
    if(city.isEmpty()) {
        QMessageBox::warning(this, "错误", "未找到城市代码");
        city = "101010100"; //默认北京
    }
    QUrl url("https://na5n8kmhfn.re.qweatherapi.com/v7/weather/now?location="+city+"&key=34755a3426cd4aa9aef0d34160985cc5");
    QUrl urlLife("https://na5n8kmhfn.re.qweatherapi.com/v7/indices/1d?location="+city+"&type=0&key=34755a3426cd4aa9aef0d34160985cc5");
    m_apiCaller->sendGetRequest(url);
    Life_apiCaller->sendGetRequest(urlLife);
    if (d7) {
        QUrl url7("https://na5n8kmhfn.re.qweatherapi.com/v7/weather/7d?location="+city+"&key=34755a3426cd4aa9aef0d34160985cc5");
        d7_apiCaller->sendGetRequest(url7);
    }
}


void MainWindow::handleWeatherData(const QByteArray &data)
{
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

            QString FeelingT="体感:  "+nowObj["feelsLike"].toString()+"°C";
            Feeling->setText(FeelingT);

            QString Windinfom=nowObj["windDir"].toString()+" "+nowObj["windScale"].toString()+"级";
            windInfo->setText(Windinfom);

            QString wetnessT="湿度:  "+nowObj["humidity"].toString()+"%";
            Wetness->setText(wetnessT);

            //百帕->kPa
            QString pressureT="气压:  "+QString::number(nowObj["pressure"].toString().toDouble()/10.0)+"kPa";
            Pressure->setText(pressureT);

        } else {
            QMessageBox::warning(this, "数据错误", "缺少'now'对象");
        }
    }
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

void MainWindow::handleLifeIndexData(const QByteArray &data) {
    QJsonDocument jsonDoc = QJsonDocument::fromJson(data);
    QJsonObject rootObj = jsonDoc.object();

    // 检查 API 返回状态
    if (rootObj["code"].toString() != "200") {
        qDebug() << "生活指数 API 错误:" << rootObj["code"].toString();
        return;
    }

    // 获取生活指数数组
    QJsonArray dailyArray = rootObj["daily"].toArray();
    if (dailyArray.isEmpty()) {
        qDebug() << "生活指数数据为空";
        return;
    }

    // 创建映射表存储各类指数（按类型分组）
    QMap<QString, QVector<QJsonObject>> indexMap;

    // 遍历所有指数项
    for (const QJsonValue &value : dailyArray) {
        QJsonObject indexObj = value.toObject();
        QString type = indexObj["type"].toString();
        indexMap[type].append(indexObj);
    }

    if (indexMap.contains("1")) {
        QJsonObject sportIndex = indexMap["1"].first();
        Sports->setText("运动:    "+sportIndex["category"].toString());
    }

    if (indexMap.contains("2")) {
        QJsonObject carWashIndex = indexMap["2"].first();
        CarWash->setText("洗车:    "+carWashIndex["category"].toString());
    }

    QJsonObject clothIndex = indexMap["3"].first();
    Clothes->setText(clothIndex["text"].toString());

    QJsonObject comfortIndex = indexMap["8"].first();
    Comfort->setText("舒适指数:  "+comfortIndex["category"].toString());

    QJsonObject rayIndex = indexMap["5"].first();
    UVray->setText("紫外线强度:  "+rayIndex["category"].toString());

    QJsonObject dryIndex = indexMap["14"].first();
    Drying->setText("晾晒衣物:  "+dryIndex["category"].toString());
}

void MainWindow::addToFavorites()
{
    QString city = LocationInfo->text().trimmed();  //移除空白
    if (city.isEmpty()) {
        QMessageBox::warning(this, "提示", "请输入城市名称");
        return;
    }

    // 检查城市代码是否存在
    QString cityCode = getCityCode(city);
    if (cityCode.isEmpty()) {
        QMessageBox::warning(this, "提示", "未找到该城市代码");
        return;
    }

    // 检查是否已存在
    for (int i = 0; i < favoritesList->count(); i++) {
        if (favoritesList->item(i)->text() == city) {
            QMessageBox::information(this, "提示", "该城市已在收藏列表中");
            return;
        }
    }

    // 添加到列表
    QListWidgetItem *item = new QListWidgetItem(city);
    item->setData(Qt::UserRole, cityCode);  // 保存城市代码
    favoritesList->addItem(item);

    // 保存收藏列表
    saveFavorites();
}

void MainWindow::removeFromFavorites()
{
    QListWidgetItem *item = favoritesList->currentItem();
    if (!item) {
        QMessageBox::warning(this, "提示", "请选中要删除的收藏");
        return;
    }

    int row = favoritesList->row(item);
    delete favoritesList->takeItem(row);

    // 保存收藏列表
    saveFavorites();
}

void MainWindow::onFavoriteClicked(QListWidgetItem *item)
{
    QString city = item->text();
    LocationInfo->setText(city);
    reSetInfo();  // 刷新天气信息
}

void MainWindow::saveFavorites()
{
    QStringList favorites;
    for (int i = 0; i < favoritesList->count(); i++) {
        QListWidgetItem *item = favoritesList->item(i);
        favorites << item->text() + "|" + item->data(Qt::UserRole).toString();
    }
    settings->setValue("favorites", favorites);
}

void MainWindow::loadFavorites()
{
    QStringList favorites = settings->value("favorites").toStringList();
    for (const QString &fav : favorites) {
        QStringList parts = fav.split("|");
        if (parts.size() >= 2) {
            QListWidgetItem *item = new QListWidgetItem(parts[0]);
            item->setData(Qt::UserRole, parts[1]);
            favoritesList->addItem(item);
        }
    }
}

MainWindow::~MainWindow(){
    if(d7)delete d7;
}
