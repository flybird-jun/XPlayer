_Pragma("once")
#include<QWidget>
#include"AVInfo.h"
#include "BtnObj/inc/BtnObj.h"
class MovieWidget:public QWidget
{
   Q_OBJECT
public:
    //using QWidget::QWidget;
    MovieWidget(QWidget *parent);
    ~MovieWidget();
/*
 * 视频解码相关
*/
    virtual void paintEvent(QPaintEvent *event);
    void GetPicture();

/*
 * 处理按键的函数
*/
    void Pause();

public slots:
    void GetAVinfoSlots(AVInfo *info);
  //  void ButtonSlots(BtnObj *obj);
private:
    double GetVideoClock();
    AVInfo* av_info;
    QImage *img=nullptr;
    double video_clock = 0;
    bool pause = false;
    //QTimer *refresh_timer;
};
