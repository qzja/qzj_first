#ifndef ENEMY_H
#define ENEMY_H

#include <QObject>
#include<QPropertyAnimation>
#include<QPoint>
#include<QPixmap>
#include<QPainter>
#include<QTimer>
#include "carrot.h"
#include"tower.h"
class tower;
struct _sRatio
{
    int type;
    int rx;
    int ry;
};

class Enemy : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QPoint currentPos READ getCurrentPos WRITE setCurrentPos)
public:
    Enemy(QPoint startPos,QPoint targetPos,QString fileName);
    Enemy(QList<QPoint> &lpath,QString fileName,Carrot * carrot);
    void draw(QPainter *painter);//绘制敌人
    void clear(QPainter *painter);
    void move();//敌人移动
    void move(QPoint from,QPoint to);//敌人移动
    QPoint getCurrentPos();//获取当前位置
    void setCurrentPos(QPoint pos);//设定当前位置
    void setTargetPos(QPoint pos);//设定结束位置
    void changePos(Enemy *enemy);
    int lifevalue;//生命值

    void updateState();
    QList<QPoint> mapPath;//路径点
    QList<_sRatio> direction;//路径点方向
    int cur_idx;//当前起始点序列
//private:
    QPoint startPos;//起始位置
    QPoint targetPos;//结束位置
    QPoint currentPos;//当前位置
    QPixmap pixmap;
    QTimer *timer_enemy;
    QList<tower*>Attacktower;
    int timespan;//刷新前进的时间
    double speed;//敌人速度
    bool flag_end;//到终点信号
    bool flag_die;//敌人死亡信号
    bool slow;

    Carrot * carrot;//萝卜对象指针
    void Attackedby(tower*mtower);
    void getout(tower *mtower);
    void Attacked(int damage);
    void beremoved();
    void slowdown();

signals:

};

#endif // ENEMY_H
