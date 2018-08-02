#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    //添加头部信息
    ui->treeWidget->setHeaderLabels(QStringList()<<"英雄"<<"简介");
    //添加根节点
    QTreeWidgetItem *item1 = new QTreeWidgetItem(QStringList()<<"力量");
    QTreeWidgetItem *item2 = new QTreeWidgetItem(QStringList()<<"敏捷");
    QTreeWidgetItem *item3 = new QTreeWidgetItem(QStringList()<<"智力");
    ui->treeWidget->addTopLevelItem(item1);
    ui->treeWidget->addTopLevelItem(item2);
    ui->treeWidget->addTopLevelItem(item3);

    //添加子节点到根节点上
    QStringList heroL1,heroL2,heroM1,heroM2,heroZ1,heroZ2;
    heroL1 << "刚背猪" << "前排坦克，能在吸收伤害的同时造成可观的范围输出";
    heroL2 << "船长" << "前排坦克，能肉能输出能控场的全能英雄";

    heroM1 << "月骑" << "中排物理输出，可以使用分裂利刃攻击多个目标";
    heroM2 << "小鱼人" << "前排战士，擅长偷取敌人的属性来增强自身战力";

    heroZ1 << "死灵法师" << "前排法师坦克，魔法抗性较高，拥有治疗技能";
    heroZ2 << "巫医" << "后排辅助法师，可以使用奇特的巫术诅咒敌人与治疗队友";

    item1->addChild(new QTreeWidgetItem(heroL1));
    item1->addChild(new QTreeWidgetItem(heroL2));
    item2->addChild(new QTreeWidgetItem(heroM1));
    item2->addChild(new QTreeWidgetItem(heroM2));
    item3->addChild(new QTreeWidgetItem(heroZ1));
    item3->addChild(new QTreeWidgetItem(heroZ2));
}

Widget::~Widget()
{
    delete ui;
}
