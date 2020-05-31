#ifndef SNAKE_WIDGET_H
#define SNAKE_WIDGET_H

#include <QWidget>
#include <QPaintEvent>
#include <QKeyEvent>
#include <QCloseEvent>
#include "measure_time.h"
#include <QMainWindow>
#include "Process_RAM.h"
#include "global.h"
const int BLOCK_SIZE = 25; // the length of each block
const int MARGIN = 5; // margin of the playground
const int AREA_ROW = 15; // the nember of the rows
const int AREA_COL = 15; // the number of the columns
const int TIME_INTERVAL = 500; // the time interval of the movement, unit is ms

enum Direction {
    UP,
    DOWN,
    LEFT,
    RIGHT
};


class snake_widget : public QMainWindow
{
    Q_OBJECT
public:
    snake_widget(QWidget *parent = nullptr);
    ~snake_widget();
    virtual void paintEvent(QPaintEvent *);
    virtual void keyPressEvent(QKeyEvent *event);
    virtual void closeEvent(QCloseEvent *event);


    void InitGame();
    void PauseGame();
    void GameOver();
    bool IsGameOver();
    void GenerateFood();
//    void snakeExist();
    void StoreData(int address);
//    static Process_APP snakeProcess;
private slots:
    void SnakeGrow();
private:
    QTimer *gameTimer;
    bool isPause;
    QPoint foodPoint;
    QList<QPoint> snake;
    Direction dir;
    int score;
    Tools::Time::AlgoTimeS runTime;
    int elasped;


};

#endif // SNAKE_WIDGET_H
