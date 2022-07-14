#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "chooselevelscene.h"
#include <QMediaPlayer>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    //重新painEvent事件 画背景图
    void paintEvent(QPaintEvent *);
    QMediaPlayer * BtnMusic;
    QMediaPlayer * BGMusic;

    ChooseLevelScene * chooseScene = NULL;

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
