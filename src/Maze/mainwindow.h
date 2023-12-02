#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QFileDialog>
#include <QMainWindow>
#include <QMessageBox>

#include "controller.h"
#include "graphicsgrid.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(Maze::Controller *c);
  ~MainWindow();

 private slots:
  void on_actionOpen_File_triggered();
  void on_Button_Clean_clicked();
  void on_Button_Generate_clicked();
  void on_Button_Solution_clicked();
  void SetMaxInSpinBox();

  void on_actionSave_maze_as_txt_triggered();

 private:
  Ui::MainWindow *ui;
  Maze::Controller *controller_;
  Maze::GraphicsGrid *grid_;
};
#endif  // MAINWINDOW_H
