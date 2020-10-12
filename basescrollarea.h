/*
 *@author:  缪庆瑞
 *@date:    2020.05.14
 *@brief:   基类滚动区域
 * 1.该类继承自QScrollArea，父类已经集成了关于滚动区可能用到的大部分功能接口，包括水平和垂直滚动条，
 * 所以通常情况下调用父类的接口基本能实现滚动区域的相关需求。
 * 2.该类重写了eventFilter()事件过滤处理函数，并提供接口可选择在自身上安装事件过滤器。事件过滤处理函数
 * 内部监听鼠标移动和释放事件，进而实现对非滚动条区域的拖动效果。
 * 注:该类通过事件过滤器监听自身的鼠标事件实现对非滚动条区域的拖动行为，所以需要确保用户产生的鼠标
 * 事件最终能传递到该组件上。例如滚动区内部窗口上布局一个QPushButton按钮和QLabel标签，当鼠标点击
 * 按钮时，鼠标事件会被按钮本身接收处理不会向上层传递，而QLabel默认则会忽视鼠标事件向上传递。不过
 * 如果QLabel设置了富文本显示，则需要设置setTextInteractionFlags(Qt::NoTextInteraction)才能确保鼠标事件
 * 向上传递，对于QPushButton按钮要想鼠标事件也能向上层传递，可以派生该类重写鼠标事件处理函数，调用
 * ignore()忽略事件即可。
 * 参考资料：https://blog.csdn.net/wjgwrr/article/details/72852021    Wang Jianguo
 *
 */
#ifndef BASESCROLLAREA_H
#define BASESCROLLAREA_H

#include <QScrollArea>
#include <QScrollBar>
#include <QMouseEvent>

class BaseScrollArea : public QScrollArea
{
    Q_OBJECT
public:
    explicit BaseScrollArea(QWidget *parent = 0);

    //设置/获取非滚动条区域是否可以直接拖动的状态
    void setMoveEnabled(bool moveEnabled);
    bool getMoveEnabled(){return moveEnabled;}
    //设置移动灵敏度的相关参数
    void setMoveSensitivity(int offsetMinimum=10,int offsetFactor=3);

protected:
      virtual bool eventFilter(QObject *obj, QEvent *event);

private:
    /*鼠标拖动相关参数*/
    bool moveEnabled;
    bool moveStart;
    bool moveContinue;
    QPoint mouseMovePoint;
    int moveOffsetMinimum;
    int moveOffsetFactor;
    //滚动条
    QScrollBar *horiScrollBar;
    QScrollBar *verScrollBar;

signals:

public slots:
};

#endif // BASESCROLLAREA_H
