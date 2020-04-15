#ifndef __BTN_OBJ
#define __BTN_OBJ
#include "movie/inc/MovieWidget.h"
class MovieWidget;
class BtnObj
{
public:
   virtual void DoAction(MovieWidget *w) = 0;
};
#endif
