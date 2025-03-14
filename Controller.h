#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QTimer>
#include <Bullet.h>
#include <vector>
#include <QDebug>


class Controller: public QObject
{
    Q_OBJECT

    Q_PROPERTY(double x READ x WRITE setX NOTIFY xChanged)
    Q_PROPERTY(double y READ y WRITE setY NOTIFY yChanged)

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

    Q_INVOKABLE void moveLeft();
    Q_INVOKABLE void moveRight();
    Q_INVOKABLE void applyThrust();
    Q_INVOKABLE void fireBullet();

public slots:
    void updateState();

signals:
    void xChanged();
    void yChanged();

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
};

#endif // CONTROLLER_H
