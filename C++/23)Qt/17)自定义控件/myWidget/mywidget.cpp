#include "mywidget.h"
#include "ui_mywidget.h"

myWidget::myWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::myWidget)
{
    ui->setupUi(this);
    //设置滚桥和计数器的数值范围
    ui->horizontalSlider->setRange(0,100);
    ui->spinBox->setRange(0,100);

    //设计移动滚桥计数器的数值跟着变化
    connect(ui->horizontalSlider,&QSlider::valueChanged,[=](int value){
        //设定计数器的数值
        ui->spinBox->setValue(value);
    });

    //设计计数器的数值变化滚桥跟随
    connect(ui->spinBox,
            static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),
            ui->horizontalSlider,
            &QSlider::setValue
            );
}

myWidget::~myWidget()
{
    delete ui;
}

//返回自定义控件的值
int myWidget::getVal()
{
    return ui->spinBox->value();
}

//设置自定义控件的值
void myWidget::setVal(int val)
{
    ui->spinBox->setValue(val);
}
