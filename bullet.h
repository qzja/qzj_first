#ifndef BULLET_H
#define BULLET_H
#include"enemy.h"
//#include"widget.h"
#include"tower.h"
class Enemy;
//class Widget;
class tower;
class PlayScene;
class Bullet:public QObject{
    Q_OBJECT
    Q_PROPERTY(QPoint currentp READ getpos WRITE setpos)//用于qpropertyanimation
public:
    Bullet(QPoint point1,QPoint point2,tower*mtower,Enemy*aim,int a,PlayScene*mplay);
    //Bullet(QPoint point1,QPoint point2,tower*mtower,stone*aim,Widget *mw,int a);
    Bullet(){};
    ~Bullet();
    void show(QPainter * painter);
    void show2(QPainter * painter);
    void show3(QPainter * painter);
    void move();
    QPoint getpos(){return currentp;}
    void setpos(QPoint p);
    //void doublespeed(){duration/=2;}
    //void normalspeed(){duration*=2;}
private:
    QPoint startp;
    QPoint currentp;
    QPoint targetp;
    QPixmap bullet;
    double theta;//旋转角度
    int damage;
    int duration=1000;//运动时间
    int k;
    //Widget *w;
    tower*mtower;
    Enemy*targetenemy;
    PlayScene*play;
    //stone*targetstone;
private slots:
    void hittarget();};
#endif // BULLET_H
