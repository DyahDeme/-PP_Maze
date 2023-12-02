# Maze

Implementation of the Maze project.

## Introduction

In this project you’ll learn about mazes, including the basic algorithms of their handling, such as: generation, rendering, solving.

## Maze description

The maze can be stored in a file as a number of rows and columns, as well as two matrices containing the positions of vertical and horizontal walls respectively.

The first matrix shows the wall to the right of each cell, and the second - the wall at the bottom.

An example of such a file:
```
4 4
0 0 0 1
1 0 1 1
0 1 0 1
0 0 0 1

1 0 1 0
0 0 1 0
1 1 0 1
1 1 1 1
```

The maze described in this file:  \
![maze1](misc/images/maze1.jpg)

## Implementation of the Maze project

You need to implement a Maze program that can generate and render perfect mazes and caves:
- The program is developed in C++ language of C++17 standard
- The program code is located in the src folder
- When writing code it is necessary to follow the Google style
- The program is built with Makefile which contains standard set of targets for GNU-programs: all, install, uninstall, clean, dvi, dist, tests.
- GUI implementation, based on any GUI library with API for C++17: Qt.
- The program has a button to load the maze from a file, which is set in the format described above
- Maximum size of the maze is 50x50
- The loaded maze is rendered on the screen in a field of 500 x 500 pixels
- The size of the maze cells themselves is calculated so that the maze occupies the entire field allotted to it.

## Generation of a perfect maze

Add the ability to automatically generate a perfect maze. \
A maze is considered perfect if it is possible to get from each point to any other point in exactly one way.
- The maze is generated according to the **Eller's algorithm**
- The generated maze must not have isolations and loops
- Prepare full coverage of the perfect maze generation module with unit-tests
- The user enters only the dimensionality of the maze: the number of rows and columns
- The generated maze is saved in the file format described above
- The created maze should be displayed on the screen as specified in the first part

## Solving the maze

Add the ability to show the solution to _any_ maze currently shown on the screen:
- The user sets the starting and ending points
- The route, which is the solution, is displayed with a line 2 pixel thick, passing through the middle of all the cells in the maze through which the solution runs.
- Prepare full coverage of the maze solving module with unit-tests
