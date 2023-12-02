#include "model.h"

namespace Maze {

void Model::Resize(int new_rows, int new_cols) {
  v_walls_.resize(new_rows, std::vector<bool>(new_cols, false));
  h_walls_.resize(new_rows, std::vector<bool>(new_cols, false));
}

void Model::ClearMatrixes() {
  if (h_size_ == 0 && v_size_ == 0) return;
  for (int i = 0; i < h_size_; ++i)
    for (int j = 0; j < v_size_; ++j) {
      v_walls_[i][j] = false;
      h_walls_[i][j] = false;
    }
  v_size_ = 0;
  h_size_ = 0;
}

void Model::ClearGenerator() {
  sideLine_.clear();
  counter_ = 1;
}

void Model::GenerateRandomMaze(int h_size, int v_size) {
  ClearMatrixes();
  ClearGenerator();
  h_size_ = h_size;
  v_size_ = v_size;
  Resize(0, 0);
  Resize(h_size_, v_size_);
  FillEmptyValue();
  for (int j = 0; j < h_size_ - 1; j++) {
    AssignUniqueSet();
    AddingVerticalWalls(j);
    AddingHorizontalWalls(j);
    CheckedHorizontalWalls(j);
    PreparatingNewLine(j);
  }
  AddingEndLine();
}

void Model::FillEmptyValue() {
  for (int i = 0; i < v_size_; i++) {
    sideLine_.push_back(kEmpty);
  }
}

void Model::AssignUniqueSet() {
  for (int i = 0; i < v_size_; i++) {
    if (sideLine_[i] == kEmpty) {
      sideLine_[i] = counter_;
      counter_++;
    }
  }
}

void Model::AddingVerticalWalls(int row) {
  for (int i = 0; i < v_size_ - 1; i++) {
    bool choise = RandomBool();
    if (choise == true || sideLine_[i] == sideLine_[i + 1]) {
      v_walls_[row][i] = true;
    } else {
      MergeSet(i, sideLine_[i]);
    }
  }
  v_walls_[row][v_size_ - 1] = true;
}

void Model::MergeSet(int index, int element) {
  int mutableSet = sideLine_[index + 1];
  for (int j = 0; j < v_size_; j++) {
    if (sideLine_[j] == mutableSet) {
      sideLine_[j] = element;
    }
  }
}

void Model::AddingHorizontalWalls(int row) {
  for (int i = 0; i < v_size_; i++) {
    bool choise = RandomBool();
    if (CalculateUniqueSet(sideLine_[i]) != 1 && choise == true) {
      h_walls_[row][i] = true;
    }
  }
}

int Model::CalculateUniqueSet(int element) {
  int countUniqSet = 0;
  for (int i = 0; i < v_size_; i++) {
    if (sideLine_[i] == element) {
      countUniqSet++;
    }
  }
  return countUniqSet;
}

void Model::CheckedHorizontalWalls(int row) {
  for (int i = 0; i < v_size_; i++) {
    if (CalculateHorizontalWalls(sideLine_[i], row) == 0) {
      h_walls_[row][i] = false;
    }
  }
}

int Model::CalculateHorizontalWalls(int element, int row) {
  int countHorizontalWalls = 0;
  for (int i = 0; i < v_size_; i++) {
    if (sideLine_[i] == element && h_walls_[row][i] == false) {
      countHorizontalWalls++;
    }
  }
  return countHorizontalWalls;
}

void Model::PreparatingNewLine(int row) {
  for (int i = 0; i < v_size_; i++) {
    if (h_walls_[row][i] == true) {
      sideLine_[i] = kEmpty;
    }
  }
}

void Model::AddingEndLine() {
  AssignUniqueSet();
  AddingVerticalWalls(h_size_ - 1);
  CheckedEndLine();
}

void Model::CheckedEndLine() {
  for (int i = 0; i < v_size_ - 1; i++) {
    if (sideLine_[i] != sideLine_[i + 1]) {
      v_walls_[h_size_ - 1][i] = false;
      MergeSet(i, sideLine_[i]);
    }
    h_walls_[h_size_ - 1][i] = true;
  }
  h_walls_[h_size_ - 1][v_size_ - 1] = true;
}

bool Model::RandomBool() {
  std::random_device rd;
  std::default_random_engine engine(rd());
  std::uniform_int_distribution<int> dist(0, 1);
  return static_cast<bool>(dist(engine));
}

Model::Coordinates Model::Solve(Coordinate begin, Coordinate end) {
  std::vector<std::vector<bool>> visited_places_(h_size_);
  Coordinates path;
  begin.x -= 1;
  begin.y -= 1;
  end.x -= 1;
  end.y -= 1;
  for (size_t i = 0; i < visited_places_.size(); ++i) {
    visited_places_[i] = std::vector<bool>(v_walls_[0].size());
  }
  RecursiveSolveTheMaze(visited_places_, path, begin, end);
  return path;
}

bool Model::RecursiveSolveTheMaze(
    std::vector<std::vector<bool>>& visited_places_, Coordinates& path,
    Coordinate begin, Coordinate end) {
  path.push(begin);
  size_t j = path.top().x;
  size_t i = path.top().y;
  if (i != end.y || j != end.x) {
    visited_places_[i][j] = true;
    Turns t{i > 0 && !h_walls_[i - 1][j], j > 0 && !v_walls_[i][j - 1],
            j < v_walls_[0].size() - 1 && !v_walls_[i][j],
            i < h_walls_.size() - 1 && !h_walls_[i][j]};
    if (t.right && !visited_places_[i][j + 1] &&
        RecursiveSolveTheMaze(visited_places_, path, Coordinate{j + 1, i}, end))
      return true;
    if (t.bottom && !visited_places_[i + 1][j] &&
        RecursiveSolveTheMaze(visited_places_, path, Coordinate{j, i + 1}, end))
      return true;
    if (t.left && !visited_places_[i][j - 1] &&
        RecursiveSolveTheMaze(visited_places_, path, Coordinate{j - 1, i}, end))
      return true;
    if (t.up && !visited_places_[i - 1][j] &&
        RecursiveSolveTheMaze(visited_places_, path, Coordinate{j, i - 1}, end))
      return true;
    path.pop();
    return false;
  }
  return true;
}

void Model::ParseFromFileIntoMatrixes(std::string path_to_file_with_maze) {
  ClearMatrixes();
  Resize(1, 1);
  std::ifstream file_with_maze(path_to_file_with_maze);
  if (!file_with_maze.is_open()) {
    throw std::runtime_error("Failed to open file");
  }
  std::string line;
  std::vector<std::string> tokens;
  if (std::getline(file_with_maze, line)) {
    std::istringstream iss(line);
    iss >> v_size_ >> h_size_;
  } else {
    throw std::runtime_error("Invalid maze format");
  }

  for (int i = 0; i < h_size_; ++i) {
    if (std::getline(file_with_maze, line)) {
      std::istringstream iss(line);
      std::vector<bool> row;
      bool value;
      while (iss >> value) row.push_back(value);
      if (static_cast<int>(row.size()) != v_size_)
        throw std::runtime_error("Invalid h_walls format");
      if (i == 0)
        v_walls_[0] = row;
      else
        v_walls_.push_back(row);
    } else {
      throw std::runtime_error("Invalid maze format");
    }
  }
  std::getline(file_with_maze, line);
  for (int i = 0; i < h_size_; ++i) {
    if (std::getline(file_with_maze, line)) {
      std::istringstream iss(line);
      std::vector<bool> row;
      bool value;
      while (iss >> value) row.push_back(value);
      if (static_cast<int>(row.size()) != v_size_)
        throw std::runtime_error("Invalid h_walls format");
      if (i == 0)
        h_walls_[0] = row;
      else
        h_walls_.push_back(row);
    } else
      throw std::runtime_error("Invalid maze format");
  }
  file_with_maze.close();
}

void Model::SaveInFile(std::string file_path) {
  std::ofstream file(file_path);
  if (file.is_open()) {
    file << v_size_ << " " << h_size_ << "\n";
    for (const std::vector<bool>& row : v_walls_) {
      for (size_t i = 0; i < row.size(); ++i) {
        file << (row[i] ? 1 : 0);
        if (i < row.size() - 1) file << " ";
      }
      file << "\n";
    }
    file << "\n";
    for (const std::vector<bool>& row : h_walls_) {
      for (size_t i = 0; i < row.size(); ++i) {
        file << (row[i] ? 1 : 0);
        if (i < row.size() - 1) file << " ";
      }
      if (&row != &v_walls_.back()) file << "\n";
    }
    file.close();
  } else {
    throw std::runtime_error("Error in opening file");
    return;
  }
}

}  // namespace Maze
