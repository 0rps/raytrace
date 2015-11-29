#ifndef MYPICTURE_H
#define MYPICTURE_H

#include <QWidget>
#include <QImage>
#include <QPainter>
#include "MyVector3.h"

class MyPicture : public QWidget
{
    Q_OBJECT
public:
    explicit MyPicture(QWidget *parent = 0);

public:
    QImage _img;
    void paintEvent(QPaintEvent *);
    void SetImage( float3** matrix);
signals:
    
public slots:
    
};

#endif // MYPICTURE_H
