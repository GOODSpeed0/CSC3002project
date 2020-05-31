#include "snake_widget.h"
#include <QPainter>
#include <QTimer>
#include <QString>
#include <QMessageBox>
#include <time.h>
#include <QMainWindow>
#include "global.h"
#include "F_code_library.h"
#include "mainwindow.h"
//Process_APP snake_widget::snakeProcess = Process_APP(ana_ram);
snake_widget::snake_widget(QWidget *parent)  : QMainWindow(parent) {
    resize(MARGIN*4 + (AREA_COL + 3)*BLOCK_SIZE, MARGIN*2 + AREA_ROW*BLOCK_SIZE);
    InitGame();
}
snake_widget::~snake_widget(){
    GameOver();
}

void snake_widget::InitGame() {
    for(int i = 4; i >= 0; i--) {
        snake.push_back(QPoint(i,0));
    }
    dir = RIGHT;
    srand(time(0));
    GenerateFood();
    score = 0;
    isPause = false;
    runTime.start();
    gameTimer = new QTimer(this);
    connect(gameTimer, SIGNAL(timeout()),this,SLOT(SnakeGrow()));
    gameTimer->start(TIME_INTERVAL);
    snakeProcess = Process_APP(ana_ram);
    int startaddress = snakeProcess.address;
    StoreData(startaddress);
}

void snake_widget::GenerateFood() {
    foodPoint.setX(rand() % AREA_COL);
    foodPoint.setY(rand() % AREA_ROW);
    if (snake.contains(foodPoint)) {
        GenerateFood();
    }
}

void snake_widget::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    painter.setBrush(QColor(219, 207, 202));
    painter.setPen(QColor(13, 12, 12));
    painter.drawRect(MARGIN, MARGIN, AREA_COL * BLOCK_SIZE, AREA_ROW * BLOCK_SIZE);
    //draw playground
    painter.setBrush(QColor(89, 69,61));
    painter.setPen(QColor(13, 12, 12));
    for (int i = 0; i < snake.size(); i++) {
        painter.drawRect(MARGIN + snake[i].x() * BLOCK_SIZE, MARGIN + snake[i].y() * BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE);
    }
    // draw snake
//    painter.setPen(QColor(13, 12, 12));
    painter.setBrush(QColor(166, 137, 124));
    painter.drawEllipse(MARGIN + foodPoint.x() * BLOCK_SIZE, MARGIN + foodPoint.y() * BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE);
    // draw food
    painter.setPen(Qt::black);
    painter.setFont(QFont("Arial",15));
    painter.drawText(MARGIN * 3 + AREA_COL *  BLOCK_SIZE, MARGIN + 2 * BLOCK_SIZE, "Score: " + QString::number(score));
    // display score
}


void snake_widget::keyPressEvent(QKeyEvent *event) {
    switch (event->key()) {
    case Qt::Key_Up:
        if (dir != DOWN) {
            dir = UP;
        } break;
    case Qt::Key_Down:
        if (dir != UP) {
            dir = DOWN;
        } break;
    case Qt::Key_Right:
        if (dir != LEFT) {
            dir = RIGHT;
        } break;
    case Qt::Key_Left:
        if (dir != RIGHT) {
            dir = LEFT;
        } break;
    case Qt::Key_P:
        PauseGame();
        break;
    case Qt::Key_E:
        GameOver();
        break;
    default:
        break;
    }
}

bool snake_widget::IsGameOver() {
    int x = snake.front().x();
    int y = snake.front().y();
    if (x < 0 || x == AREA_COL || y < 0 || y == AREA_ROW) {
        return true;
    }
    for (int i = 3; i < snake.size(); i++) {
        if (snake[i] == snake.front()) {
            return true;
        }
    }
    return false;
}

void snake_widget::SnakeGrow() {
    int x = snake.front().x();
    int y = snake.front().y();
    switch (dir) {
    case UP:
        snake.push_front(QPoint(x, y - 1));
        break;
    case DOWN:
        snake.push_front(QPoint(x, y + 1));
        break;
    case LEFT:
        snake.push_front(QPoint(x - 1, y));
        break;
    case RIGHT:
        snake.push_front(QPoint(x + 1, y));
        break;
    }
    if (x == foodPoint.x() && y == foodPoint.y()) {
        score += 1;
        GenerateFood();
    } else {
        snake.pop_back();
    }
    if (IsGameOver()) {
        GameOver();
        return;
    }
    update();
}

void snake_widget::GameOver() {
    gameTimer -> stop();
    elasped = runTime.elapsed();

//    snakeProcess.kill_Process_APP(ana_ram);
    QMessageBox::information(this, "FAILED",
                             "GAME OVER! \n \nRUNNING TIME: " + QString::number(elasped) + " SECONDS.\n" + "Do you want to store your data ?" ,
                             QMessageBox::Yes | QMessageBox::No, QMessageBox::No);

}

void snake_widget::PauseGame() {
    if (!isPause) {
        isPause = !isPause;
        gameTimer -> stop();
    } else {
        isPause = !isPause;
        gameTimer -> start(TIME_INTERVAL);
    }
    system_report(ana_ram);
    cout << show_RAM(ana_ram) << endl;

}

void snake_widget::StoreData(int address) {
    int startadress = address;
    RAM firstPage = ana_ram[startadress];
    RAM secondPage = ana_ram[startadress + 1];
    for (int i = 0;i < 1024; i += 2) {
        change_byte_by_num(firstPage.contents[i],elasped);
        change_byte_by_num(firstPage.contents[i + 1], score);
    }
}

void snake_widget::closeEvent(QCloseEvent *event) {
    if (!IsGameOver()) {
        GameOver();
    }
    snakeProcess.kill_Process_APP(ana_ram);
//    MainWindow::task
    event->accept();
}





