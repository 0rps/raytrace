#ifndef COLORWIDGET_H
#define COLORWIDGET_H

#include <QWidget>
#include "MyVector3.h"
#include <QPainter>
#include <QColorDialog>

class ColorWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ColorWidget(QWidget *parent = 0);

public:
    float3 _color;
public:
    QColor TranslateToQColor(const float3 color);
    float3 TranslateToFloat3(const QColor qcolor);
    void SetColor(const float3 &newColor);
signals:
    
public slots:
    void mousePressEvent(QMouseEvent *);
    void paintEvent(QPaintEvent *);
};

#endif // COLORWIDGET_H
