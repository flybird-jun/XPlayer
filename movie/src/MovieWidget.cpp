#include "MovieWidget.h"
#include <QEvent>
#include <QTimer>
#include <QPainter>
#include <QtDebug>
#include <QTime>
MovieWidget::MovieWidget(QWidget *parent):QWidget(parent)
{

}
MovieWidget::~MovieWidget()
{

}
void MovieWidget::paintEvent(QPaintEvent*event)
{
    QPainter painter(this);
    if(img)
    {
        painter.drawImage(QPoint(0,0),*img);
        //painter.drawImage(QRect(0,0,img->width(),img->height()),*img);
    }
}
void MovieWidget::GetAVinfoSlots(AVInfo *info)
{
    av_info = info;
    GetPicture();
}
double MovieWidget::GetVideoClock()
{
    return video_clock;
    //av_q2d(av_info->VideoCodec->time_base);
}
void MovieWidget::GetPicture()
{
    double delay;
    Picture ptr;
    Picture ptr2;

    if(pause)
    {
        return;
    }



    bool ret=av_info->GetQueueNode(av_info->pictureq,&ptr,0);
    bool ret2 = av_info->GetQueueNode(av_info->pictureq,&ptr2,0,false);
    if(ret)
    {
       qDebug()<<QThread::currentThread()<<"取出图片包";
        if(img)
        {
            delete img->bits();
            delete img;
        }
        img = ptr.img;
        if(ret2)
        {
            delay = (ptr2.pts-ptr.pts)*av_q2d(av_info->VideoCodec->time_base);
        }
        else
        {
            delay = av_q2d(av_info->VideoCodec->time_base);
        }
        repaint();
    }
    else
    {
        delay = av_q2d(av_info->VideoCodec->time_base);
        qDebug()<<"未读取到图片包，进行显示";
    }
    if(delay<0)
    {
        delay = 0;
    }
    video_clock+=delay;
    delay = delay*1000;//
    qDebug()<<"delay:"<<delay;
    QTimer::singleShot(delay, this,&MovieWidget::GetPicture);
}
/*************************************************************************************************************/
/*
 * 处理按键的函数
*/
void MovieWidget::Pause()
{
    pause = !pause;
    if(!pause)
    {
         GetPicture();
    }
}
