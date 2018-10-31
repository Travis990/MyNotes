#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include "mainwindow.h"

namespace Ui {
class Login;
}

class Login : public QWidget
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = 0);
    ~Login();

protected:
    void paintEvent(QPaintEvent *event);
private slots:

    void on_toolButton_options_clicked();

    void on_pushButton_goto_register_clicked();

    void on_pushButton_back_to_login_clicked();

    void on_pushButton_back_to_login_2_clicked();

    void on_pushButton_register_clicked();

    void on_pushButton_2_clicked();

    void loginSucc();

    void on_pushButton_confirm_option_clicked();

private:
    Ui::Login *ui;
};

#endif // LOGIN_H
