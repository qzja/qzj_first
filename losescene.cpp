#include "losescene.h"
#include "mypushbutton.h"
#include "mainwindow.h"
#include "playscene.h"

LoseScene::LoseScene(QWidget *parent) : QMainWindow(parent)
{
    //初始化赢场景
    //设置固定大小1920,1153
    setFixedSize(1920, 1153);
    //设置图标
    setWindowIcon(QIcon(":/resource/gameTitle.png"));
    //设置标题
    setWindowTitle("保卫萝卜");

    QMediaPlayer *loseMusic = new QMediaPlayer;
    loseMusic->setMedia(QUrl::fromLocalFile("C:/Users/qzj/Desktop/Lose.mp3"));
    loseMusic->setVolume(50);
    loseMusic -> play();

    //坟墓
    MyPushButton * cup = new MyPushButton(":/resource/grave.png");
    cup -> setParent(this);
    cup -> move(780, 200);
    //游戏
    MyPushButton * youxi = new MyPushButton(":/resource/gameLetter_end.png");
    youxi -> setParent(this);
    youxi -> move(200, 300);
    //失败
    MyPushButton * shengli = new MyPushButton(":/resource/loseLetter.png");
    shengli -> setParent(this);
    shengli -> move(1118, 300);
    //home键
    MyPushButton * homeBtn_long = new MyPushButton(":/resource/homeButton_Long.png");
    homeBtn_long -> setParent(this);
    homeBtn_long -> move(600, 800);
    //重玩游戏键
    MyPushButton * tryAgainBtn = new MyPushButton(":/resource/tryAgain.png");
    tryAgainBtn -> setParent(this);
    tryAgainBtn -> move(900, 805);

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
    connect(tryAgainBtn, &MyPushButton::clicked, [=](){
        //弹跳动画
        tryAgainBtn -> startPress();
        tryAgainBtn -> startRelease();
        //延时0.5秒返回chooselevelscene界面
        QTimer::singleShot(500, this, [=](){
            PlayScene *playAgain = new PlayScene(1);
            //设置开始场景的位置
            playAgain -> setGeometry(this -> geometry());
            //自身隐藏
            this -> hide();
            //显示开始场景
            playAgain -> show();
        });
    });


}

void LoseScene::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/resource/EndBg.png");
    painter.drawPixmap(0, 0, this -> width(), this -> height(), pix);//使图片适应窗口比例

}
