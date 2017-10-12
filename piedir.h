#ifndef PIEDIR_H
#define PIEDIR_H

#include <QWidget>

class PieDir: public QWidget
{
    Q_OBJECT
public:
    explicit PieDir(QWidget *parent = 0);
protected:
    void paintEvent(QPointEvent *);

};

#endif // PIEDIR_H
