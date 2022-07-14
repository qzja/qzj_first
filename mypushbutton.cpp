#include "mypushbutton.h"
#include <QDebug>
#include <QPropertyAnimation>
//#include <QString>

MyPushButton::MyPushButton()
{
    //初始化定时器对象
    timer2 = new QTimer(this);
    QPixmap pix;
    QString str = QString(":/resource/Blank.png");
    pix.load(str);
//    qDebug() << "timer2connect: " << countNum << "启动";
//    qDebug() << str;
    this -> setFixedSize(pix.width(), pix.height());
    this -> setStyleSheet("QPushButton{border:0px}");
    this -> setIcon(pix);
    this -> setIconSize(QSize(pix.width(), pix.height()));
}
MyPushButton::MyPushButton(QString normalImg, QString pressImg)
{
    this -> normalImgPath = normalImg;
    this -> pressImgPath = pressImg;

    QPixmap pix;
    pix.load(normalImg);
    //设置图片固定大小
    this -> setFixedSize(pix.width(), pix.height());
    //设置不规则图片样式
    this -> setStyleSheet("QPushButton{border:0px;}");
    //设置图标
    this -> setIcon(pix);
    //设置图标大小
    this -> setIconSize(QSize(pix.width(), pix.height()));
}

void MyPushButton::startPress()
{
    //创建动态对象
    QPropertyAnimation * animation = new QPropertyAnimation(this, "geometry");
    //设置动画时间间隔
    animation -> setDuration(200);

    //起始位置
    animation -> setStartValue(QRect(this -> x(), this -> y(), this -> width(), this -> height()));
    //结束位置
    animation -> setEndValue(QRect(this -> x(), this -> y()+5, this -> width(), this -> height()));
    //设置弹跳曲线
    animation -> setEasingCurve(QEasingCurve::OutBounce);
    //执行动画
    animation -> start();
}

void MyPushButton::startRelease()
{
    //创建动态对象
    QPropertyAnimation * animation = new QPropertyAnimation(this, "geometry");
    //设置动画时间间隔
    animation -> setDuration(200);

    //起始位置
    animation -> setStartValue(QRect(this -> x(), this -> y()+5, this -> width(), this -> height()));
    //结束位置
    animation -> setEndValue(QRect(this -> x(), this -> y(), this -> width(), this -> height()));
    //设置弹跳曲线
    animation -> setEasingCurve(QEasingCurve::OutBounce);
    //执行动画
    animation -> start();
}

void MyPushButton::CountDown()
{
    timer2 -> start(1000);
    QMediaPlayer * count = new QMediaPlayer;
    count->setMedia(QUrl::fromLocalFile("C:/Users/qzj/Desktop/CountDown.mp3"));
    count->setVolume(50);
    QMediaPlayer * Go = new QMediaPlayer;
    Go->setMedia(QUrl::fromLocalFile("C:/Users/qzj/Desktop/GO.mp3"));
    Go->setVolume(50);

    //监听倒数信号
    connect(timer2, &QTimer::timeout, [=](){
        QPixmap pix;
        QString str = QString(":/resource/countdown_%1.png").arg(this -> countNum++);
        pix.load(str);
        this -> setFixedSize(pix.width(), pix.height());
        this -> setStyleSheet("QPushButton{border:0px}");
        this -> setIcon(pix);
        this -> setIconSize(QSize(pix.width(), pix.height()));
        //判断如果萝卜抖完了，将shakeNum重置为1
        if(this -> countNum > 1 && this -> countNum < 5)
        {
            count -> play();
        }
        else if(this -> countNum == 5)
        {
            Go -> play();
        }
        if(this -> countNum > 5)
        {
            this -> countNum = 1;
            timer2 -> stop();
            this -> ~MyPushButton();
        }
    });
}

void MyPushButton::chooseWeapon()
{
    QPixmap position, weapons;
    position.load(":/resource/position.png");
    this -> setFixedSize(position.width(), position.height());
    //设置不规则图片样式
    this -> setStyleSheet("QPushButton{border:0px;}");
    //设置图标
    this -> setIcon(position);
    //设置图标大小
    this -> setIconSize(QSize(position.width(), position.height()));
}

void MyPushButton::ShowHeart(int num)
{
    QString str = QString(":/resource/heart%1.png").arg(num);
    QPixmap heart;
    heart.load(str);
    this -> setFixedSize(heart.width(), heart.height());
    //设置不规则图片样式
    this -> setStyleSheet("QPushButton{border:0px;}");
    //设置图标
    this -> setIcon(heart);
    //设置图标大小
    this -> setIconSize(QSize(heart.width(), heart.height()));
}
