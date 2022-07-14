#ifndef WINSCENE_H
#define WINSCENE_H

#include <QMainWindow>
#include <QPainter>

class WinScene : public QMainWindow
{
    Q_OBJECT
public:
    explicit WinScene(QWidget *parent = nullptr);

    //重写paintEvent
    void paintEvent(QPaintEvent *);

signals:

};

#endif // WINSCENE_H
