#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "basescrollarea.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private:
    Ui::Widget *ui;
    BaseScrollArea *area;

private slots:
    void valueChangedSlot(int value);//滚动区滚动条值改变响应槽
};

#endif // WIDGET_H
