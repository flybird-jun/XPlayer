#pragma("once")

#include <QMainWindow>
#include <QTreeWidget>
#include "movie/MovieWidget.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:
    void CreateMenuBar();
    void CreateFileTree();
    void CreateButtonWidget();
private:
    Ui::MainWindow *ui;
    QMenuBar *bar;
    QTreeWidget *file_list;
    QWidget *button_widget;
    QWidget *movie_widget;
};
