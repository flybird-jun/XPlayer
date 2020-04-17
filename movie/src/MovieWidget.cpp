#include "MovieWidget.h"
#include <QEvent>
#include <QTimer>
#include <QPainter>
#include <QtDebug>
#include <QTime>
#include <QDir>
#include "AVStreamSeperate.h"
MovieWidget::MovieWidget(QWidget *parent):QWidget(parent)
{

}
MovieWidget::~MovieWidget()
{
    if(movieThread)
    {
        movieThread->terminate();
        movieThread->wait();
        delete movieThread;
    }
}
/******************************************************************************************/
/*
 * 供mainwindow调用接口
*/
void MovieWidget::OpenAV(char *path)
{
    if(path==nullptr)
    {
        return;
    }
    if(movieThread)
    {
        movieThread->terminate();
        movieThread->wait();
    }

    file_path=path;
    //QStringList str = filePath.split("/");
    QRegExp reg("(.*[\\\\])(.*)\\.([^\\.]*)");
    reg.indexIn(file_path);
    qDebug()<<"path:"<<path;
    file_dir = reg.cap(1);
    file_name = reg.cap(2);
    file_suffix = reg.cap(3);
    qDebug()<<"file dir:"<<file_dir.toStdString().c_str();
    qDebug()<<"file name:"<<file_name;
    qDebug()<<"file suffix"<<file_suffix;
/*
    movieThread = new DecodeThread();
    connect(movieThread,&DecodeThread::SendAVinfoSignal,this,&MovieWidget::GetAVinfoSlots);
    movieThread->OpenFile(path);
    movieThread->start();*/
}
/******************************************************************************************/
/*
 * 视频解码相关
*/
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
 * 辅助函数
*/

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
void MovieWidget::SeparateAVCodeStream()
{
    QDir dir(file_dir);
    if(!dir.exists(file_name))
    {
        dir.mkpath(file_name);
    }
    dir.cd(file_name);
    QString AVCodeStreamDir = dir.path();
    QString audioFile = AVCodeStreamDir+"/"+file_name+".aac";
    QString videoFile = AVCodeStreamDir+"/"+file_name+".h264";
    qDebug()<<"file_path"<<file_path;
    qDebug()<<"file_path str"<<file_path.toStdString().c_str();

    AVStreamSeperate *sthread = new AVStreamSeperate(file_path.toStdString().c_str(),
                                                     const_cast<char *>(audioFile.toStdString().c_str()),
                                                     const_cast<char *>(videoFile.toStdString().c_str()));
    sthread->start();
    //sthread->run();

}
