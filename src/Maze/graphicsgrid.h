#ifndef A1_MAZE_SRC_GRAPHICSGRID_H
#define A1_MAZE_SRC_GRAPHICSGRID_H

#include <QFile>
#include <QGraphicsView>

#include "controller.h"

namespace Maze {

class GraphicsGrid : public QGraphicsView {
  Q_OBJECT

 public:
  using Coordinates = std::stack<Coordinate>;
  GraphicsGrid(QWidget *parent = nullptr);
  void DrawArea();
  void DrawMaze(std::vector<std::vector<bool>> v_walls,
                std::vector<std::vector<bool>> h_walls, int v_size, int h_size);
  void CleanGrid();
  void DrawSolution(int v_size, int h_size, Coordinates path);

 private:
  QGraphicsScene *scene_;
};

}  // namespace Maze
#endif  // A1_MAZE_SRC_GRAPHICSGRID_H
