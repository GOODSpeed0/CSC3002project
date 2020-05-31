#ifndef MineSweeper_H
#define MineSweeper_H

#include <QMainWindow>
#include <QDebug>
#include <QPainter>
#include <QPixmap>
#include <QMouseEvent>
#include <block.h>
#include <QTimer>
#include <QMessageBox>
#include <qmessagebox.h>
#include <dialog.h>
#include "global.h"

//定义常量
#define BLOCK_LENGTH 21
#define BLOCK_HEIGH 21
#define ELENUM_LENGHT 20
#define EXPRESSION_LENGHT 24
#define EXPRESSION_HEIGH 24
#define TTILE_BEGIN 23
#define TITILE_HEIGH  (TTILE_BEGIN+40)
#define PRIMARY_LENGTH  189
#define MIDDLE_LENGTH   336
#define TOP_LENGTH      630

namespace Ui {
class MineSweeper;
}
class MineSweeper : public QMainWindow
{
    Q_OBJECT

public:
    explicit MineSweeper(QWidget *parent = 0);
    ~MineSweeper();
    void closeEvent(QCloseEvent *event);

private:
    Ui::MineSweeper *ui;
    QTimer * runtime_Mine;
    Dialog * useDefineWindows;
protected:
    virtual void paintEvent(QPaintEvent *event);
    virtual void mousePressEvent(QMouseEvent *event);
private slots:
    void on_secondadd();

    void on_actionPrimary_triggered();
    void on_actionMiddle_triggered();
    void on_actionSenior_triggered();
    void on_actionQuit_triggered();
    void on_actionUser_defined_triggered();
    void on_actionHelp_triggered();
    void on_actionAbout_triggered();
    void on_actionHow_to_play_triggered();

};

void showblock(int x,int y);
int iswin();
void restart(int row,int col,int boolnum);
void painttitle(QPainter * painter);
void paintboom(QPainter * painter);
void createinterface();

#endif // MineSweeper_H
