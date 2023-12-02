#include "mainwindow.h"

#include "ui_mainwindow.h"

MainWindow::MainWindow(Maze::Controller* c)
    : ui(new Ui::MainWindow), controller_(c) {
  ui->setupUi(this);
  grid_ = new Maze::GraphicsGrid(ui->widget_grid);
  ui->Button_Solution->setEnabled(false);
  ui->actionSave_maze_as_txt->setEnabled(false);
  // on_Button_Generate_clicked();
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_actionOpen_File_triggered() {
  QString filename = QFileDialog::getOpenFileName(
      this, "Choose the file", QDir::homePath(), "maze file (*.txt);;");
  try {
    controller_->ParseFromFileIntoMatrixes(filename.toStdString());
  } catch (const std::runtime_error& e) {
    QMessageBox::critical(nullptr, "Error", e.what());
    return;
  }
  grid_->DrawMaze(controller_->GetVWalls(), controller_->GetHWalls(),
                  controller_->GetVSize(), controller_->GetHSize());
  ui->Button_Solution->setEnabled(true);
  ui->actionSave_maze_as_txt->setEnabled(true);
}

void MainWindow::on_Button_Clean_clicked() {
  grid_->CleanGrid();
  ui->Button_Solution->setEnabled(false);
  ui->actionSave_maze_as_txt->setEnabled(false);
}

void MainWindow::on_Button_Generate_clicked() {
  grid_->CleanGrid();
  controller_->GenerateRandomMaze(ui->spinBox_height->value(),
                                  ui->spinBox_width->value());
  grid_->DrawMaze(controller_->GetVWalls(), controller_->GetHWalls(),
                  controller_->GetVSize(), controller_->GetHSize());
  SetMaxInSpinBox();
  ui->Button_Solution->setEnabled(true);
  ui->actionSave_maze_as_txt->setEnabled(true);
}

void MainWindow::on_Button_Solution_clicked() {
  Maze::Coordinate point_from{
      static_cast<size_t>(ui->spinBox_x_point_1->value()),
      static_cast<size_t>(ui->spinBox_y_point_1->value())};
  Maze::Coordinate point_to{static_cast<size_t>(ui->spinBox_x_point_2->value()),
                           static_cast<size_t>(ui->spinBox_y_point_2->value())};
  grid_->DrawMaze(controller_->GetVWalls(), controller_->GetHWalls(),
                  controller_->GetVSize(), controller_->GetHSize());
  grid_->DrawSolution(controller_->GetVSize(), controller_->GetHSize(),
                      controller_->GetSolvedMaze(point_from, point_to));
}

void MainWindow::SetMaxInSpinBox() {
  ui->spinBox_y_point_1->setMaximum(controller_->GetHSize());
  ui->spinBox_y_point_2->setMaximum(controller_->GetHSize());
  ui->spinBox_x_point_1->setMaximum(controller_->GetVSize());
  ui->spinBox_x_point_2->setMaximum(controller_->GetVSize());
}

void MainWindow::on_actionSave_maze_as_txt_triggered() {
  QString file_path = QFileDialog::getSaveFileName(
      this, "Сохранить файл", QDir::homePath(), "Текстовые файлы (*.txt)");
  if (!file_path.isEmpty()) {
    controller_->SaveInFile(file_path.toStdString());
  } else {
    QMessageBox::critical(nullptr, "Error", "Save been cancel");
    return;
  }
}
