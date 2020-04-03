#include "VideoThread.h"
#include<QtDebug>
#include<QImage>
void VideoThread::run()
{
    while(1)
    {

    }
}
void VideoThread::StartDecodePacket(AVInfo *info)
{
    AVPacket *pkt;
    unsigned char * out_buffer;
    AVFrame *frame = av_frame_alloc();
    AVFrame * convert_frame = av_frame_alloc();
    SwsContext * img_convert_ctx;
    int size = av_image_get_buffer_size(AV_PIX_FMT_RGB32,info->VideoCodec->width,info->VideoCodec->height,1);
    img_convert_ctx = sws_getContext(info->VideoCodec->width, info->VideoCodec->height, info->VideoCodec->pix_fmt,
               info->VideoCodec->width, info->VideoCodec->height, AV_PIX_FMT_RGB32, SWS_BICUBIC, NULL, NULL, NULL);
    int ret;
    while(1)
    {
        //pkt=info->GetQueueNode(info->videoq);
        if(!pkt)
        {
            qDebug()<<"视频包队列为空，退出解码帧";
            break;
        }
        if(avcodec_decode_video2(info->VideoCodec,frame,&ret,pkt)<0)
        {
            qDebug()<<"-7:VideoThread,解码帧失败";
        }
        if(ret)
        {
            out_buffer = (unsigned char *)av_malloc(size);
            av_image_fill_arrays(convert_frame->data,convert_frame->linesize,out_buffer,AV_PIX_FMT_RGB32,
                                 info->VideoCodec->width, info->VideoCodec->height, 1);
            sws_scale(img_convert_ctx, (const unsigned char* const*)frame->data, frame->linesize, 0,
                      info->VideoCodec->height,convert_frame->data, convert_frame->linesize);
            QImage* img = new QImage((uchar*)out_buffer,info->VideoCodec->width,info->VideoCodec->height,QImage::Format_RGB32);
            Picture *pic = new Picture;
            pic->img = img;
            pic->pts = frame->pts;

         //   info->PutQueueNode(info->pictureq,pic);
        }
    }
}
