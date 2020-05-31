#include "taskcontroller.h"
#include <iostream>
#include <string>
#include <QMainWindow>
#include <QWidget>
#include <QMessageBox>
#include <QPainter>
#include "F_code_library.h"
#include "global.h"

using namespace std;
taskcontroller::taskcontroller(QWidget *parent) : QMainWindow(parent)
{
//    resize(TASK_MARGIN * 50, TASK_MARGIN * 50);
}

taskcontroller::~taskcontroller() {

}

void taskcontroller::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    painter.setBrush(QColor(219, 207, 202));
    painter.setPen(QColor(13, 12, 12));
    painter.drawRect(5,5,200,20);
    painter.drawLine(5, 15, 205, 15);
    for (int i = 0; i < 20; i++) {
        painter.drawLine((5 + 10*i),5,(5 + 10*i),25);
    }
    string s = show_RAM(ana_ram);
    for (int i = 0; i < 20; i++) {
        int used = stoi(s.substr(i,1));
        if (used == 1 && used <= 9) {
            painter.setBrush(QColor(13, 12, 12));
            painter.drawRect((5 + 10*i),5,10,10);

        }
        if (used == 1 && used > 9) {
            painter.setBrush(QColor(13, 12, 12));
            painter.drawRect((5 + 10*i),5,10,10);
        }
    }


}
