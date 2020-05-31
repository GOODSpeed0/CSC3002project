#include "file_widget.h"
#include "ui_file_widget.h"
#include "texteditor.h"
#include <QInputDialog>
file_widget::file_widget(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::file_widget)
{
    ui->setupUi(this);
}

file_widget::~file_widget()
{
    delete ui;
}

void file_widget::on_CreateFile_clicked() {
    texteditor *editorCreate = new texteditor;
    editorCreate->show();
}

void file_widget::on_OpenFile_clicked() {
    texteditor *editorOpen = new texteditor;
    editorOpen->show();
}

void file_widget::on_ShowFiles_clicked() {
    texteditor *editorCreate = new texteditor;
    editorCreate->show();
}
