#include "chooselevelscene.h"
#include <QPainter>
#include "mypushbutton.h"
#include <QTimer>


ChooseLevelScene::ChooseLevelScene(QMediaPlayer * BGMusic)
{
    //配置选择关卡场景
    setFixedSize(1920, 1153);
    //设置图标
    setWindowIcon(QIcon(":/resource/gameTitle.png"));
    //设置标题
    setWindowTitle("保卫萝卜");

    BtnMusic = new QMediaPlayer;
    BtnMusic->setMedia(QUrl::fromLocalFile("C:/Users/qzj/Desktop/Select.mp3"));
    BtnMusic->setVolume(50);

    //创建关卡选择按钮
    for(int i = 0; i < 2; i++)
    {
        QString str = QString(":/resource/ss_map%1.png").arg(i+1);
        MyPushButton * levelBtn = new MyPushButton(str);
        levelBtn -> setParent(this);
        levelBtn -> move(600 + i * 400, 500);

        //监听每个按钮的点击事件
        connect(levelBtn, &MyPushButton::clicked, [=](){
            BtnMusic -> play();
            this -> hide();
            play = new PlayScene(i+1);
            play -> show();
            BGMusic -> stop();
        });
    }

}

void ChooseLevelScene::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/resource/blueBg.png");
    painter.drawPixmap(0, 0, this -> width(), this -> height(), pix);//使图片适应窗口比例
}

