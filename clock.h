#ifndef CLOCK_H
#define CLOCK_H
#include<stdio.h>
#include<time.h>
#include<F_code_library.h>
//#include<windows.h>
#include<iostream>
class Clock{
struct TimeCarrier{
    int time_year;
    int time_mon;
    int time_day;
    int time_hour;
    int time_min;
    int time_sec;
};
private:
    int time_year;
    int time_mon;
    int time_day;
    int time_hour;
    int time_min;
    int time_sec;
    bool shouleClose=false;
    string instruct;
    RAM clock;
public:
    void start();
    void run();
    void showTime();
    void carry();
    void close();
    tm recordCurrentTime();
    inline Clock operator-(const Clock& subtractor);

};
#endif // CLOCK_H
