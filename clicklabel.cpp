#include "clicklabel.h"

ClickLabel::ClickLabel (QWidget* parent) : QLabel(parent) {this->setPos(0,0);}

ClickLabel::~ClickLabel() {}

void ClickLabel::mousePressEvent (QMouseEvent *event) { emit clicked(event);}

void ClickLabel::setPos(int x, int y)
{
 this->x = x;
 this->y = y;
}

int ClickLabel::get_x(){return this->x;}

int ClickLabel::get_y(){return this->y;}
