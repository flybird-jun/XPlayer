_Pragma("once")
#include"AVInfo.h"
class VideoThread:public QThread
{
Q_OBJECT
public:
    void run() override;
    void StartDecodePacket(AVInfo *info);
};
