#ifndef PLAYSCENE_H
#define PLAYSCENE_H

#include <QMainWindow>
#include <QList>
#include<enemy.h>
#include"bullet.h"
#include"tower.h"
#include <QMediaPlayer>

class Bullet;
class Enemy;
class tower;

QT_BEGIN_NAMESPACE
namespace Ui { class playscene; }
QT_END_NAMESPACE

class PlayScene : public QMainWindow
{
    Q_OBJECT
public:
    //explicit PlayScene(QWidget *parent = nullptr);
    PlayScene(int level);
    int levelNum; //记录所选关卡
    //重写paintEvent
    void paintEvent(QPaintEvent *);

    QMediaPlayer * chooseWpn;

    Carrot * carrot;
    int count;//每波计数
    int count2;//波次计数
    int enemyNum;//敌人总数
    int enterEnemyNum;//最多进入敌人数量
    int money;//金币总数
    int enemy_money;//敌人死了加金币数
    void addAllEnemy();//添加敌人，敌人出现
    void add();
    void addEnemy();
    QList <QPoint> mappath;
    void updateScene();//更新界面，使敌人运动连贯
    QList<Enemy*>enemy_list;
    QTimer *timer_enemy;
    QTimer * judge;
    int getmoney(){return money;}
    QList<Enemy*>getenemyList(){return enemy_list;}
    void removeenemy(Enemy*enem);
    void removebullet(Bullet*bull);
    QList<Bullet*>bullet_list;
    void addbullet(Bullet*bull);
    tower *t;
    QPainter*painter;
signals:


};

#endif // PLAYSCENE_H
