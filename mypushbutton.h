#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H

#include <QPushButton>
#include <QTimer>
#include <QMediaPlayer>

class MyPushButton : public QPushButton
{
    Q_OBJECT
public:
    //explicit MyPushButton(QWidget *parent = nullptr);
    MyPushButton();
    //构造函数 参数1 正常显示的图片路径 参数2 按下后显示的图片路径
    MyPushButton(QString normalImg, QString pressImg = "");

    //成员属性 保护用户传入的默认显示路径 以及按下后显示的图片路径
    QString normalImgPath;
    QString pressImgPath;

    //弹跳特效
    void startPress();//向下跳
    void startRelease();//向上跳

    //倒数特效
    void CountDown();
    QTimer *timer2;
    int countNum = 1;

    //选择武器
    void chooseWeapon();

    //carrot血量
    void ShowHeart(int num);


signals:

};

#endif // MYPUSHBUTTON_H
