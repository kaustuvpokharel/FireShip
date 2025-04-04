#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QTimer>
#include <Bullet.h>
#include <Enemy.h>
#include <vector>
#include <QDebug>
#include <QQmlListProperty>


class Controller: public QObject
{
    Q_OBJECT

    Q_PROPERTY(double x READ x WRITE setX NOTIFY xChanged)
    Q_PROPERTY(double y READ y WRITE setY NOTIFY yChanged)
    Q_PROPERTY(QQmlListProperty<Bullet> bullets READ bullets NOTIFY bulletChanged)
    Q_PROPERTY(QQmlListProperty<Enemy> enemies READ enemies NOTIFY enemyChanged)
    Q_PROPERTY(double score READ score WRITE setScore NOTIFY scoreChanged)

public:
    Controller(QObject* parent = nullptr);

    double x()
    {
        return m_x;
    }
    double y()
    {
        return m_y;
    }

    void setX(double value)
    {
        if(m_x != value)
        {
            m_x = value;
            emit xChanged();
        }
    }

    void setY(double value)
    {
        if(m_y != value)
        {
            m_y = value;
            emit yChanged();
        }
    }

    double score()
    {
        return m_score;
    }

    void setScore(double value)
    {
        if(m_score != value)
        {
            m_score = value;
            emit scoreChanged();
        }
    }

    Q_INVOKABLE void moveLeft();
    Q_INVOKABLE void moveRight();
    Q_INVOKABLE void applyThrust();
    Q_INVOKABLE void fireBullet();
    Q_INVOKABLE void createEnemy();
    Q_INVOKABLE void stopMovement();
    Q_INVOKABLE QString showScore();
    Q_INVOKABLE void restartGame();


    //This helps you expose our c++ objects or classes to qmls
    QQmlListProperty <Bullet> bullets()
    {
        return QQmlListProperty(this, &bulletList);
    }

    QQmlListProperty <Enemy> enemies()
    {
        return QQmlListProperty(this, &enemyList);
    }

public slots:
    void updateState();
    void deleteBullet(Bullet* bullet);
    void deleteEnemy(Enemy *enemy);
    void checkCollision();
    void updateMovement();

signals:
    void xChanged();
    void yChanged();
    void bulletChanged();
    void enemyChanged();
    void scoreChanged();
    void gameOver();

private:
    double m_x; //current position of our rect on x dimension
    double m_y;
    double xSpeed;
    double minX;
    double maxX;
    double bottomY;
    double ySpeed;
    double maxThrust = -15;
    double gravity = 0.5;
    QTimer time;
    QTimer startE;
    QList<Bullet*> bulletList;
    QList<Enemy*> enemyList;
    QTimer move;

    int moveDirection;
    double m_score = 0;
};

#endif // CONTROLLER_H
