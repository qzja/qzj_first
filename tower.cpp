#include "tower.h"
#include<QPoint>
#include<QPixmap>
#include<QPainter>
#include <QTimer>
#include<QVector2D>
#include<QtMath>
tower::tower(QPoint p,PlayScene*plays,int a)
{
    kind=a;
    coor=p;//坐标
    aimenemy=NULL;
    play=plays;
    t=new QTimer(this);
    connect(t,SIGNAL(timeout()),this,SLOT(shoot()));
    damage=getdamage();
    switch(level)
    {
    case 0:
        range=200;
    case 1:
        range=250;
    case 2:
        range=300;
    }//攻击范围
    switch(kind){
    case 1:
        money=100;
    case 2:
        money=120;
    }//升级耗费
}
tower::~tower(){
    delete t;
    play=NULL;
    aimenemy=NULL;
}
void tower::show(QPainter*painter)
{
    if(kind==1){
        switch(level){
        case 0:
            m_tower.load(":/resource/pingzipao1.png");
            break;
        case 1:
            m_tower.load(":/resource/pingzipao2.png");
            break;
        case 2:
            m_tower.load(":/resource/pingzipao3.png");
            break;
        }
    }//瓶子炮
    else if(kind==2){
        switch(level){
        case 0:
            m_tower.load(":/resource/shit(1).png");
            break;
        case 1:
            m_tower.load(":/resource/shit(2).png");
            break;
        case 2:
            m_tower.load(":/resource/shit(3).png");
            break;
        }
    }
    painter->save();
    if(levelup)
    {
        QPixmap up;
        painter->drawPixmap(coor.x()-50,coor.y()-40,130,130,QPixmap());
        if(level==0)
        {
            if(play->getmoney()>=180)
            {
                up.load(":/resource/shenji1.png");//可以升级
            }
            else
            {
                up.load(":/resource/bushenji1.png");//不可升级
            }
        }
        if(level==1){
            if(play->getmoney()>=260){
                up.load(":/resource/shenji2.png");//可以升级
            }
            else{
                up.load(":/resource/bushenji2.png");//不可升级
            }
        }
        painter->drawPixmap(coor.x(),coor.y()-30,30,30,up);
    }
    painter->translate(coor.x()*m_tower.width()/2,coor.y()+m_tower.height()/2); painter->rotate(theta-135);
    painter->drawImage(-m_tower.width()/2,-m_tower.height()/2,m_tower);
    painter->translate(-coor.x()-m_tower.width()/2,-coor.y()-m_tower.height()/2); painter->rotate(135-theta);
    painter->restore();
}//使武器对准敌人或者障碍物
void tower::move()
{
    if(aimenemy){
        double direct_x=coor.x()-aimpoint.x(),direct_y=coor.y()-aimpoint.y();
        if(aimpoint.x()>0){
            if(abs(direct_x)>abs(direct_y)){
                theta=qAtan(direct_y/direct_x)*180/3.1416;
                if(direct_x>0)theta+=180;
            }
            else
            {
                theta=-90-qAtan(direct_x/direct_y)*180/3.1416;
                if(direct_y<0)theta+=180;
            }
        }
        theta+=220;
    }
}
void tower::Attack(){
    t->start(interval);
}
void tower::shoot()
{
    if(aimenemy){
        Bullet *b=new Bullet(coor,aimpoint,this,aimenemy,kind,play);
        b->move();
        play->addbullet(b);
    }
}
void tower::targetkilled()
{
    if(aimenemy){
        aimenemy=NULL;}
    t->stop();
}

void tower::enemyout()
{
    aimenemy->getout(this);
    if(aimenemy)
    {
        aimenemy=NULL;}
    t->stop();
}


int tower:: getdamage(){
    switch(level){
    case 0:
        damage=10;
        break;
    case 1:
        damage=25;
        break;
    case 2:
        damage=50;
        break;}
    return damage;
}

Enemy*tower::getattacking()
{return aimenemy;}
void tower::checkenemyin(){
    //if(aimstone);
    if(aimenemy){
        aimpoint=aimenemy->getCurrentPos();
        double dx=coor.x()-aimpoint.x();
        double dy=coor.y()-aimpoint.y();
        double dis=sqrt(dx*dx+dy*dy);
        if(dis>=range){
            enemyout();}
    }
    else
    {
        QList<Enemy*>enemyList=play->getenemyList();
        foreach(Enemy * menemy,enemyList){
            double dx=coor.x()-menemy->getCurrentPos().x();
            double dy=coor.y()-menemy->getCurrentPos().y();
            double dis=sqrt(dx*dx+dy*dy);
            if(dis<=range){
                aimenemy=menemy;
                aimpoint=aimenemy->getCurrentPos();
                aimenemy->Attackedby(this);
                Attack();
                break;}
        }
    }//下一个敌人
}
