#ifndef A1_MAZE_SRC_MODEL_H
#define A1_MAZE_SRC_MODEL_H

#include <fstream>
#include <list>
#include <random>
#include <sstream>
#include <stack>
#include <vector>

namespace Maze {
struct Coordinate {
  size_t x;
  size_t y;
  bool operator==(const Coordinate& B) const { return x == B.x && y == B.y; };
};

struct Turns {
  bool up;
  bool left;
  bool right;
  bool bottom;
};

class Model {
 public:
  using Coordinates = std::stack<Coordinate>;
  Model()
      : v_walls_(1, std::vector<bool>(1, false)),
        h_walls_(1, std::vector<bool>(1, false)){};
  void ParseFromFileIntoMatrixes(std::string path_to_file_with_maze);
  void GenerateRandomMaze(int h_size, int v_size);
  std::vector<std::vector<bool>> GetVWalls() { return v_walls_; };
  std::vector<std::vector<bool>> GetHWalls() { return h_walls_; };
  int GetVSize() { return v_size_; };
  int GetHSize() { return h_size_; };
  Coordinates Solve(Coordinate begin, Coordinate end);
  void SaveInFile(std::string file_path);

 private:
  void ClearMatrixes();
  void Resize(int new_rows, int new_cols);
  void FillEmptyValue();
  void AssignUniqueSet();
  void AddingVerticalWalls(int row);
  void MergeSet(int index, int element);
  void AddingHorizontalWalls(int row);
  int CalculateUniqueSet(int element);
  void CheckedHorizontalWalls(int row);
  int CalculateHorizontalWalls(int element, int row);
  void PreparatingNewLine(int row);
  void AddingEndLine();
  void CheckedEndLine();
  bool RandomBool();
  void ClearGenerator();
  std::list<std::pair<int, int>> SolveTheMaze(int x1, int y1, int x2, int y2);
  bool RecursiveSolveTheMaze(std::vector<std::vector<bool>>& visited_places_,
                             Coordinates& path, Coordinate begin,
                             Coordinate end);
  int v_size_ = 0;
  int h_size_ = 0;
  std::vector<std::vector<bool>> v_walls_;
  std::vector<std::vector<bool>> h_walls_;
  std::vector<int> sideLine_;
  const int kEmpty = 0;
  int counter_ = 1;
  ;
};

}  // namespace Maze
#endif  // A1_MAZE_SRC_MODEL_H
