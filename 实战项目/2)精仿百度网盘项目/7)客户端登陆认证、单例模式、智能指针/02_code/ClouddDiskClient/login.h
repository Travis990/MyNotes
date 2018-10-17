#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>

namespace Ui {
class Login;
}

class Login : public QWidget
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = 0);
    ~Login();

private slots:

    void on_toolButton_options_clicked();

    void on_pushButton_goto_register_clicked();

    void on_pushButton_back_to_login_clicked();

    void on_pushButton_back_to_login_2_clicked();

    void on_pushButton_register_clicked();

private:
    Ui::Login *ui;
};

#endif // LOGIN_H
