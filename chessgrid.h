#ifndef CHESSGRID_H
#define CHESSGRID_H

#include <QWidget>
#include <QtWidgets>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QFrame>
#include <QHBoxLayout>
#include "Playing_field.h"
#include "clicklabel.h"

class ChessGrid : public QWidget {
Q_OBJECT
 public:
     ChessGrid(QWidget *parent = 0);
     ~ChessGrid();
private:
     Playing_field* fld;
     ClickLabel *squares[8][8];
     QPushButton *saveBtn;
     QPushButton *resetBtn;
     QLabel *result;

     void update_grid();
private slots:
     void labelClick(QMouseEvent*);
     void resetBtnClick();
     void saveBtnClick();
};
#endif // CHESSGRID_H
