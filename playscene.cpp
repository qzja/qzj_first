#include "playscene.h"
#include <QDebug>
#include <QPainter>
#include "carrot.h"
#include "mypushbutton.h"
#include "losescene.h"
#include "winscene.h"
#include <synchapi.h>
#include "enemy.h"

PlayScene::PlayScene(int level)
{
    QString str = QString("进入了第%1关").arg(level);
    qDebug() << str;
    this -> levelNum = level;

    //初始化游戏场景
    //设置固定大小1920,1153
    setFixedSize(1920, 1153);
    //设置图标
    setWindowIcon(QIcon(":/resource/gameTitle.png"));
    //设置标题
    setWindowTitle("保卫萝卜");

    money = 100;//初始金币数
    enemy_money = 20;//杀死怪物加金币数
    enemyNum = 30;//根据敌人波数更改，总敌人数3*10
    count=0;//每波敌人数统计
    count2=0;//波次统计
    enterEnemyNum=0;//到达终点的敌人数
    //int num = 10;//怪物每在萝卜处消失一次，num--;

    //设置怪物出来的牌子
    MyPushButton * enemyStart = new MyPushButton(":/resource/enemyEntrance.png");
    enemyStart -> setParent(this);
    enemyStart -> move(140, 100);

    //点击牌子出现怪物
    connect(enemyStart,&MyPushButton::clicked,this,&PlayScene::addAllEnemy);
    QTimer *timer_enemy=new QTimer(this);
    connect(timer_enemy,&QTimer::timeout,this,&PlayScene::updateScene);
    timer_enemy->start(10);//每10ms触发updateScene,刷新界面

    //设置萝卜血量
    MyPushButton * heart = new MyPushButton(":/resource/heart10.png");
    heart -> setParent(this);
    heart -> move(1810, 150);
    int num = 0;

    //设置萝卜
    //Carrot * carrot = new Carrot(num);
    carrot = new Carrot(":/resource/carrot4.png");
    carrot -> setParent(this);
    carrot -> move(1680, 100);
    judge = new QTimer(this);
    judge -> start(500);
    connect(judge, &QTimer::timeout, [=]()mutable{
        carrot -> ShowCarrot(carrot -> heartNum);
        carrot -> show();
        heart -> ShowHeart(carrot -> heartNum);
        heart -> show();
        //判断输赢
       printf("%d\n",carrot->heartNum);
        if(carrot -> heartNum == 0)//输
        {
            judge -> stop();
            QTimer::singleShot(500, this, [=](){
                LoseScene * lose = new LoseScene();
                carrot -> heartNum = 10;
                //设置endScene场景的位置
                lose -> setGeometry(this -> geometry());
                //自身隐藏
                this -> hide();
                //显示场景
                lose -> show();
                judge -> stop();
            });

        }
        else if(enemyNum == 0 && carrot -> heartNum != 0)//赢
        {
            judge -> stop();
            QTimer::singleShot(500, this, [=](){
                WinScene * win = new WinScene();
                carrot -> heartNum = 10;
                //设置winScene场景的位置
                win -> setGeometry(this -> geometry());
                //自身隐藏
                this -> hide();
                //显示选择关卡场景
                win -> show();
                judge -> stop();
            });
        }

    });

    //萝卜抖动触发
    if(carrot -> heartNum == 10 && num == 0)
    {
        connect(carrot, &Carrot::clicked, [=]()mutable{
            qDebug() << "点击萝卜";
            carrot -> move(1630, 100);
            carrot -> CarrotShake();
            num = 1;
        });
    }

    //设置倒数3，2，1，go
    MyPushButton * count = new MyPushButton;
    count -> setParent(this);
    count -> move(860, 458);
    count -> CountDown();

    //clouds装饰设置
    MyPushButton * balloon = new MyPushButton(":/resource/balloon.png");
    balloon -> setParent(this);
    balloon -> move(880, 50);
    MyPushButton * clouds_1 = new MyPushButton(":/resource/cloud01(2).png");
    MyPushButton * clouds_2 = new MyPushButton(":/resource/cloud01(2).png");
    clouds_1 -> setParent(this);
    clouds_1 -> move(330, 520);
    clouds_2 -> setParent(this);
    clouds_2 -> move(1480, 520);
    MyPushButton * planet_1 = new MyPushButton(":/resource/cloud03.png");
    MyPushButton * planet_2 = new MyPushButton(":/resource/cloud03.png");
    planet_1 -> setParent(this);
    planet_1 -> move(700, 390);
    planet_2 -> setParent(this);
    planet_2 -> move(1150, 390);
    MyPushButton * rainbow = new MyPushButton(":/resource/rainbow.png");
    rainbow -> setParent(this);
    rainbow -> move(820, 650);
    MyPushButton * forest_1 = new MyPushButton(":/resource/forest.png");
    MyPushButton * forest_2 = new MyPushButton(":/resource/forest.png");
    forest_1 -> setParent(this);
    forest_1 -> move(550, 50);
    forest_2 -> setParent(this);
    forest_2 -> move(1200, 50);

    chooseWpn = new QMediaPlayer;
    chooseWpn->setMedia(QUrl::fromLocalFile("C:/Users/qzj/Desktop/TowerBulid.mp3"));
    chooseWpn->setVolume(50);

    //设置鼠标点击以后可显示武器位置以及武器选择
    MyPushButton * choose_1 = new MyPushButton(":/resource/posBlank.png");
    MyPushButton * choose_2 = new MyPushButton(":/resource/posBlank.png");
    MyPushButton * choose_3 = new MyPushButton(":/resource/posBlank.png");
    //位置1
        choose_1 -> setParent(this);
        choose_1 -> move(500, 520);//左一小云旁
        connect(choose_1, &MyPushButton::clicked, [=](){
            choose_1 -> chooseWeapon();
            //设置武器选择选项
            //瓶子
            MyPushButton * bottle = new MyPushButton(":/resource/ss_towers_01(1).png");
            bottle -> setParent(this);
            bottle -> move(460, 430);
            bottle -> show();
            //shit攻击
            MyPushButton * shit = new MyPushButton(":/resource/ss_towers_01(2).png");
            shit -> setParent(this);
            shit -> move(563, 430);
            shit -> show();
            //底座
            MyPushButton * base = new MyPushButton(":/resource/weaponBase.png");
            base -> setParent(this);
            base -> move(510, 530);
            connect(bottle, &MyPushButton::clicked, [=](){
                delete bottle;
                delete shit;
                choose_1 -> hide();//隐藏位置
                QTimer::singleShot(500, this, [=](){
                    chooseWpn -> play();
                    base -> show();
                    MyPushButton * bottle_wpn = new MyPushButton(":/resource/bottle.png");
                    bottle_wpn -> setParent(this);
                    bottle_wpn -> move(527, 520);
                    bottle_wpn -> show();
                });
            });
            connect(shit, &MyPushButton::clicked, [=](){
                delete bottle;
                delete shit;
                choose_1 -> hide();//隐藏位置
                QTimer::singleShot(500, this, [=](){
                    chooseWpn -> play();
                    MyPushButton * shit_wpn = new MyPushButton(":/resource/shit(3).png");
                    shit_wpn -> setParent(this);
                    shit_wpn -> move(480, 490);
                    shit_wpn -> show();
                });
            });
        });

        //位置2
        choose_2 -> setParent(this);
        choose_2 -> move(850, 360);//左一星球旁
        connect(choose_2, &MyPushButton::clicked, [=](){
            choose_2 -> chooseWeapon();
            //设置武器选择选项
            MyPushButton * bottle = new MyPushButton(":/resource/ss_towers_01(1).png");
            bottle -> setParent(this);
            bottle -> move(810, 270);
            bottle -> show();
            MyPushButton * shit = new MyPushButton(":/resource/ss_towers_01(2).png");
            shit -> setParent(this);
            shit -> move(913, 270);
            shit -> show();
            MyPushButton * base = new MyPushButton(":/resource/weaponBase.png");
            base -> setParent(this);
            base -> move(860, 370);
            connect(bottle, &MyPushButton::clicked, [=](){
                delete bottle;
                delete shit;
                choose_2 -> hide();
                QTimer::singleShot(500, this, [=](){
                    chooseWpn -> play();
                    base -> show();
                    MyPushButton * bottle_wpn = new MyPushButton(":/resource/bottle.png");
                    bottle_wpn -> setParent(this);
                    bottle_wpn -> move(877, 370);
                    bottle_wpn -> show();
                });
            });
            connect(shit, &MyPushButton::clicked, [=](){
                delete bottle;
                delete shit;
                choose_2 -> hide();
                QTimer::singleShot(500, this, [=](){
                    chooseWpn -> play();
                    MyPushButton * shit_wpn = new MyPushButton(":/resource/shit(3).png");
                    shit_wpn -> setParent(this);
                    shit_wpn -> move(830, 330);
                    shit_wpn -> show();
                });
            });
        });
        //位置3
        choose_3 -> setParent(this);
        choose_3 -> move(1330, 830);//右道下侧
        connect(choose_3, &MyPushButton::clicked, [=](){
            choose_3 -> chooseWeapon();
            //设置武器选择选项
            MyPushButton * bottle = new MyPushButton(":/resource/ss_towers_01(1).png");
            bottle -> setParent(this);
            bottle -> move(1290, 960);
            bottle -> show();
            MyPushButton * shit = new MyPushButton(":/resource/ss_towers_01(2).png");
            shit -> setParent(this);
            shit -> move(1393, 960);
            shit -> show();
            MyPushButton * base = new MyPushButton(":/resource/weaponBase.png");
            base -> setParent(this);
            base -> move(1330, 830);
            connect(bottle, &MyPushButton::clicked, [=](){
                delete bottle;
                delete shit;
                choose_3 -> hide();
                QTimer::singleShot(500, this, [=](){
                    chooseWpn -> play();
                    base -> show();
                    MyPushButton * bottle_wpn = new MyPushButton(":/resource/bottle.png");
                    bottle_wpn -> setParent(this);
                    bottle_wpn -> move(1347, 820);
                    bottle_wpn -> show();
                });
            });
            connect(shit, &MyPushButton::clicked, [=](){
                delete bottle;
                delete shit;
                choose_3 -> hide();
                QTimer::singleShot(500, this, [=](){
                    chooseWpn -> play();
                    MyPushButton * shit_wpn = new MyPushButton(":/resource/shit(3).png");
                    shit_wpn -> setParent(this);
                    shit_wpn -> move(1300, 800);
                    shit_wpn -> show();
                });
            });
        });
    }

void PlayScene::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/resource/blueBg.png");
    painter.drawPixmap(0, 0, this -> width(), this -> height(), pix);//使图片适应窗口比例
    pix.load(":/resource/playScene1.png");
    painter.drawPixmap(0, 178, pix.width(), pix.height(), pix);

    QPixmap pix_end;
    pix_end.load(":/resource/startBtn.png");

    QMediaPlayer *EatMusic = new QMediaPlayer;
    EatMusic->setMedia(QUrl::fromLocalFile("C:/Users/qzj/Desktop/Crash.mp3"));
    EatMusic->setVolume(50);


    QList <int> idx_array;//记录消失敌人序号
    for (int i=0;i<enemy_list.length();i++) {
        if (enemy_list[i]->flag_end==true)//敌人吃到萝卜
        {
            enterEnemyNum++;
            enemyNum--;//敌人总数
            //printf("%d\n",carrot->heartNum);
            enemy_list[i]->clear(&painter);
            //enemy_list.removeAt(i);
            idx_array.push_back(i);
            EatMusic -> play();
        }
        else if(enemy_list[i]->flag_die==true)
        {
            enemy_list[i]->clear(&painter);
            enemyNum--;
            money += enemy_money;//加金币
            //enemy_list.removeAt(i);
            idx_array.push_back(i);
        }
        else
        {
            enemy_list[i]->draw(&painter);
        }
    }

    //消失敌人删除
    for (int i=0;i<idx_array.length();i++) {
        enemy_list.removeAt(idx_array[i]);
    }

    //调试信息
    printf("heartNum=%d\n",carrot->heartNum);
    printf("enemyNum=%d\n",enemyNum);
    printf("enterEnemyNum=%d\n",enterEnemyNum);
}

void PlayScene::addAllEnemy()
{
    //Enemy *enemy=new Enemy(QPoint (160,110),QPoint(160,650),":/resource/shit(3).png");
    //enemy_list.push_back(enemy);
    //enemy->move();
    //第一个地图路径
    //QList <QPoint> mappath;
    mappath.push_back(QPoint (160,110));
    mappath.push_back(QPoint(160,650));
    mappath.push_back(QPoint(620,650));
    mappath.push_back(QPoint(620,450));
    mappath.push_back(QPoint(1150,450));
    mappath.push_back(QPoint(1150,650));
    mappath.push_back(QPoint(1620,650));
    mappath.push_back(QPoint(1620,110));
    add();
    //建立timer
//    QTimer *timer_enemy=new QTimer(this);
//    connect(timer_enemy,&QTimer::timeout,this,&PlayScene::add);
//      timer_enemy->start(10000);//每10ms触发updateScene,刷新界面

//    Enemy *enemy=new Enemy(mappath,":/resource/shit(3).png");
//    enemy_list.push_back(enemy);
//    update();
}

void PlayScene::add()//增加怪物
{
//   for (int i=0;i<10;i++)
//   {
//    Sleep(300);
//    Enemy *enemy=new Enemy(mappath,":/resource/shit(3).png");
//    enemy_list.push_back(enemy);
//    update();
//   }

       timer_enemy=new QTimer(this);
       connect(timer_enemy,&QTimer::timeout,this,&PlayScene::addEnemy);
         timer_enemy->start(1000);//每10ms触发updateScene,刷新界面


}

void PlayScene::addEnemy()//增加一个怪物
{
    Enemy *enemy=new Enemy(mappath, ":/resource/monster1-2.png",carrot);
    enemy_list.push_back(enemy);
    update();
    count++;//一波怪物数量

    //判断波次
    if(count==10)
    {
        timer_enemy->stop();//一波停止
        count2++;//下一波
        count=0;
        if(count2<3)
        {
        QTimer::singleShot(10*1000, this,[=](){timer_enemy->start(1000);});//停止一段时间，下一波开启
        }
    }
}


void PlayScene::updateScene()
{
    update();
}
void PlayScene::removeenemy(Enemy *enem){
    Q_ASSERT(enem);
    enemy_list.removeOne(enem);
    delete enem;
}
void PlayScene::removebullet(Bullet *bull){
    Q_ASSERT(bull);
    bullet_list.removeOne(bull);
    delete bull;

}
void PlayScene::addbullet(Bullet *bull){
    Q_ASSERT(bull);
    bullet_list.push_back(bull);
}
