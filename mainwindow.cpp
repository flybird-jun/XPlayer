#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QtDebug>
#include "MacroDefine.h"
#include <QPushButton>
#include <DecodeThread.h>
#include "BtnObj/inc/Pause.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    resize(MAIN_WINDOW_W,MAIN_WINDOW_H);
    CreateMovieWidget();
    CreateMenuBar();
    CreateFileTree();
    CreateButtonWidget();

   // connect(bar)
}
void MainWindow::CreateMovieWidget()
{
    movie_widget = new MovieWidget(this);
    movie_widget->setGeometry(VIDEO_WIDGET_X,VIDEO_WIDGET_Y,VIDEO_WIDGET_W,VIDEO_WIDGET_H);
}

void MainWindow::CreateMenuBar()
{
    bar = new QMenuBar(this);
    bar->resize(width(),MENU_BAR_H);
    QMenu *open = new QMenu(tr("打开"));
    QAction *file = new QAction(tr("文件"));
    QAction *dir = new QAction(tr("目录"));
    open->addAction(file);
    open->addAction(dir);
    bar->addMenu(open);
    /*******test*******/

    DecodeThread * movieThread = new DecodeThread();
    connect(movieThread,&DecodeThread::SendAVinfoSignal,movie_widget,&MovieWidget::GetAVinfoSlots);
    movieThread->OpenFile("./5.avi");
    movieThread->start();
    /*******************************/
    /*
    connect(file,&QAction::triggered,this,[=](bool checked)
              {
                 QString file_name=QFileDialog::getOpenFileName(this,tr("选择视频"), ".", tr("视频(*.avi *.mp4 *.flv)"));
                 QTreeWidgetItem *item = new QTreeWidgetItem(file_list,QStringList(file_name));
                 DecodeThread * movieThread = new DecodeThread();
                 connect(movieThread,&DecodeThread::SendAVinfoSignal,movie_widget,&MovieWidget::GetAVinfoSlots);
                 movieThread->OpenFile(file_name.toStdString().c_str());
                 movieThread->start();

              }
            );
    connect(dir,&QAction::triggered,this,[=](bool checked)
              {
                QString file_dir=QFileDialog::getExistingDirectory(this,tr("选择文件夹"), ".");
                QDir dir(file_dir);
                if(!dir.exists())
                {
                    return;
                }
                QStringList str = file_dir.split("/");
                QString itemName = *(str.end()-1);
                qDebug()<<"itemName:"<<itemName;
                QTreeWidgetItem *item = new QTreeWidgetItem(file_list,QStringList(itemName));
                dir.setSorting(QDir::Name);
                QFileInfoList list = dir.entryInfoList();
                qDebug()<<"file list:";
                QRegExp reg("([^\\\\*]+\\.((avi)|(mp4)|(mkv)|(flv)|(rmvb)|(mp3)))");///
                for(auto file:list)
                {
                    reg.indexIn(file.fileName());
                    QString name=reg.cap(0);
                    if(name!=nullptr)
                    {
                         QTreeWidgetItem *item2 = new QTreeWidgetItem(item,QStringList(name));
                         qDebug()<<name<<" ";
                    }
                }
              }
            );*/
}
void MainWindow::CreateFileTree()
{
    file_list = new QTreeWidget(this);
    file_list->setGeometry(TREE_WIDGET_X,TREE_WIDGET_Y,TREE_WIDGET_W,TREE_WIDGET_H);
}
#define BTN_NUM 4
void MainWindow::CreateButtonWidget()
{

    button_widget = new QWidget(this);
    qDebug()<<BUTTON_WIDGET_X<<" "<<BUTTON_WIDGET_Y<<" "<<BUTTON_WIDGET_W<<" "<<BUTTON_WIDGET_H;
    button_widget->setGeometry(BUTTON_WIDGET_X,BUTTON_WIDGET_Y,BUTTON_WIDGET_W,BUTTON_WIDGET_H);
    QString btn_text[BTN_NUM]={tr("上一个"),tr("暂停/播放"),tr("下一个"),tr("测试")};
    QPushButton * btn[BTN_NUM];
    for(int i=0;i<BTN_NUM;i++)
    {
        btn[i] = new QPushButton(button_widget);
        btn[i]->setText(btn_text[i]);
        btn[i]->resize(BUTTON_W,BUTTON_H);
        btn[i]->move(BUTTON_START_X+BUTTON_W*i+BUTTON_GAP,BUTTON_START_Y);
    }
    connect(btn[1],&QPushButton::clicked,movie_widget,[=]
    {
        BtnObj *obj = new PauseBtn();
        obj->DoAction(movie_widget);
    });
  //  connect(btn[3],&QPushButton::clicked,)
}
MainWindow::~MainWindow()
{

    delete ui;
}

