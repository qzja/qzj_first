#include "bullet.h"
#include"tower.h"
//#include "widget.h"
#include "enemy.h"
#include <QPoint>
#include <QPixmap>
#include<QPainter>
#include <QTimer>
#include<QVector2D>
#include <QtMath>
#include<QPropertyAnimation>
Bullet::Bullet(QPoint point1,QPoint point2,tower*mtower,Enemy*aim,int a,PlayScene*mplay)
{
    startp=point1;
    currentp=startp;
    targetp=point2;
    targetenemy=aim;
    k=a;
    play=mplay;
    theta=mtower->gettheta();
    damage=mtower->getdamage();
    if(a==1){
        switch(mtower->getlevel()){
        case 0:
            bullet.load(":/resource/pzpzd1.png");
            break;
        case 1:
            bullet.load(":/resource/pzpzd2.png");
            break;
        case 2:
            bullet.load(":/resource/pzpzd3.png");
            break;}
    }
    else if(a==2){
        switch(mtower->getlevel())
        {
        case 0:
            bullet.load(":/resource/shitt.png");
            break;
        case 1:
            bullet.load(":/resource/shitt.png");
            break;
        case 2:
            bullet.load(":/resource/shitt.png");
            break;}}
}
Bullet::~Bullet(){
}
void Bullet::show(QPainter * painter)
{
    QPoint relative(0,0);
    painter->save();
    painter->translate(currentp.x(),currentp.y());
    painter->rotate(theta);
    painter->drawPixmap(relative,bullet);
    painter->translate(-currentp.x(),-currentp.y());
    painter->rotate(-theta);
    painter->restore();}
void Bullet::move(){
    QPropertyAnimation *animation=new QPropertyAnimation(this,"currentp"); animation->setDuration(duration);
    animation->setStartValue(startp);
    animation->setEndValue(targetp);
    connect(animation,SIGNAL(finished()),this,SLOT(hittarget()));
    animation->start();
}
void Bullet::hittarget()
{
    if(targetenemy&&play->getenemyList().indexOf(targetenemy)!=0){
        targetenemy->Attacked(damage);
        if(k==2){
            targetenemy->slowdown();}//减速
    }
    play->removebullet(this);}
void Bullet:: setpos(QPoint p){
    currentp=p;}
