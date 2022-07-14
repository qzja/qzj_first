#include "enemy.h"


Enemy::Enemy(QPoint startPos,QPoint targetPos,QString fileName) : QObject(0),pixmap(fileName)
{
    this->currentPos=startPos;
    this->startPos=startPos;
    this->targetPos=targetPos;


}

Enemy::Enemy(QList<QPoint> &lpath,QString fileName,Carrot * carrot):
    QObject(0),pixmap(fileName),carrot(carrot)
{
    timespan=10;
    speed=3;//初始值
    lifevalue=100;//敌人生命值
    flag_end=false;//敌人没到萝卜
    flag_die=false;//敌人没死
    //mapPath=lpath;
    int len= lpath.length();
    for(int i=0;i<len;i++)
    {
        mapPath.push_back(lpath[i]);
    }
    //计算方向
    _sRatio temp;
    for(int i=0;i<len-1;i++)
    {
        int dx=mapPath[i+1].x()-mapPath[i].x();
        int dy=mapPath[i+1].y()-mapPath[i].y();


        if (dx>0)    {
            temp.rx=1;
            temp.ry=0;
            temp.type=1;
        }

        if (dx<0)    {
            temp.rx=-1;
            temp.ry=0;
            temp.type=2;
        }

        if (dy>0)    {
            temp.rx=0;
            temp.ry=1;
            temp.type=3;
        }

        if (dy<0)    {
            temp.rx=0;
            temp.ry=-1;
            temp.type=4;
        }
        direction.push_back(temp);
    }
    temp.rx=0;
    temp.ry=0;
    temp.type=5;
    direction.push_back(temp);

    timer_enemy=new QTimer(this);
    connect(timer_enemy,&QTimer::timeout,this,&Enemy::updateState);
      timer_enemy->start(timespan);//每timespan触发updateScene,刷新界面
      int num= mapPath.length();
      this->currentPos=mapPath[0];
      this->startPos=mapPath[0];
      this->targetPos=mapPath[num-1];
      cur_idx=0;
}

void Enemy::draw(QPainter *painter)
{
    painter->drawPixmap(currentPos,pixmap);

}

void Enemy::clear(QPainter *painter)
{
    painter->drawPixmap(currentPos,QPixmap());

}

void Enemy::updateState()
{

    //计算实时位置

    int ddx =speed*timespan;
    int ddy=speed*timespan;

    int x=currentPos.x()+ddx*direction[cur_idx].rx;
    int y=currentPos.y()+ddy*direction[cur_idx].ry;
    QPoint next(x,y);

    //如果下一步超出拐点，走到拐点处
    if (direction[cur_idx].type == 1 && next.x()>=mapPath[cur_idx+1].x())
    {
        //d_x=next.x()-mapPath[cur_idx+1].x();
        next=mapPath[cur_idx+1];
        cur_idx++;
    }
    if (direction[cur_idx].type == 2 && next.x()<=mapPath[cur_idx+1].x())
    {
        //d_x=next.x()-mapPath[cur_idx+1].x();
        next=mapPath[cur_idx+1];
        cur_idx++;
    }
    if (direction[cur_idx].type == 3 && next.y()>=mapPath[cur_idx+1].y())
    {
        //d_x=next.x()-mapPath[cur_idx+1].x();
        next=mapPath[cur_idx+1];
        cur_idx++;
    }
    if (direction[cur_idx].type == 4 && next.y()<=mapPath[cur_idx+1].y())
    {
        //d_x=next.x()-mapPath[cur_idx+1].x();
        next=mapPath[cur_idx+1];
        cur_idx++;
    }
    int len=mapPath.length();

    //到终点
    if (cur_idx>=len-1)
    {
        //结束动作
        //printf("end");
        carrot->heartNum--;
        flag_end=true;
        if(timer_enemy->isActive()==true)
        {
            timer_enemy->stop();
        }
    }


    //判断血量，消失
    if (lifevalue<=0)
    {
        flag_die=true;
        //printf("end");
    }


    //移动，显示，更新
    move(currentPos,next);
    currentPos=next;
    //
}

void Enemy::move()
{
    QPropertyAnimation *animation=new QPropertyAnimation(this,"currentPos");
    animation->setDuration(2000);
    animation->setStartValue(startPos);
    animation->setEndValue(targetPos);
    animation->start();

}

void Enemy::move(QPoint from,QPoint to)
{
    QPropertyAnimation *animation=new QPropertyAnimation(this,"currentPos");
    animation->setDuration(timespan);
    animation->setStartValue(from);
    animation->setEndValue(to);
    animation->start();

}

QPoint Enemy::getCurrentPos()//获取当前位置
{
    return this->currentPos;
}

void Enemy::setCurrentPos(QPoint pos)//设定当前位置
{
    this->currentPos=pos;
}

void Enemy::setTargetPos(QPoint pos)//设定结束位置
{
    this->targetPos=pos;
}

void Enemy::changePos(Enemy *enemy)
{
    int x=this->currentPos.x();
    int y=this->currentPos.y();
    if(x==160 &&y==650)
    {
        enemy->setTargetPos(QPoint(360,650));
    }
    enemy->move();
}

void Enemy::Attackedby(tower *mtower){
    Attacktower.push_back(mtower);
}
void Enemy::beremoved(){
    if(Attacktower.empty())
    {
        return ;
    }
    else
    {
        foreach(tower*mtower,Attacktower)
            mtower->targetkilled();

    }
}
void Enemy::getout(tower *mtower){
    Attacktower.removeOne(mtower);
}
void Enemy::Attacked(int damage){
    lifevalue-=damage;
    if(lifevalue<=0){
        beremoved();
    }
}
void Enemy::slowdown(){
    speed*=0.75;
    slow=true;
}


