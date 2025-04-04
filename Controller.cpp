#include "Controller.h"

Controller::Controller(QObject* parent): m_x(1450/2), m_y(922-100), xSpeed(10), minX(0), maxX(1450), bottomY(922-100)
{
    //&Controller
    connect(&time, &QTimer::timeout, this, &Controller::updateState);
    time.start(16); //60fps frame per second.

    connect(&move, &QTimer::timeout, this, &Controller::updateMovement);
    move.start(16); //60fps frame per second.

    connect(&startE, &QTimer::timeout, this, &Controller::createEnemy);
    startE.start(1000 + rand() % 2000); //1-3 seconds
}

void Controller::moveLeft()
{
    moveDirection = -1;
    if(!move.isActive())
    {
        move.start();
    }

    // setX(m_x - xSpeed);
    // if(m_x < minX)
    // {
    //     setX(minX);
    // }
}

void Controller::moveRight()
{
    moveDirection = 1;
    if(!move.isActive())
    {
        move.start();
    }
    // {
    //     setX(m_x + xSpeed);
    //     if(m_x > maxX)
    //     {
    //         setX(maxX);
    //     }
    // }
}

void Controller::stopMovement()
{
    moveDirection = 0;
    move.stop();
}

QString Controller::showScore()
{
    return QString::number(score());
}

void Controller::restartGame()
{
    for(Enemy* e: enemyList)
    {
        delete e;
    }
    enemyList.clear();

    for(Bullet* b: bulletList)
    {
        delete b;
    }
    bulletList.clear();

    emit enemyChanged();
    emit bulletChanged();

    setX(1462/2);
    setY(922-50);

    setScore(0);
    emit scoreChanged();

    emit xChanged();
    emit yChanged();
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
    newBullet->setX(m_x+35);
    newBullet->setY(m_y);
    bulletList.append(newBullet);
    emit bulletChanged();
    qInfo()<<"Fired bullets";
}

void Controller::createEnemy()
{
    Enemy* newEnemy = new Enemy();
    newEnemy->setX(rand() % 1450);
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

    for(Enemy* e : enemyList)
    {
        if(e->y() > bottomY)
        {
            emit gameOver();
            qInfo()<< "Game Over";
            return;
        }

        double enemyLeft = e->x();
        double enemyRight = e->x() + 50;
        double enemyTop = e->y();
        double enemyBottom = e->y() + 50;

        double playerLeft = m_x;
        double playerRight = m_x + 50;
        double playerTop = m_y;
        double playerBottom = m_y + 50;

        if(enemyRight > playerLeft && enemyLeft < playerRight &&
            enemyTop < playerBottom && enemyBottom > playerTop)
        {
            emit gameOver();
            qInfo()<< "Game Over";
            return;
        }
    }

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
        //Debuging message
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
                setScore(score() + 10);
                emit scoreChanged();
            }
        }
    }
}

void Controller::updateMovement()
{
    if(moveDirection == -1 && m_x>minX)
    {
        setX(m_x - xSpeed);
    }
    if(moveDirection == 1 && m_x<maxX)
    {
        setX(m_x + xSpeed);
    }
    if(moveDirection == 0)
    {
        setX(m_x);
    }
}
