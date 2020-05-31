#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include <QCloseEvent>
#include "Process_RAM.h"
#include "F_code_library.h"
#include <QTimer>
#include"controller.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    controller * task = new controller(this);
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    virtual void closeEvent(QCloseEvent *event);
private slots:
    void on_actionText_Editor_triggered();
    void on_actionSnake_triggered();
    void on_actionTask_triggered();
    void on_actionOpen_triggered();

//    void snake_close();
private:
    Ui::MainWindow *ui;
    QTimer *systemTimer;
    bool snakeRunning;
//    QStackedWidget * stackwidget;
};
#endif // MAINWINDOW_H
