#ifndef DRAWWAVE_H
#define DRAWWAVE_H

#include <QWidget>
#include <QBasicTimer>

class DrawWave : public QWidget
{
    Q_OBJECT
public:
    explicit DrawWave(QWidget *parent = nullptr, QColor color1 = Qt::green, QColor color2 = Qt::gray);
    void paintEvent( QPaintEvent *event ) override;
    void timerEvent( QTimerEvent *event ) override;
    void Slot_Data_Handle( int data );
    void Draw_Wave( QPainter *painter );
    void Draw_Wave_To_Pixmap( int data );
    void Send( int data );

    int currentX;
    int currentY;
    int lastX;
    int lastY;

    QColor penColor;
    QColor backgroundColor;

    QBasicTimer *basicTimer;
    QPixmap *pixmap;

signals:

};

#endif // DRAWWAVE_H
