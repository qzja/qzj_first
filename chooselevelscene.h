#ifndef CHOOSELEVELSCENE_H
#define CHOOSELEVELSCENE_H

#include <QMainWindow>
#include "playscene.h"
#include <QMediaPlayer>

class ChooseLevelScene : public QMainWindow
{
    Q_OBJECT
public:
    explicit ChooseLevelScene(QMediaPlayer * BGMusic);

    //重写绘图事件
    void paintEvent(QPaintEvent *);

    QMediaPlayer * BtnMusic;

    //游戏场景对象指针
    PlayScene * play = NULL;

signals:

};

#endif // CHOOSELEVELSCENE_H
