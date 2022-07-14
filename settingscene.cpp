#include "settingscene.h"
#include "mypushbutton.h"
#include "mainwindow.h"
#include <QPushButton>
#include <QLabel>

SettingScene::SettingScene(QWidget *parent) : QMainWindow(parent)
{
    //初始化赢场景
    //设置固定大小1920,1153
    setFixedSize(1920, 1153);
    //设置图标
    setWindowIcon(QIcon(":/resource/gameTitle.png"));
    //设置标题
    setWindowTitle("保卫萝卜");

    QFont font;
    font.setFamily("华文新魏");
    font.setPointSize(20);
    QString str1 = QString("简介");
    QString str2 = QString("制作者：阙子菁，刘开蕊，蓝佳伟");
    QLabel * label1 = new QLabel;
    label1 -> setParent(this);
    label1 -> setFont(font);
    label1 -> setText(str1);
    label1 -> setGeometry(900, 540, 900, 50);
    QLabel * label2 = new QLabel;
    label2 -> setParent(this);
    label2 -> setFont(font);
    label2 -> setText(str2);
    label2 -> setGeometry(500, 650, 900, 50);


    //关闭按钮
    MyPushButton * close = new MyPushButton(":/resource/ss_back_normal.png");
    close -> setParent(this);
    close -> move(100, 1000);
    connect(close, &MyPushButton::clicked, [=](){
        //摁下动画
        close -> startPress();
        close -> startRelease();
        QTimer::singleShot(500, this, [=](){
            emit this -> chooseSceneBack();
//            MainWindow *mainScene = new MainWindow;
//            //设置开始场景的位置
//            mainScene -> setGeometry(this -> geometry());
//            //自身隐藏
//            this -> hide();
//            //显示开始场景
//            mainScene -> show();
        });
    });

}

void SettingScene::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/resource/setting_bg.png");
    painter.drawPixmap(0, 0, this -> width(), this -> height(), pix);//使图片适应窗口比例

}
