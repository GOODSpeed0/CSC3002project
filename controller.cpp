#include "controller.h"
#include "ui_controller.h"
#include <QPainter>
#include <QKeyEvent>
#include "F_code_library.h"
#include "global.h"
#include<QStandardItemModel>
#include<QDebug>


controller::controller(QWidget *parent) :
QMainWindow(parent),
    ui(new Ui::controller)
{
    ui->setupUi(this);
    QTimer *timer=new QTimer();
    model->setColumnCount(3);
    model->setHeaderData(0,Qt::Horizontal,QString::fromLocal8Bit("Process_Name"));
    model->setHeaderData(1,Qt::Horizontal,QString::fromLocal8Bit("Memory_Used(MB)"));
    model->setHeaderData(2,Qt::Horizontal,QString::fromLocal8Bit("RunTime"));
    ui->tableView->setModel(model);
    ui->tableView->setColumnWidth(0,200);
    ui->tableView->setColumnWidth(1,200);
    ui->tableView->setColumnWidth(2,80);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    connect(timer,SIGNAL(timeout()),this,SLOT(updateTime()));
    timer->start(1000);
}

controller::~controller()
{
    delete ui;
}

void controller::updateTasks(QString name,QString memory,QString runTime){

    model->setItem(taskNumber,0,new QStandardItem(name));
    model->setItem(taskNumber,1,new QStandardItem(memory));
    model->setItem(taskNumber,2,new QStandardItem(runTime));
    taskNumber+=1;
}
void controller::updateTime(){
    if (endSnack) {
        deleteProcess(process_id_Snack);
        endSnack=false;
    }
    if (endClock) {
        deleteProcess(process_id_Clock);
        endClock=false;
    }
    if (endMine){
        deleteProcess(process_id_Mine);
        endMine=false;
    }
    for (int i=0;i<taskNumber;i++){
        //int duration=nowTime.tm_min*60+nowTime.tm_sec-startTimes[i].tm_min*60-startTimes[i].tm_sec;
        QModelIndex index=model->index(i,2,QModelIndex());
        QString runTime=index.data().toString();
        int time=runTime.toInt();
        time+=1;
        QString nextTime=QString::number(time);
        model->setItem(i,2,new QStandardItem(nextTime));
    }
    //Update ROMUsage
    ui->textBrowser_C->setText("C:"+QString::fromStdString(RomUsage((ana_rom[0]))));
    ui->textBrowser_D->setText("D:"+QString::fromStdString(RomUsage((ana_rom[1]))));
    ui->textBrowser_E->setText("E:"+QString::fromStdString(RomUsage((ana_rom[2]))));

}
void controller::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    painter.setBrush(QColor(219, 207, 202));
    painter.setPen(QColor(13, 12, 12));
    painter.drawRect(MEM_MARGIN, MEM_MARGIN, MEM_BLOCK * 20, MEM_BLOCK);

    for (int i = 0; i < 20; i++) {
        painter.drawLine((MEM_MARGIN + MEM_BLOCK*i), MEM_MARGIN ,(MEM_MARGIN + MEM_BLOCK * i), MEM_MARGIN + MEM_BLOCK);
    }
    string s = show_RAM(ana_ram);
    for (int i = 0; i < 20; i++) {
        int used = stoi(s.substr(i,1));
        if (used == 1) {
            painter.setBrush(QColor(13, 12, 12));
            painter.drawRect((MEM_MARGIN + MEM_BLOCK *i), MEM_MARGIN, MEM_BLOCK, MEM_BLOCK);
        }
    }
    update();
}

void controller::deleteProcess(int process_id){
    model->removeRow(process_id);
    for (int i=process_id+1;i<taskNumber;i++){
        if (process_id_Mine==i){
            process_id_Mine-=1;
        }
        else if (process_id_Clock==i){
            process_id_Clock-=1;
        }
        else if (process_id_Snack==i){
            process_id_Snack-=1;
        }
        else if (process_id_Text==i){
            process_id_Text-=1;
        }
    }
    taskNumber-=1;

}
