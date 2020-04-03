#include "MovieWidget.h"
#include <QEvent>
#include <QTimer>
void MovieWidget::paintEvent(QPaintEvent*event)
{

}
void MovieWidget::GetAVinfoSlots(AVInfo *info)
{
    av_info = info;
}
void MovieWidget::GetPicture()
{
    int delay;
    Picture*ptr;//=av_info->GetQueueNode(av_info->pictureq);
    img = ptr->img;
    repaint();
    QTimer::singleShot(delay, this,&MovieWidget::GetPicture);
}
