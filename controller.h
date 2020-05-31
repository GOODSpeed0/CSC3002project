/*
 * This file is the header file
 */




#ifndef CONTROLLER_H
#define CONTROLLER_H
#include <QMainWindow>
#include <QWidget>
#include <QPaintEvent>
#include <QKeyEvent>
#include <QTableView>
#include<QTableWidget>
#include<QStandardItemModel>
#include<QTimer>
const int MEM_MARGIN = 50;
const int MEM_BLOCK = 20;
using namespace std;
namespace Ui {
class controller;
}

class controller : public QMainWindow
{
    Q_OBJECT

public:
    //QTimer *timer=new QTimer(this);
    int taskNumber=0;
    QStandardItemModel *model=new QStandardItemModel();
    explicit controller(QWidget *parent = nullptr);
    ~controller();
    void updateTasks(QString name,QString memory,QString runTime);
    virtual void paintEvent(QPaintEvent *);
    virtual void keyPressEvent(QKeyEvent *event);
private:
    Ui::controller *ui;
private slots:
    void update();
};

#endif // CONTROLLER_H
