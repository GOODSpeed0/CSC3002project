#ifndef TASKCONTROLLER_H
#define TASKCONTROLLER_H
#include <QMainWindow>
#include <QWidget>
#include <QPaintEvent>
//const int MEM_BLOCK = 5;
//const int TASK_MARGIN = 10;
class taskcontroller : public QMainWindow
{
    Q_OBJECT
public:
    taskcontroller(QWidget *parent = nullptr);
    ~taskcontroller();
    virtual void paintEvent(QPaintEvent *);
};

#endif // TASKCONTROLLER_H
