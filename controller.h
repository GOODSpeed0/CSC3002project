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
#include "Rom_system.h"
const int MEM_MARGIN = 50;
const int MEM_BLOCK = 20;
extern tm nowTime;
using namespace std;
namespace Ui {
class controller;
}

class controller : public QMainWindow
{
    Q_OBJECT

public:
    vector <tm> startTimes;
    int taskNumber=0;
    QStandardItemModel *model=new QStandardItemModel();
    explicit controller(QWidget *parent = nullptr);
    ~controller();
    void updateTasks(QString name,QString memory,QString runTime);
    void deleteProcess(int process_id);
    virtual void paintEvent(QPaintEvent *);
private:
    Ui::controller *ui;

private slots:
    void updateTime();
};

#endif // CONTROLLER_H
