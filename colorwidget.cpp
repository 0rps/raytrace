#include "colorwidget.h"

ColorWidget::ColorWidget(QWidget *parent) :
    QWidget(parent)
{
    _color = float3(0,0,0);
}

QColor ColorWidget::TranslateToQColor(const float3 color)
{
    QColor qcolor;
    qcolor.setRed(color[0]);
    qcolor.setGreen(color[1]);
    qcolor.setBlue(color[2]);
    return qcolor;
}

float3 ColorWidget::TranslateToFloat3(const QColor qcolor)
{
    return float3(qcolor.red(),qcolor.green(), qcolor.blue());
}

void ColorWidget::SetColor(const float3 &newColor)
{
    _color = newColor;
    this->update();
}

void ColorWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setPen(TranslateToQColor(_color));
    painter.setBrush(QBrush(TranslateToQColor(_color)));
    painter.drawRect(0,0,this->width()-1,this->height()-1);
}

void ColorWidget::mousePressEvent(QMouseEvent *)
{
    QColorDialog cDialog;
    QColor color = cDialog.getColor(TranslateToQColor(_color));
    if (color.isValid())
        _color = TranslateToFloat3(color);
    update();
}
