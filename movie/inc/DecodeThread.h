_Pragma("once")
#include"AVInfo.h"

class DecodeThread:public QThread
{
Q_OBJECT
public:
     DecodeThread();
     void OpenFile(const char *path);
     void DecodeVideo();
     void run();
     ~DecodeThread();
signals:
    void SendAVinfoSignal(AVInfo *);
private:
     AVFormatContext    *pFormatCtx;
     //AVStream *audio_stream,*video_stream;
     int audio_index,video_index;
     AVInfo *av_info;
};

class AudioThread:public QThread
{
    Q_OBJECT
public:
    double AudioClock();
private:
};
