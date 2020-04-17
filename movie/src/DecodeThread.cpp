#include "DecodeThread.h"
#include <QtDebug>
DecodeThread::DecodeThread()
{
    av_info = new AVInfo();
    vthread = new QThread();
    athread = new QThread();
    videoThreadObj = new VideoThread();
    videoThreadObj->moveToThread(vthread);
    vthread->start();
    connect(this,&DecodeThread::StartVideoDecodeSingal,videoThreadObj,&VideoThread::StartDecodePacketSlot);
}
void DecodeThread::run()
{
    av_register_all();
    DecodeVideo();
}
void DecodeThread::OpenFile(const char *filepath)
{

    pFormatCtx = avformat_alloc_context();
    av_info->AvFormatCtx = pFormatCtx;
    if (avformat_open_input(&pFormatCtx, filepath, NULL, NULL) != 0)
    {
        qDebug()<<"-1:打开文件失败";
        return;
    }
    if (avformat_find_stream_info(pFormatCtx, NULL) < 0)
    {
        qDebug()<<"-2:没找到音视频流";
        return ;
    }
    for (unsigned int i = 0; i < pFormatCtx->nb_streams; i++)
     {
          if (pFormatCtx->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_VIDEO)
          {
             video_index = i;
             // video_stream = pFormatCtx->streams[i];
          }
          else if(pFormatCtx->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_AUDIO)
          {
            //  audio_stream = pFormatCtx->streams[i];
              audio_index = i;
          }
     }
    av_info->VideoCodec = pFormatCtx->streams[video_index]->codec;
    emit SendAVinfoSignal(av_info);
    emit StartVideoDecodeSingal(av_info);
}
void DecodeThread::DecodeVideo()
{
    AVCodec * video_codec,*audio_codec;
    AVPacket pkt, *packet=&pkt;
    video_codec=avcodec_find_decoder(pFormatCtx->streams[video_index]->codec->codec_id);
    if(!video_codec)
    {
        qDebug()<<"-3:没找到视频解码器";
        return;
    }
    audio_codec = avcodec_find_decoder(pFormatCtx->streams[audio_index]->codec->codec_id);
    if(!audio_codec)
    {
        qDebug()<<"-4:没找到音频解码器";
    }


    if(avcodec_open2(pFormatCtx->streams[video_index]->codec, video_codec, NULL)<0)
    {
        qDebug()<<Tr("-5:打开视频解码器失败");
    }
    if(avcodec_open2(pFormatCtx->streams[audio_index]->codec,audio_codec,NULL))
    {
        qDebug()<<Tr("-6:打开音频解码器失败");
    }

    av_info->VideoCodec = pFormatCtx->streams[video_index]->codec;
    av_info->AudioCodec = pFormatCtx->streams[audio_index]->codec;


    av_init_packet(packet);
    while(av_read_frame(pFormatCtx, packet)==0)
    {
        if(packet->stream_index==audio_index)
        {
         //  av_info->PutQueueNode(av_info->audioq,pkt);

        }
        else if(packet->stream_index==video_index)
        {
           qDebug()<<QThread::currentThread()<<":加入视频包";
           av_info->PutQueueNode(av_info->videoq,pkt);
        }
    }
    //emit EndVideoDecodeSignal();
}
DecodeThread::~DecodeThread()
{
    if(av_info)
    {
        delete av_info;
        av_info = nullptr;
    }
}
