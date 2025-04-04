#include "Enemy.h"

Enemy::Enemy(QObject* parent): m_x(rand() % 1450), m_y(-50), ySpeed(1), m_index(rand()%5)
{
    connect(&eTime, &QTimer::timeout, this, &Enemy::updateEnemy);
    eTime.start(50);
}

void Enemy::updateEnemy()
{
    setY(m_y + ySpeed);
}
