#include "clock.h"
#include "ui_clock.h"
using namespace std;

Clock::Clock(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Clock)
{
    ui->setupUi(this);

    /*int startaddress = clockProcess.address;
    StoreData(startaddress);*/

    QTimer *timer=new QTimer();

    connect(timer,SIGNAL(timeout()),this,SLOT(run()));
    timer->start(1000);
}

Clock::~Clock()
{
    delete ui;
}

void Clock::start(){
    //0-3byte表示年份 4表示月份 5表示天数 6表示小时 7表示分钟 8表示秒
    clock.start();
    time_t t=time(NULL);
    struct tm* now=localtime(&t);
    this->time_year=now->tm_year+1900;
    this->time_mon=now->tm_mon+1;
    this->time_day=now->tm_mday;
    this->time_hour=now->tm_hour;
    this->time_min=now->tm_min;
    this->time_sec=now->tm_sec;
    int y1,y2,y3,y4; //四个数字表示年份
    y1=time_year/1000;
    y2=(time_year-y1*1000)/100;
    y3=(time_year-y1*1000-y2*100)/10;
    y4=(time_year-y1*1000-y2*100-y3*10);
    change_byte_by_num(clock.contents[0],y1);
    change_byte_by_num(clock.contents[1],y2);
    change_byte_by_num(clock.contents[2],y3);
    change_byte_by_num(clock.contents[3],y4);
    change_byte_by_num(clock.contents[4],time_mon);
    change_byte_by_num(clock.contents[5],time_day);
    change_byte_by_num(clock.contents[6],time_hour);
    change_byte_by_num(clock.contents[7],time_min);
    change_byte_by_num(clock.contents[8],time_sec);
}
void Clock::showTime(){
    this->time_sec=binary_to_num(clock.contents[8].contents);
    this->time_min=binary_to_num(clock.contents[7].contents);
    this->time_hour=binary_to_num(clock.contents[6].contents);
    this->time_day=binary_to_num(clock.contents[5].contents);
    this->time_mon=binary_to_num(clock.contents[4].contents);
    this->time_year=binary_to_num(clock.contents[0].contents)*1000+binary_to_num(clock.contents[1].contents)*100+
            binary_to_num(clock.contents[2].contents)*10+binary_to_num(clock.contents[3].contents);
    ui->textBrowser->setText(QString::number(this->time_year)+"-"+QString::number(this->time_mon)+"-"+QString::number(this->time_day)+" "+
                             QString::number(this->time_hour)+":"+QString::number(this->time_min)+":"+QString::number(this->time_sec));
}
tm Clock::recordCurrentTime(){
     tm currentTime;
     currentTime.tm_year=this->time_year;
     currentTime.tm_mon=this->time_mon;
     currentTime.tm_mday=this->time_day;
     currentTime.tm_hour=this->time_hour;
     currentTime.tm_min=this->time_min;
     currentTime.tm_sec=this->time_sec;
     return currentTime;
}
void Clock::carry(){
    //进位操作
    int zero=0;
    int one=1;
    if (binary_to_num(clock.contents[8].contents)==60)  {
        ++clock.contents[7];
        change_byte_by_num(clock.contents[8],zero);
    }
    if (binary_to_num(clock.contents[7].contents)==60)  {
        ++clock.contents[6];
        change_byte_by_num(clock.contents[7],zero);
    }
    if (binary_to_num(clock.contents[6].contents)==24)  {
        ++clock.contents[5];
        change_byte_by_num(clock.contents[6],zero);
    }

    // carrying bit according to month
    if (binary_to_num(clock.contents[5].contents)==32) {
        if ((binary_to_num(clock.contents[4].contents)==1)||
        (binary_to_num(clock.contents[4].contents)==3)||
        (binary_to_num(clock.contents[4].contents)==5)||
        (binary_to_num(clock.contents[4].contents)==7)||
        (binary_to_num(clock.contents[4].contents)==8)||
        (binary_to_num(clock.contents[4].contents)==10)||
        (binary_to_num(clock.contents[4].contents)==12))
        {
        ++clock.contents[4];
        change_byte_by_num(clock.contents[5],one);
        }
    }
    if (binary_to_num(clock.contents[5].contents)==31) {
        if ((binary_to_num(clock.contents[4].contents)==4)||
        (binary_to_num(clock.contents[4].contents)==6)||
        (binary_to_num(clock.contents[4].contents)==9)||
        (binary_to_num(clock.contents[4].contents)==11))
        {
        ++clock.contents[4];
        change_byte_by_num(clock.contents[5],one);
        }
    }
    if (binary_to_num(clock.contents[5].contents)==30) {
        if ((binary_to_num(clock.contents[4].contents)==2))
        {
            if (this->time_year%4==0&&this->time_year%100!=0)
            {
                ++clock.contents[4];
                change_byte_by_num(clock.contents[5],one);
            }
        }
    }
    if (binary_to_num(clock.contents[5].contents)==29) {
        if ((binary_to_num(clock.contents[4].contents)==2))
        {
            if (this->time_year%4!=0||this->time_year%100==0)
            {
                ++clock.contents[4];
                change_byte_by_num(clock.contents[5],one);
            }
        }
    }



    if (binary_to_num(clock.contents[4].contents)==13)  {
        ++clock.contents[3];
        change_byte_by_num(clock.contents[4],one);
    }


    //Four number represent year, both decimal
    for (int i=3;i>0;i--){
        if(binary_to_num(clock.contents[i].contents)==10){
            ++clock.contents[i-1];
            change_byte_by_num(clock.contents[i],zero);
        }
    }
}
void Clock::StoreData(int address) {
    int startadress = address;
    RAM firstPage = ana_ram[startadress];
    RAM secondPage = ana_ram[startadress + 1];
}
void Clock::run(){
    ++clock.contents[8];
    carry();
    showTime();
}
void Clock::close(){
    shouleClose=true;
}
void Clock::closeEvent(QCloseEvent *event){
    endClock=true;
    hasClock=false;
    clockProcess.kill_Process_APP(ana_ram);
}
