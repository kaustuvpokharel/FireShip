#include "Controller.h"

Controller::Controller(QObject* parent): m_x(1462/2), m_y(922-50), xSpeed(10), minX(0), maxX(1462), bottomY(922-50)
{
    //&Controller
    connect(&time, &QTimer::timeout, this, &Controller::updateState);
    time.start(16); //60fps frame per second.
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
    Bullet* newBullet = new Bullet();
    std::vector<Bullet*> bulletList;
    bulletList.push_back(newBullet);
    qInfo()<<"Fired bullets";
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

    emit yChanged();
}
