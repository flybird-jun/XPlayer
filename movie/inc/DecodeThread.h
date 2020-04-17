_Pragma("once")
#include"AVInfo.h"
#include <QThread>
#include "VideoThread.h"
class DecodeThread:public QThread
{
Q_OBJECT
public:
     DecodeThread();
     void OpenFile(const char *path);
     void DecodeVideo();
     void run() override;
     ~DecodeThread();
signals:
    void SendAVinfoSignal(AVInfo *);
    void StartVideoDecodeSingal(AVInfo *);
    void AVCurrentTime();
    //void EndVideoDecodeSignal();
private:
     AVFormatContext    *pFormatCtx;
     //AVStream *audio_stream,*video_stream;
     int audio_index,video_index;
     AVInfo *av_info;
     QThread *vthread;
     QThread *athread;
     VideoThread *videoThreadObj;
};

class AudioThread:public QThread
{
    Q_OBJECT
public:
    double AudioClock();
private:
};
