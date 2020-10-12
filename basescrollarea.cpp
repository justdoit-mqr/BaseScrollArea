/*
 *@author:  缪庆瑞
 *@date:    2020.05.14
 *@brief:   基类滚动区域
 */
#include "basescrollarea.h"
#include <QDebug>

/*滚动区域滚动条默认样式*/
#define HORI_SCROLLBAR_STYLE "QScrollBar:horizontal{\
height:16px;margin:0px;background-color:transparent;}\
QScrollBar::handle:horizontal{\
border-radius:1px;margin:9px 1px 1px 1px;\
height:16px;background:#cfcfcf;}\
QScrollBar::add-line:horizontal,QScrollBar::sub-line:horizontal {\
background: none;}\
QScrollBar::add-page:horizontal,QScrollBar::sub-page:horizontal{\
background:none;}"
#define VER_SCROLLBAR_STYLE "QScrollBar:vertical{\
width:16px;margin:0px;background-color:transparent;}\
QScrollBar::handle:vertical{\
border-radius:1px;margin:1px 1px 1px 9px;\
width:16px;background:#cfcfcf;}\
QScrollBar::add-line:vertical,QScrollBar::sub-line:vertical {\
background:none;}\
QScrollBar::add-page:vertical,QScrollBar::sub-page:vertical{\
background:none;}"


BaseScrollArea::BaseScrollArea(QWidget *parent) : QScrollArea(parent)
{
    this->setFrameShape(QFrame::NoFrame);//滚动区域不显示边框
    this->setStyleSheet("BaseScrollArea{background-color:transparent;}");//设置背景透明
    horiScrollBar = this->horizontalScrollBar();
    verScrollBar = this->verticalScrollBar();
    horiScrollBar->setStyleSheet(HORI_SCROLLBAR_STYLE);
    verScrollBar->setStyleSheet(VER_SCROLLBAR_STYLE);
    //默认启用拖动功能
    setMoveEnabled(true);
    setMoveSensitivity();
}
/*
 *@brief:   设置非滚动条区域是否可以直接拖动
 *@author:  缪庆瑞
 *@date:    2020.05.14
 *@param:   moveEnabled:bool类型
 */
void BaseScrollArea::setMoveEnabled(bool moveEnabled)
{
    if(moveEnabled)
    {
        moveStart = false;
        this->installEventFilter(this);
    }
    else
    {
        this->removeEventFilter(this);
    }
}
/*
 *@brief:   设置移动灵敏度的相关参数
 *@author:  缪庆瑞
 *@date:    2020.05.14
 *@param:   offsetMinimum:按下首次移动的最小偏移量。该参数用来控制鼠标按下首次移动的灵敏度，越小
 * 越灵敏，但如果灵敏度过高可能会导致鼠标点击时因为触发移动事件而引起滚动区域产生微量的偏移
 *@param:   offsetFactor:移动偏移量系数。该参数控制鼠标按下移动时，滚动条的变化量，值越大移动越快。
 */
void BaseScrollArea::setMoveSensitivity(int offsetMinimum, int offsetFactor)
{
    this->moveOffsetMinimum = offsetMinimum;
    this->moveOffsetFactor = offsetFactor;
}
/*
 *@brief:   事件过滤处理函数
 *@author:  缪庆瑞
 *@date:    2020.05.14
 *@param:   obj:产生事件的对象
 *@param:   event:产生的事件
 *@return:  bool:表示事件是否继续向外传递
 */
bool BaseScrollArea::eventFilter(QObject *obj, QEvent *event)
{
    if(obj == this)
    {
        if(event->type() == QEvent::MouseMove)//鼠标移动
        {
            QMouseEvent *mouseEvent = (QMouseEvent*) event;
            if(mouseEvent->buttons()&Qt::LeftButton)
            {
                if(!moveStart)
                {
                    //左键按下后的首次移动
                    moveStart = true;
                    moveContinue = false;
                    mouseMovePoint = mouseEvent->globalPos();
                }
                else
                {
                    QPoint p = mouseEvent->globalPos();
                    int offsetx = p.x() - mouseMovePoint.x();
                    int offsety = p.y() - mouseMovePoint.y();
                    //首次移动的灵敏度控制
                    if(!moveContinue && (offsetx > -moveOffsetMinimum && offsetx < moveOffsetMinimum)
                            && (offsety > -moveOffsetMinimum && offsety < moveOffsetMinimum))
                    {
                        return QScrollArea::eventFilter(obj,event);
                    }
                    horiScrollBar->setValue(horiScrollBar->value() - offsetx*moveOffsetFactor);
                    verScrollBar->setValue(verScrollBar->value() - offsety*moveOffsetFactor);
                    moveContinue = true;
                    mouseMovePoint = p;
                }
            }
        }
        else if(event->type() == QEvent::MouseButtonRelease)//鼠标释放
        {
            moveStart = false;
        }
    }
    return QScrollArea::eventFilter(obj,event);
}
