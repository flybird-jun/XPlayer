#pragma("once")

#include <QMainWindow>
#include <QTreeWidget>
#include "MovieWidget.h"
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
    void CreateMovieWidget();
private:
    Ui::MainWindow *ui;
    QMenuBar *bar;
    QTreeWidget *file_list;
    QWidget *button_widget;
    MovieWidget *movie_widget;
};
