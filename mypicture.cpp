#include "mypicture.h"
#include <QColor>

MyPicture::MyPicture(QWidget *parent) :
    QWidget(parent)
{
    _img = QImage(500,500,QImage::Format_RGB32);
}

void MyPicture::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawImage(QPoint(0,0), _img);
}

void MyPicture::SetImage(float3 **matrix)
{
    for (int i = 0; i < 500 ; i++)
        for (int j =0; j < 500; j++)
        {
            _img.setPixel(j,500-1-i, qRgb(matrix[i][j][0],matrix[i][j][1],matrix[i][j][2]));
        }
}
