#include "Bullet.h"

Bullet::Bullet(QObject* parent): m_x(1462/2), m_y(922-50), ySpeed(-10)
{
    connect(&bTime, &QTimer::timeout, this, &Bullet::updateBullet);
    bTime.start(16);
}

void Bullet::updateBullet()
{
    setY(m_y + ySpeed);
}
