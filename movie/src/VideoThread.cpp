#include "VideoThread.h"
#include<QtDebug>
#include<QImage>
void VideoThread::StartDecodePacketSlot(AVInfo *info)
{
    AVPacket packet,*pkt=&packet;

    AVFrame *frame = av_frame_alloc();
    AVFrame * convert_frame = av_frame_alloc();
    int size = av_image_get_buffer_size(AV_PIX_FMT_RGB32,info->VideoCodec->width,info->VideoCodec->height,1);
    SwsContext *img_convert_ctx = sws_getContext(info->VideoCodec->width, info->VideoCodec->height, info->VideoCodec->pix_fmt,
               info->VideoCodec->width, info->VideoCodec->height, AV_PIX_FMT_RGB32, SWS_BICUBIC, NULL, NULL, NULL);
    int ret;

    while(1)
    {

        /*
         *不能用av_malloc，因为dll和exe申请的内存空间不一样，用image->bits()会导致报错
        */
        unsigned char * out_buffer = new uchar[size];//(unsigned char *)av_malloc(size);
        info->GetQueueNode(info->videoq,pkt);
        qDebug()<<QThread::currentThread()<<"取出视频包";
        if(!pkt)
        {
            qDebug()<<Tr("视频包队列为空，退出解码帧");
            continue;
        }
        if(avcodec_decode_video2(info->VideoCodec,frame,&ret,pkt)<0)
        {
            qDebug()<<tr("-7:VideoThread,解码帧失败");
        }
        av_packet_unref(pkt);
        if(ret)
        {
            av_image_fill_arrays(convert_frame->data,convert_frame->linesize,out_buffer,AV_PIX_FMT_RGB32,
                                 info->VideoCodec->width, info->VideoCodec->height, 1);
            sws_scale(img_convert_ctx, (const unsigned char* const*)frame->data, frame->linesize, 0,
                      info->VideoCodec->height,convert_frame->data, convert_frame->linesize);
            QImage* img = new QImage((uchar*)out_buffer,info->VideoCodec->width,info->VideoCodec->height,QImage::Format_RGB32);
            Picture pic ;
            pic.img = img;
            pic.pts = frame->pts;
            qDebug()<<QThread::currentThread()<<"加入图片包";
            info->PutQueueNode(info->pictureq,pic);
        }
       // av_packet_unref(pkt);
    }
}
