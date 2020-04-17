_Pragma("once")
#include<QWidget>
#include"AVInfo.h"
#include "BtnObj/inc/BtnObj.h"
#include "DecodeThread.h"
class MovieWidget:public QWidget
{
   Q_OBJECT
public:
    //using QWidget::QWidget;
    MovieWidget(QWidget *parent);
    ~MovieWidget();


/*
 * 处理按键的函数
*/
    void Pause();
    void SeparateAVCodeStream();
private:
    bool pause = false;
/*
 * 供mainwindow调用接口
*/
public:
    void OpenAV(char *path);
private:
    QString file_dir;
    QString file_name;
    QString file_suffix;
    QString file_path;

/*
 * 视频解码相关
*/
public:
    virtual void paintEvent(QPaintEvent *event);
    void GetPicture();
public slots:
    void GetAVinfoSlots(AVInfo *info);
private:
    double GetVideoClock();

    DecodeThread * movieThread = nullptr;
    AVInfo* av_info;
    QImage *img=nullptr;
    double video_clock = 0;

    //QTimer *refresh_timer;
};
