#include "carrot.h"
#include <QDebug>
#include "mypushbutton.h"

Carrot::Carrot(QString str)
{
    QPixmap pix;

    pix.load(str);
    this -> setFixedSize(pix.width(), pix.height());
    this -> setStyleSheet("QPushButton{border:0px}");
    this -> setIcon(pix);
    this -> setIconSize(QSize(pix.width(), pix.height()));
}

void Carrot::ShowCarrot(int num)
{
    //萝卜137*177
    heartNum = num;
    QString ImgPath ;
    QPixmap pix;
    if(num == 10)
    {
        ImgPath = ":/resource/carrot4.png";
        pix.load(ImgPath);
        this -> setFixedSize(pix.width(), pix.height());
        this -> setStyleSheet("QPushButton{border:0px}");
        this -> setIcon(pix);
        this -> setIconSize(QSize(pix.width(), pix.height()));

        //初始化定时器对象
        timer1 = new QTimer(this);
        //监听萝卜抖动信号
        connect(timer1, &QTimer::timeout, [=](){
            QPixmap shakePix;
            QString shake_str = QString(":/resource/carrotShake%1.png").arg(this -> shakeNum++);
            shakePix.load(shake_str);
            qDebug() << "timer1connect: " << shakeNum << "启动";
            qDebug() << shake_str;
            this -> setFixedSize(shakePix.width(), shakePix.height());
            this -> setStyleSheet("QPushButton{border:0px}");
            this -> setIcon(shakePix);
            this -> setIconSize(QSize(shakePix.width(), shakePix.height()));
            //判断如果萝卜抖完了，将shakeNum重置为1
            if(this -> shakeNum > 10)
            {
                this -> shakeNum = 1;
                timer1 -> stop();
            }
        });
    }
    else if(num == 9)
    {
        ImgPath = ":/resource/carrot9.png";
        pix.load(ImgPath);
        this -> setFixedSize(pix.width(), pix.height());
        this -> setStyleSheet("QPushButton{border:0px}");
        this -> setIcon(pix);
        this -> setIconSize(QSize(pix.width(), pix.height()));
    }
    else if(num == 8 || num  == 7)
    {
        ImgPath = ":/resource/crycarrot2.png";
        pix.load(ImgPath);
        this -> setFixedSize(pix.width(), pix.height());
        this -> setStyleSheet("QPushButton{border:0px}");
        this -> setIcon(pix);
        this -> setIconSize(QSize(pix.width(), pix.height()));
    }
    else if(num == 6 || num == 5 || num == 4)
    {
        ImgPath = ":/resource/crycarrot3.png";
        pix.load(ImgPath);
        this -> setFixedSize(pix.width(), pix.height());
        this -> setStyleSheet("QPushButton{border:0px}");
        this -> setIcon(pix);
        this -> setIconSize(QSize(pix.width(), pix.height()));
    }
    else if(num == 3 || num == 2 || num == 1)
    {
        ImgPath = ":/resource/crycarrot4.png";
        pix.load(ImgPath);
        this -> setFixedSize(pix.width(), pix.height());
        this -> setStyleSheet("QPushButton{border:0px}");
        this -> setIcon(pix);
        this -> setIconSize(QSize(pix.width(), pix.height()));
    }
    else if(num == 0)
    {
        ImgPath = ":/resource/dieCarrot.png";
        pix.load(ImgPath);
        this -> setFixedSize(pix.width(), pix.height());
        this -> setStyleSheet("QPushButton{border:0px}");
        this -> setIcon(pix);
        this -> setIconSize(QSize(pix.width(), pix.height()));
    }

}

void Carrot::CarrotShake()
{
    timer1 -> start(50);
    qDebug() << "定时器启动";
}



