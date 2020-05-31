#include "login_page.h"
#include "ui_login_page.h"
#include "login_system.h"
#include "mainwindow.h"
#include <QApplication>
#include <QDebug>
#include "global.h"
//#include <QMessageBox>

LoginPage::LoginPage(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LoginPage)
{
    ui->setupUi(this);
}

LoginPage::~LoginPage()
{
    delete ui;
}


void LoginPage::on_actionPower_triggered()
{
    QApplication::quit();
}

void LoginPage::on_loginButton_clicked()
{
    // Declare new LoginSystem and User instance
    LoginSystem system;
    MainWindow * window = new MainWindow;
    User *user = new User;
    for (int i = 0; i < 20; i++) {
        ana_ram[i].ram_used = 0;
    }
    user->username = ui->usernameEdit->text().toStdString();
    user->password = ui->passwordEdit->text().toStdString();
    if (system.SystemEnter(user->username, user->password) == true) {
        window->show();
    }
}

void LoginPage::on_registerButton_clicked()
{
    // Declare new LoginSystem and User instance
    LoginSystem loginsystem;
    MainWindow * window = new MainWindow;
    User *user = new User;
    for (int i = 0; i < 20; i++) {
        ana_ram[i].ram_used = 0;
    }
    user->username = ui->usernameEdit->text().toStdString();
    user->password = ui->passwordEdit->text().toStdString();
    if (loginsystem.SystemRegister(user->username, user->password) == true) {
        window->show();
    }
}

void LoginPage::closeEvent(QCloseEvent *event) {
    for (int i = 0; i < 20; i++) {
        ana_ram[i].ram_used = 0;
    }
    event->accept();
}

