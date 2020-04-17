_Pragma("once")
extern "C"
{
#include "libavcodec/avcodec.h"
#include "libavformat/avformat.h"
#include "libswscale/swscale.h"
#include "libavdevice/avdevice.h"
#include "libavutil/imgutils.h"
#include "libswresample/swresample.h"
}
#include<QQueue>
#include<QThread>
#include<QMutex>
#include<QWaitCondition>
#include "MacroDefine.h"

    #include<QtDebug>
    #include<QThread>

#define QUEUE_PACKET_MAX_SIZE 500
struct Picture
{
  QImage *img;
  double pts;
};//AVPacketList
template<class T>
class Queue
{
public:

    QQueue<T>list;
    QMutex mutex;
  //  QMutex mutex2;
    QWaitCondition cond;
    QWaitCondition cond2;

};

class AVTime
{
public:
    double curTime;
    double TotalTime;
};

class AVInfo
{
public:
    AVFormatContext    *AvFormatCtx;
    AVCodecContext * AudioCodec;
    AVCodecContext * VideoCodec;

    Queue<AVPacket>videoq;
    Queue<AVPacket>audioq;
    Queue<Picture>pictureq;

   // unsigned char* audio_buf;
   // unsigned int audio_buf_size;
    template<class T>
    void PutQueueNode(Queue<T>&q,T node);
    template<class T>
    bool GetQueueNode(Queue<T>&q,T * val,int block=1,bool pop=true);
private:

};
template<class T>
void AVInfo::PutQueueNode(Queue<T> &q,T node)
{
    q.mutex.lock();

    if(q.list.size()>=QUEUE_PACKET_MAX_SIZE)
    {
       // qDebug()<<QThread::currentThread()<<":等待条件变量1";
        q.cond.wait(&q.mutex);
      //  qDebug()<<QThread::currentThread()<<":条件变量1已唤醒";
    }
    q.list.append(node);
    if(q.list.size()>0)
    {
        q.cond2.wakeAll();
       // qDebug()<<QThread::currentThread()<<":唤醒条件变量2";
    }
    qDebug()<<"Q Put SIZE:"<<q.list.size();
    q.mutex.unlock();
}
template<class T>
bool AVInfo::GetQueueNode(Queue<T>&q,T * val,int block,bool pop)
{
    q.mutex.lock();
    if(q.list.isEmpty()&&block)
    {
         //  qDebug()<<QThread::currentThread()<<":等待条件变量2";
           q.cond2.wait(&q.mutex) ;
         //  qDebug()<<QThread::currentThread()<<":条件变量2已唤醒";
    }
    else if(q.list.isEmpty())
    {
        q.mutex.unlock();
        return false;
    }
    T p=q.list.front();
    if(pop)
    {
        q.list.pop_front();
    }
    if(q.list.size()<QUEUE_PACKET_MAX_SIZE)
    {
       q.cond.wakeAll();
    //   qDebug()<<QThread::currentThread()<<":唤醒条件变量1";
    }
    qDebug()<<"Q Get SIZE:"<<q.list.size();
    q.mutex.unlock();
    *val = p;
    return true;
}
