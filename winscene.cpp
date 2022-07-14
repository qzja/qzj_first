#include "winscene.h"
#include "mypushbutton.h"
#include "mainwindow.h"
#include "chooselevelscene.h"

WinScene::WinScene(QWidget *parent) : QMainWindow(parent)
{
    //初始化赢场景
    //设置固定大小1920,1153
    setFixedSize(1920, 1153);
    //设置图标
    setWindowIcon(QIcon(":/resource/gameTitle.png"));
    //设置标题
    setWindowTitle("保卫萝卜");

    //奖杯
    MyPushButton * cup = new MyPushButton(":/resource/WinCup.png");
    cup -> setParent(this);
    cup -> move(801, 200);
    //游戏
    MyPushButton * youxi = new MyPushButton(":/resource/gameLetter_end.png");
    youxi -> setParent(this);
    youxi -> move(200, 300);
    //胜利
    MyPushButton * shengli = new MyPushButton(":/resource/winLetter_end.png");
    shengli -> setParent(this);
    shengli -> move(1118, 300);
    //home键
    MyPushButton * homeBtn_long = new MyPushButton(":/resource/homeButton_Long.png");
    homeBtn_long -> setParent(this);
    homeBtn_long -> move(600, 800);
    //继续游戏键
    MyPushButton * continueBtn = new MyPushButton(":/resource/ContinueBtn.png");
    continueBtn -> setParent(this);
    continueBtn -> move(900, 805);

    //home键摁下返回最开始的游戏界面
    connect(homeBtn_long, &MyPushButton::clicked, [=](){
        //弹跳动画
        homeBtn_long -> startPress();
        homeBtn_long -> startRelease();
        //延时0.5秒返回初始主界面
        QTimer::singleShot(500, this, [=](){
            MainWindow *mainScene = new MainWindow;
            //设置开始场景的位置
            mainScene -> setGeometry(this -> geometry());
            //自身隐藏
            this -> hide();
            //显示开始场景
            mainScene -> show();
        });
    });
    //按继续游戏键可以返回选择游戏场景界面
    connect(continueBtn, &MyPushButton::clicked, [=](){
        //弹跳动画
        continueBtn -> startPress();
        continueBtn -> startRelease();
        //延时0.5秒返回chooselevelscene界面
        QTimer::singleShot(500, this, [=](){
//            ChooseLevelScene *choose = new ChooseLevelScene(BGMusic);
//            //设置开始场景的位置
//            choose -> setGeometry(this -> geometry());
//            //自身隐藏
//            this -> hide();
//            //显示开始场景
//            choose -> show();
        });
    });


}

void WinScene::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/resource/EndBg.png");
    painter.drawPixmap(0, 0, this -> width(), this -> height(), pix);//使图片适应窗口比例

}
