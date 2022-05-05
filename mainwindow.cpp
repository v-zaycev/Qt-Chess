#include "mainwindow.h"

#include <QCoreApplication>

MainWindow::MainWindow(QWidget *parent)

: QMainWindow(parent)

{

// создаем кнопку
m_button = new QPushButton("My Button", this);
// устанавливаем размер и положение кнопки
m_button->setGeometry(QRect(QPoint(100, 100),
QSize(200, 50)));

// подключаем сигнал к соответствующему слоту

connect(m_button, SIGNAL (released()), this, SLOT (handleButton()));

}

void MainWindow::handleButton() {

// меняем текст
m_button->setText("Example");
// изменяем размер кнопки
m_button->resize(100,100);

}

MainWindow::~MainWindow() {

}
