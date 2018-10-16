#include "widget.h"
#include "ui_widget.h"
#include <QRegExp>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setWindowTitle("正则");

    connect(this->ui->plainTextEdit_content,&QPlainTextEdit::textChanged,[=](){
        this->matchRegexp();
    });
    connect(this->ui->plainTextEdit_regex,&QPlainTextEdit::textChanged,[=](){
        this->matchRegexp();
    });
}

Widget::~Widget()
{
    delete ui;
}

void Widget::matchRegexp()
{
    //Regular expression
    QString regText = this->ui->plainTextEdit_regex->toPlainText();
    QString content = this->ui->plainTextEdit_content->toPlainText();

    if(regText.isEmpty()&&content.isEmpty())
    {
        this->ui->label_result->setText("");
        return;
    }

    QRegExp reg(regText);
    if(reg.exactMatch(content))
    {
        this->ui->label_result->setText(
                    "<div style=\"color:green\">完全匹配</div>"
                    );
    }
    else if(reg.indexIn(content)>=0)
    {
        this->ui->label_result->setText(
                    "<div style=\"color:yellow\">部分匹配</div>"
                    );
    }
    else
    {
        this->ui->label_result->setText(
                    "<div style=\"color:red\">匹配失败</div>"
                    );
    }
}
