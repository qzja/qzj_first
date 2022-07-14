#ifndef CARROT_H
#define CARROT_H

#include <QPushButton>
#include <QTimer>

class Carrot : public QPushButton
{
    Q_OBJECT
public:
    //explicit Carrot(QWidget *parent = nullptr);
    Carrot(QString str);
    //参数 萝卜血量
    void ShowCarrot(int num);
    void CarrotShake();

    //萝卜抖动
    QTimer *timer1;
    int shakeNum = 1;
    int heartNum = 10;

    QTimer *eatGif;
    int eatPixNum = 1;

signals:

};

#endif // CARROT_H
