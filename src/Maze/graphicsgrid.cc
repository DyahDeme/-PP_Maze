#include "graphicsgrid.h"

#include <QGraphicsLineItem>
#include <QGraphicsScene>

namespace Maze {

GraphicsGrid::GraphicsGrid(QWidget *parent) : QGraphicsView(parent) {
  scene_ = new QGraphicsScene(this);
  setScene(scene_);
  int sceneWidth = 500;
  int sceneHeight = 500;
  scene_->setSceneRect(0, 0, sceneWidth, sceneHeight);
  scene_->setBackgroundBrush(QColor(200, 200, 200));
  setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

  DrawArea();
}

void GraphicsGrid::DrawArea() {
  QGraphicsRectItem *border = new QGraphicsRectItem(scene_->sceneRect());
  QPen pen;
  pen.setWidth(2);
  border->setPen(pen);

  scene_->addItem(border);
}

void GraphicsGrid::DrawMaze(std::vector<std::vector<bool>> v_walls,
                            std::vector<std::vector<bool>> h_walls, int v_size,
                            int h_size) {
  CleanGrid();
  double indent_by_x = 500 / static_cast<double>(v_size);
  double indent_by_y = 500 / static_cast<double>(h_size);
  for (int i = 0; i < v_walls.size(); i++)
    for (int j = 0; j < h_walls[0].size(); j++)
      if (v_walls[i][j] == true) {
        QGraphicsRectItem *wall =
            scene_->addRect((j + 1) * indent_by_x, i * indent_by_y, 2,
                            indent_by_y, QPen(Qt::black), QBrush(Qt::black));
      }
  for (int i = 0; i < v_walls.size(); i++)
    for (int j = 0; j < h_walls[0].size(); j++)
      if (h_walls[i][j] == true) {
        QGraphicsRectItem *wall =
            scene_->addRect((j)*indent_by_x, (i + 1) * indent_by_y, indent_by_x,
                            2, QPen(Qt::black), QBrush(Qt::black));
      }
}

void GraphicsGrid::CleanGrid() { scene_->clear(); }

void GraphicsGrid::DrawSolution(int v_size, int h_size, Coordinates path) {
  QGraphicsRectItem *solution_;
  double indent_by_x = 500 / static_cast<double>(v_size);
  double indent_by_y = 500 / static_cast<double>(h_size);
  while (!path.empty()) {
    Coordinate point_prev{path.top().x + 1, path.top().y + 1};
    path.pop();
    if (path.empty()) return;
    int change_x = path.top().x + 1 - point_prev.x;
    int change_y = path.top().y + 1 - point_prev.y;
    if (change_y == -1) {
      solution_ =
          scene_->addRect((path.top().x + 1) * indent_by_x - (indent_by_x / 2),
                          (path.top().y + 1) * indent_by_y - (indent_by_y / 2),
                          2, indent_by_y, QPen(Qt::red), QBrush(Qt::red));
    } else if (change_x == -1) {
      solution_ =
          scene_->addRect((path.top().x + 1) * indent_by_x - (indent_by_x / 2),
                          (path.top().y + 1) * indent_by_y - (indent_by_y / 2),
                          indent_by_x, 2, QPen(Qt::red), QBrush(Qt::red));
    } else if (change_x == 1) {
      solution_ =
          scene_->addRect((path.top().x) * indent_by_x - (indent_by_x / 2),
                          (path.top().y + 1) * indent_by_y - (indent_by_y / 2),
                          indent_by_x, 2, QPen(Qt::red), QBrush(Qt::red));
    } else if (change_y == 1) {
      solution_ =
          scene_->addRect((path.top().x + 1) * indent_by_x - (indent_by_x / 2),
                          (path.top().y) * indent_by_y - (indent_by_y / 2), 2,
                          indent_by_y, QPen(Qt::red), QBrush(Qt::red));
    }
  }
}

}  // namespace Maze
