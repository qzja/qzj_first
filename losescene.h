#ifndef LOSESCENE_H
#define LOSESCENE_H

#include <QMainWindow>
#include <QPainter>
#include <QMediaPlayer>

class LoseScene : public QMainWindow
{
    Q_OBJECT
public:
    explicit LoseScene(QWidget *parent = nullptr);

    //重写paintEvent
    void paintEvent(QPaintEvent *);

signals:

};

#endif // LOSESCENE_H
