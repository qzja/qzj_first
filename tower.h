#ifndef TOWER_H
#define TOWER_H
#include"enemy.h"
//#include"widget.h"
#include"playscene.h"
#include"bullet.h"
//class Widget;
class PlayScene;
//class Bullet;
//class QTimer;
class Enemy;
class tower:QObject{
    Q_OBJECT
public:
    tower(QPoint,PlayScene*,int);
    ~tower();
    void show(QPainter *painter);
    void move();
    //void setaimstone(stone*s);
    void Attack();//攻击小怪兽
    void targetkilled();
    void removebullet();
    //bool checkstonein(QPoint p);
    void checkenemyin();
    void enemyout();
    //void removeaimstone(){aimstone=NULL;};
    void getremoved();
    int getdamage();
    int gettheta(){return theta;}
    int getlevel(){return level;}
    int getmoney(){return money;}
    int getrange(){return range;}
    void uplevel(){levelup=true;}
    bool getlevelup(){return levelup;}
    void hideuplevel(){levelup=false;}
    void addlevel(){level++;}
    QPoint getcoor(){return coor;}
    Enemy*getattacking();
    //stone*getaimstone(){return aimstone;}
    //void doublespeed(){interval/=2;}
    //void normalspeed(){interval*=2;}
    //protected:
    QImage m_tower;
    QPoint coor;//炮塔坐标
    QPoint aimpoint;
    QTimer* t;
    //Widget *w;
    PlayScene*play;
    bool active=false;
    Enemy *aimenemy;
    //stone *aimstone;
    int kind;//判断炮塔类型
    int level=0;
    int money;
    int range;//攻击范围
    int damage;
    int interval=1000;//间隔时间
    bool levelup=false;
    double theta=90;//旋转角度
protected slots:
    void shoot();};

#endif // TOWER_H
