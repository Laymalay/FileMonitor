#include "piedir.h"
#include <QPainter>
PieDir::PieDir()
{

}

void PieDir::paintEvent(QPointEvent *)
{
    QPainter painter(this);
    QRectF size = QRectF (10,10, this->width()-10, this->height()-10);


}
