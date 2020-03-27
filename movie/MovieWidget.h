_Pragma("once")
#include<QWidget>
class MovieWidget:public QWidget
{
   Q_OBJECT
 public:
    virtual void paintEvent(QPaintEvent *event) override;

};
