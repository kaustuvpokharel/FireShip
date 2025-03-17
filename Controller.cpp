#include "Controller.h"

Controller::Controller(QObject* parent): m_x(1462/2), m_y(922-50), xSpeed(10), minX(0), maxX(1462), bottomY(922-50)
{
    //&Controller
    connect(&time, &QTimer::timeout, this, &Controller::updateState);
    time.start(16); //60fps frame per second.

    connect(&startE, &QTimer::timeout, this, &Controller::createEnemy);
    startE.start(1000 + rand() % 2000); //1-3 seconds
}

void Controller::moveLeft()
{
    setX(m_x - xSpeed);
    if(m_x < minX)
    {
        setX(minX);
    }
}

void Controller::moveRight()
{
    {
        setX(m_x + xSpeed);
        if(m_x > maxX)
        {
            setX(maxX);
        }
    }
}

void Controller::applyThrust()
{
    ySpeed = maxThrust;
    if(m_y < bottomY/1.5)
    {
        ySpeed = 0;
    }
}

void Controller::fireBullet()
{
    Bullet* newBullet = new Bullet(this, this);
    newBullet->setX(m_x+20);
    newBullet->setY(m_y);
    bulletList.append(newBullet);
    emit bulletChanged();
    qInfo()<<"Fired bullets";
}

void Controller::createEnemy()
{
    Enemy* newEnemy = new Enemy();
    newEnemy->setX(rand() % 1512);
    newEnemy->setY(-50);
    enemyList.append(newEnemy);

    startE.start(1000 + rand() % 2000);
    emit enemyChanged();
}
//slot
void Controller::updateState()
{
    m_y += ySpeed;
    ySpeed += gravity;

    if(m_y > bottomY)
    {
        m_y = bottomY;
    }

    checkCollision();

    emit yChanged();
}

void Controller::deleteBullet(Bullet *bullet)
{
    int index = bulletList.indexOf(bullet);
    if(index != -1)
    {
        delete bulletList[index];
        //deletes the memory
        bulletList.removeAt(index);
        //this deletes the place inside list of the instance
        emit bulletChanged();
        qInfo()<<"Bullet Destroyed";
    }
}

void Controller::deleteEnemy(Enemy *enemy)
{
    int index = enemyList.indexOf(enemy);
    if(index != -1)
    {
        delete enemyList[index];
        //deletes the memory
        enemyList.removeAt(index);
        //this deletes the place inside list of the instance
        emit enemyChanged();
        qInfo()<<"enemy Destroyed";
    }
}

void Controller::checkCollision()
{
    for(int i = bulletList.size() -1; i >= 0; i--)
    {
        Bullet* bullet = bulletList[i];

        for(int j = enemyList.size()-1; j >=0; j--)
        {
            Enemy* enemy = enemyList[j];

            double bulletLeft = bullet->x();
            double bulletRight = bullet->x() + 10;
            double bulletTop = bullet->y();
            double bulletBottom = bullet->y() + 30;

            double enemyLeft = enemy->x();
            double enemyRight = enemy->x() + 50;
            double enemyTop = enemy->y();
            double enemyBottom = enemy->y() + 50;

            if(bulletRight > enemyLeft && bulletLeft < enemyRight &&
                bulletTop < enemyBottom && bulletBottom > enemyTop)
            {
                deleteBullet(bullet);
                deleteEnemy(enemy);

                break;
            }
        }
    }
}
