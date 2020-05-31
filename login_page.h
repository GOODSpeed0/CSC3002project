#ifndef LoginPage_H
#define LoginPage_H
#include "F_code_library.h"
#include <QMainWindow>
#include <QCloseEvent>
namespace Ui {
class LoginPage;
}

class LoginPage : public QMainWindow
{
    Q_OBJECT

public:
    explicit LoginPage(QWidget *parent = nullptr);
    ~LoginPage();
    virtual void closeEvent(QCloseEvent *event);
//    static vector<RAM> ana_ram;
private slots:

    void on_actionPower_triggered();

    void on_loginButton_clicked();

    void on_registerButton_clicked();

private:
    Ui::LoginPage *ui;
};

#endif // LoginPage_H
