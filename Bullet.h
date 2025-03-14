#ifndef BULLET_H
#define BULLET_H

#include <QObject>
#include <QTimer>

class Bullet: public QObject
{
    Q_OBJECT
    Q_PROPERTY(double x READ x WRITE setX NOTIFY xChanged)
    Q_PROPERTY(double y READ y WRITE setY NOTIFY yChanged)
public:
    Bullet(QObject* parent = nullptr);

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

public slots:
    void updateBullet();

signals:
    void xChanged();
    void yChanged();

private:
    double m_x;
    double m_y;
    double ySpeed;
    QTimer bTime;
};
#endif // BULLET_H
