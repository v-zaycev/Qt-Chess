#include <QApplication>
#include <QWidget>
#include <QtWidgets>
#include <QGridLayout>
#include <QLabel>
#include "Playing_field.h"
#include "chessgrid.h"

int main(int argc, char *argv[]) {

  QApplication app(argc, argv);

  ChessGrid window;

  window.setFixedHeight(700);
  window.setFixedWidth(800);
  window.setWindowTitle("Chess");

  window.show();

  return app.exec();
}
