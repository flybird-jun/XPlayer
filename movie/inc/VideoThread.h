_Pragma("once")
#include"AVInfo.h"
class VideoThread:public QObject
{
Q_OBJECT
public slots:
    void StartDecodePacketSlot(AVInfo *info);
};
