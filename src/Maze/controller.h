#ifndef A1_MAZE_SRC_CONTROLLER_H
#define A1_MAZE_SRC_CONTROLLER_H

#include "model.h"

namespace Maze {
class Controller {
 public:
  using Coordinates = std::stack<Coordinate>;
  Controller(Maze::Model *m) : model_(m){};
  void ParseFromFileIntoMatrixes(std::string file_with_maze) {
    model_->ParseFromFileIntoMatrixes(file_with_maze);
  };
  void SaveInFile(std::string file_path) { model_->SaveInFile(file_path); };
  void GenerateRandomMaze(int h_size, int v_size) {
    model_->GenerateRandomMaze(h_size, v_size);
  };
  Coordinates GetSolvedMaze(Maze::Coordinate begin, Maze::Coordinate end) {
    return model_->Solve(begin, end);
  };
  std::vector<std::vector<bool>> GetVWalls() { return model_->GetVWalls(); };
  std::vector<std::vector<bool>> GetHWalls() { return model_->GetHWalls(); };
  int GetVSize() { return model_->GetVSize(); };
  int GetHSize() { return model_->GetHSize(); };

 private:
  Maze::Model *model_;
};

}  // namespace Maze
#endif  // A1_MAZE_SRC_CONTROLLER_H
