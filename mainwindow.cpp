#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "login_page.h"
#include "texteditor.h"
#include "snake_widget.h"
#include <QStackedWidget>
#include "Process_RAM.h"
#include "global.h"
#include "taskcontroller.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    systemClock.start();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionText_Editor_triggered()
{
    texteditor * editor = new texteditor(this);
    task->updateTasks("Text_editor","1","0");
    process_id_Text=task->taskNumber-1;
    editor->show();
}

void MainWindow::on_actionSnake_triggered()
{
    snake_widget * snake =  new snake_widget(this);
    snakeRunning = true;
    task->updateTasks("Snack","2","0");
    process_id_Snack=task->taskNumber-1;
    snake->show();
}

void MainWindow::on_actionTask_triggered() {
    task->show();
}
void MainWindow::on_actionClock_triggered(){
    if (!hasClock){
        task->updateTasks("Clock","2","0");
        process_id_Clock=task->taskNumber-1;
        clockProcess = Process_APP(ana_ram);
        systemClock.show();
        hasClock=true;
    }
    else return;
}
void MainWindow::on_actionMinesweeper_triggered(){
    MineSweeper * minesweeper=new MineSweeper(this);
    minesweeper->show();
    mineSweeperProcess=Process_APP(ana_ram);
    task->updateTasks("MineSweeper","2","0");
    process_id_Mine=task->taskNumber-1;
}
