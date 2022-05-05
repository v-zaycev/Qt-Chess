#ifndef CLICKABLELABEL_H
#define CLICKABLELABEL_H

#include <QLabel>
#include <QMouseEvent>

class ClickLabel : public QLabel {
 Q_OBJECT
public:
 explicit ClickLabel (QWidget* parent=0);
 ~ClickLabel();
signals:
 void clicked(QMouseEvent *);
protected:
 void mousePressEvent (QMouseEvent *event);
private:
    int x;
    int y;
public:
    void setPos(int x, int y);
    int get_x();
    int get_y();
};

#endif // CLICKABLELABEL_H
