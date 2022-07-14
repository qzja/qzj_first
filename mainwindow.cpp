#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mypushbutton.h"
#include <QPainter>
#include <QTimer>
#include <QPushButton>
#include "settingscene.h"
#include <QLabel>
#include <QMediaPlayer>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //配置开始场景
    //设置固定大小1920,1153
    setFixedSize(1920, 1153);
    //设置图标
    setWindowIcon(QIcon(":/resource/gameTitle.png"));
    //设置标题
    setWindowTitle("保卫萝卜");

    BGMusic = new QMediaPlayer;
    BGMusic->setMedia(QUrl::fromLocalFile("C:/Users/qzj/Desktop/BGMusic.mp3"));
    BGMusic->setVolume(50);
    BGMusic -> play();

    BtnMusic = new QMediaPlayer;
    BtnMusic->setMedia(QUrl::fromLocalFile("C:/Users/qzj/Desktop/Select.mp3"));
    BtnMusic->setVolume(50);


    //设置按钮
    MyPushButton * setting = new MyPushButton(":/resource/Setting.png");
    setting -> setParent(this);
    setting -> move(438, 363);
    SettingScene * setWidget = new SettingScene;
    connect(setting, &MyPushButton::clicked, [=](){
        BtnMusic->play();
        setWidget -> setGeometry(this -> geometry());
        this -> hide();
        setWidget -> show();
    });

    connect(setWidget, &SettingScene::chooseSceneBack, this, [=](){
        this -> setGeometry(setWidget -> geometry());
        setWidget -> hide();//将选择关卡场景隐藏掉
        this -> show();//重新显示主场景
    });

    //帮助按钮
    MyPushButton * help = new MyPushButton(":/resource/helpBtn.png");
    help -> setParent(this);
    help -> move(1347, 361);
    connect(help, &MyPushButton::clicked, [=](){
        BtnMusic->play();
        help -> hide();
        MyPushButton * helpPage = new MyPushButton(":/resource/helpPage.png");
        helpPage -> setParent(this);
        helpPage -> move(492, 313);//936,526
        helpPage -> show();
        QFont font;
        font.setFamily("华文新魏");
        font.setPointSize(12);
        QString str1 = QString("在空位选择想要放置的武器，利用武器消灭怪物。");
        QString str2 = QString("若怪物未被消灭，吃到萝卜，则萝卜生命值减少。");
        QString str3 = QString("萝卜死亡则游戏结束.");
        QLabel * label1 = new QLabel;
        QLabel * label2 = new QLabel;
        QLabel * label3 = new QLabel;
        label1 -> setParent(this);
        label1 -> setFont(font);
        label1 -> setText(str1);
        label1 -> setGeometry(550, 350, 900, 300);
        label1 -> show();
        label2 -> setParent(this);
        label2 -> setFont(font);
        label2 -> setText(str2);
        label2 -> setGeometry(550, 400, 900, 300);
        label2 -> show();
        label3 -> setParent(this);
        label3 -> setFont(font);
        label3 -> setText(str3);
        label3 -> setGeometry(550, 450, 900, 300);
        label3 -> show();
        connect(helpPage, &MyPushButton::clicked, [=](){
            helpPage -> hide();
            help -> show();
            label1 -> hide();
            label2 -> hide();
            label3 -> hide();
        });
    });


    //开始按钮
    MyPushButton * startBtn = new MyPushButton(":/resource/startBtn.png");
    startBtn -> setParent(this);
    startBtn -> move(806, 441);
    //1085 721, 282

    //实例化选择关卡场景
    chooseScene = new ChooseLevelScene(BGMusic);

    //点击开始按钮，进入选关界面
    connect(startBtn, &QPushButton::clicked, [=](){
        BtnMusic->play();
        //弹起特效
        startBtn -> startPress();
        startBtn -> startRelease();

        //显示选择关卡场景
        //延时进入到选择关卡场景中
        QTimer::singleShot(500, this, [=](){
            //设置chooseScene场景的位置
            chooseScene -> setGeometry(this -> geometry());
            //自身隐藏
            this -> hide();
            //显示选择关卡场景
            chooseScene -> show();
        });
    });

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/resource/startWidget.png");
    painter.drawPixmap(0, 0, this -> width(), this -> height(), pix);//使图片适应窗口比例
}
