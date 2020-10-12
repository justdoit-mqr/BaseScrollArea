#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
#include <QSettings>
#include <QScrollArea>
#include <QScrollBar>
#include <QLabel>
#include <QToolButton>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    //初始化滚动区域
    area = new BaseScrollArea(this);
    area->setWidgetResizable(true);//设置滚动区内部窗口自适应
    area->setWidget(ui->widget);//设置滚动区内部窗口
    connect(area->verticalScrollBar(),SIGNAL(valueChanged(int)),this,SLOT(valueChangedSlot(int)));

    //将滚动区域加入整体布局中
    ui->verticalLayout->addWidget(area);
}

Widget::~Widget()
{
    delete ui;
}

//测试垂直滚动条值的变化
void Widget::valueChangedSlot(int value)
{
    qDebug()<<"minimum:"<<area->verticalScrollBar()->minimum()
           <<"maximum:"<<area->verticalScrollBar()->maximum()
          <<"current value:"<<value;
}
