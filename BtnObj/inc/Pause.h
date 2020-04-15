#ifndef PAUSE_H
#include "BtnObj.h"
class PauseBtn:public BtnObj
{
public:
    virtual void DoAction(MovieWidget *w)
    {
        w->Pause();
    }
};
#endif
