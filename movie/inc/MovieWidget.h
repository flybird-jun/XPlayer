_Pragma("once")
#include<QWidget>
#include"AVInfo.h"
class MovieWidget:public QWidget
{
   Q_OBJECT
public:
    virtual void paintEvent(QPaintEvent *event) override;
private slots:
    void GetAVinfoSlots(AVInfo *info);
private:
    void GetPicture();
    AVInfo* av_info;
    QImage *img;
};
