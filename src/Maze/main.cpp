#include <QApplication>

#include "mainwindow.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  Maze::Model model;
  Maze::Controller controller(&model);
  MainWindow w(&controller);
  w.show();
  return a.exec();
}
