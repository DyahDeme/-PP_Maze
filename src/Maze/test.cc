#include <gtest/gtest.h>

#include <vector>

#include "controller.h"

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

TEST(MazeTest, sizeTest) {
  Maze::Model model;
  Maze::Controller controller(&model);
  controller.GenerateRandomMaze(3, 3);
  EXPECT_TRUE(controller.GetHSize() == 3);
  EXPECT_TRUE(controller.GetVSize() == 3);
}

TEST(MazeTest, solveAndParseTest) {
  Maze::Model model;
  Maze::Controller controller(&model);
  std::ofstream outfile("test_maze.txt");
  outfile << "4 4\n";
  outfile << "0 1 1 1\n";
  outfile << "1 0 1 1\n";
  outfile << "0 1 0 1\n";
  outfile << "0 0 0 1\n";
  outfile << "\n";
  outfile << "0 1 0 0\n";
  outfile << "0 0 0 0\n";
  outfile << "1 1 1 0\n";
  outfile << "1 1 1 1";
  outfile.close();
  controller.ParseFromFileIntoMatrixes("test_maze.txt");
  std::stack<Maze::Coordinate> generated_solve_of_test_maze =
      controller.GetSolvedMaze({1, 1}, {4, 4});
  std::stack<Maze::Coordinate> solve_of_test_maze;
  solve_of_test_maze.push({0, 0});
  solve_of_test_maze.push({0, 1});
  solve_of_test_maze.push({0, 2});
  solve_of_test_maze.push({1, 2});
  solve_of_test_maze.push({1, 1});
  solve_of_test_maze.push({2, 1});
  solve_of_test_maze.push({2, 2});
  solve_of_test_maze.push({3, 2});
  solve_of_test_maze.push({3, 3});
  while (!solve_of_test_maze.empty()) {
    EXPECT_TRUE(generated_solve_of_test_maze.top() == solve_of_test_maze.top());
    solve_of_test_maze.pop();
    generated_solve_of_test_maze.pop();
  }
  std::remove("test_maze.txt");
}

TEST(MazeTest, SaveTest) {
  Maze::Model model;
  Maze::Controller controller(&model);
  std::ofstream outfile("test_maze.txt");
  outfile << "4 4\n";
  outfile << "0 1 1 1\n";
  outfile << "1 0 1 1\n";
  outfile << "0 1 0 1\n";
  outfile << "0 0 0 1\n";
  outfile << "\n";
  outfile << "0 1 0 0\n";
  outfile << "0 0 0 0\n";
  outfile << "1 1 1 0\n";
  outfile << "1 1 1 1";
  outfile.close();
  controller.ParseFromFileIntoMatrixes("test_maze.txt");
  controller.SaveInFile("save_test_maze.txt");
  std::ifstream file1("test_maze.txt");
  std::ifstream file2("solve_test_maze.txt");
  std::string line1, line2;
  while (std::getline(file1, line1) && std::getline(file2, line2)) {
    EXPECT_TRUE(line1 == line2);
  }
  file1.close();
  file2.close();
  std::remove("save_test_maze.txt");
  std::remove("test_maze.txt");
}