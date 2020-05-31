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
    connect(timer,SIGNAL(timeout()),this,SLOT(update()));
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
void controller::update(){
    for (int i=0;i<taskNumber;i++){
        QModelIndex index=model->index(i,2,QModelIndex());
        QString runTime=index.data().toString();
        int time=runTime.toInt();
        time+=1;
        QString nextTime=QString::number(time);
        qDebug()<<nextTime<<endl;
        model->setItem(i,2,new QStandardItem(nextTime));
    }
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
    painter.setPen(Qt::black);
    painter.setFont(QFont("Arial", 20));
    painter.drawText(MEM_MARGIN - 10, MEM_MARGIN - 10, "RAM Visualization:");

    painter.setPen(Qt::black);
    painter.setFont(QFont("Arial", 20));
    painter.drawText(MEM_MARGIN - 10, MEM_MARGIN * 2, "RAM Usage: \n" + QString::number(memory_usage(ana_ram)) + QString("%"));
    update();
}
void controller::keyPressEvent(QKeyEvent *event) {
    switch (event->key()) {
    case Qt::Key_1:
        for (int i = 0; i < 10; i++) {
            ana_ram[i].ram_used = 0;
        }
        break;
    case Qt::Key_2:
        for (int i = 10; i < 20; i++) {
            ana_ram[i].ram_used = 0;
        }
        break;
    }
}
