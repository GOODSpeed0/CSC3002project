#ifndef CLOCK_H
#define CLOCK_H

#include<stdio.h>
#include<time.h>
#include<F_code_library.h>
#include<windows.h>
#include<iostream>
#include <QWidget>
#include <QTimer>
#include"global.h"

namespace Ui {
class Clock;
}

class Clock : public QWidget
{
    Q_OBJECT

public:
    explicit Clock(QWidget *parent = nullptr);
    ~Clock();
    void start();
    void showTime();
    void carry();
    void close();
    tm recordCurrentTime();
    inline Clock operator-(const Clock& subtractor);
    void closeEvent(QCloseEvent *event);
    void StoreData(int address);
private slots:
    void run();
private:
    Ui::Clock *ui;
    int time_year;
    int time_mon;
    int time_day;
    int time_hour;
    int time_min;
    int time_sec;
    bool shouleClose=false;
    string instruct;
    RAM clock;
};



#endif // CLOCK_H
