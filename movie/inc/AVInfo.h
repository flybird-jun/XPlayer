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
#define QUEUE_PACKET_MAX_SIZE 500
struct Picture
{
  QImage *img;
  double pts;
};//AVPacketList
class AVInfo
{
public:
    AVFormatContext    *AvFormatCtx;
    AVCodecContext * AudioCodec;
    AVCodecContext * VideoCodec;

    QQueue<AVPacket *>videoq;
    QQueue<AVPacket *>audioq;
    QQueue<Picture *>pictureq;
   // unsigned char* audio_buf;
   // unsigned int audio_buf_size;
    template<class T>
    void PutQueueNode(QQueue<T>q,T node);
    template<class T>
    T GetQueueNode(QQueue<T>q);
    /*
    void QueuePutVideoPacket(AVPacket *pkt);
    AVPacket* QueueGetVideoPacket();
    void QueuePutAudioPacket(AVPacket *pkt);
    AVPacket* QueueGetAudioPacket();*/
    //static AVInfo& GetObject();
private:


};
