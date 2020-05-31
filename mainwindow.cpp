#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "login_page.h"
#include "texteditor.h"
#include "snake_widget.h"
#include <QStackedWidget>
#include "Process_RAM.h"
#include "global.h"
#include "file_widget.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

//QStackedWidget * stackedwidget = new QStackedWidget;
void MainWindow::on_actionText_Editor_triggered()
{
    texteditor * editor = new texteditor(this);
//    editor->show();
//    stackedwidget->addWidget(editor);
    task->updateTasks("Text_editor","3","0");
    editor->show();
}

void MainWindow::on_actionSnake_triggered()
{   if (snakeRunning != true){
        snake_widget * snake = new snake_widget(this);
        snakeRunning = true;
        task->updateTasks("Snack","2","0");
        snake->show();
    }
}

void MainWindow::on_actionTask_triggered() {
    //controller * task = new controller(this);
    task->show();

    cout << "test" << endl;
}

void MainWindow::on_actionOpen_triggered() {
    file_widget *filewidget = new file_widget(this);
    filewidget->show();
}

void MainWindow::closeEvent(QCloseEvent *event) {
    for (int i = 0; i < 20; i++) {
        ana_ram[i].ram_used = 0;
    }
    event->accept();
}
