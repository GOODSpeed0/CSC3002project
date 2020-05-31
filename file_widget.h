#ifndef FILE_WIDGET_H
#define FILE_WIDGET_H

#include <QMainWindow>

namespace Ui {
class file_widget;
}

class file_widget : public QMainWindow
{
    Q_OBJECT

public:
    explicit file_widget(QWidget *parent = nullptr);
    ~file_widget();

private slots:
    void on_CreateFile_clicked();
    void on_OpenFile_clicked();
    void on_ShowFiles_clicked();

private:
    Ui::file_widget *ui;
};

#endif // FILE_WIDGET_H
