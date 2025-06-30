#ifndef DAY7INFO_H
#define DAY7INFO_H

#include <QVector>
#include <QLabel>
#include <QWidget>

class MainWindow;

class day7info : public QWidget{
    Q_OBJECT
public:
    day7info(QWidget *parent=nullptr);
    ~day7info();

    QVector<QLabel*> dates;
    QVector<QLabel*> weathersD;
    QVector<QLabel*> weathersN;
    QVector<QLabel*> TemMaxs;
    QVector<QLabel*> TemMins;
    QVector<QLabel*> Winds;

    QLabel *dateTitle;
};
#endif //DAY7INFO_H
