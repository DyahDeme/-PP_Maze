CC = g++
CFLAGS = -Wall -Werror -Wextra -std=c++17
CFLAGS_GCOV =-Wall -Werror -Wextra --coverage
CFLAGS_TEST =-lgtest -pthread -lgmock -fprofile-arcs -ftest-coverage

OS=$(shell uname)
ifeq ($(OS), Linux)
  CFLAGS_TEST += -lm -lsubunit
  OPEN=xdg-open
else
  OPEN=open
endif

LEAKS_RUN = CK_FORK=no leaks -atExit -- ./tests

SOURCES = ./model.cc
HEADERS = ./model.h ./controller.h
SOURCES_TEST = ./test.cc

DVI_DIR = ./"doc_Maze"
BUILD_DIR = ../build
OUTFILE_TEST = test

all: install

install:
	qmake CONFIG+=release -o $(BUILD_DIR)/Makefile Maze.pro 
	-cd $(BUILD_DIR); make
	-cd $(BUILD_DIR); make clean  

uninstall:
	rm -rf ../build

dist:
	mkdir A1_Maze
	cp -rf *.cc *.cpp *.h *.ui *.pro *.icns *.texi Makefile A1_Maze
	tar -cf A1_Maze.tar A1_Maze
	rm -rf A1_Maze

dvi:
	makeinfo -o $(DVI_DIR) --html --no-warn --force ./Maze_info.texi
	$(OPEN) -a "Google Chrome" $(DVI_DIR)/index.html

test:
	$(CC) -c $(HEADERS) $(CFLAGS)
	$(CC) $(SOURCES_TEST) $(SOURCES) -o $(OUTFILE_TEST) $(CFLAGS_TEST) $(CFLAGS)
	./$(OUTFILE_TEST)

gcov_report: test
	lcov --ignore-errors mismatch --no-external -c -d . -o test.info
	genhtml --ignore-errors mismatch -o report test.info
	open report/index.html

google_style:
	cp ../../materials/linters/.clang-format .clang-format
	clang-format --verbose -i ./*.h ./*.cc ./*.cpp
	rm .clang-format

clang:
	cp ../../materials/linters/.clang-format .clang-format
	clang-format --verbose -n ./*.h ./*.cc ./*.cpp
	rm .clang-format

leaks: test
	$(LEAKS_RUN)

clean:
	rm -rf ./lcov_report
	rm -rf *.o *.a *.gcno *.gcda *.gcov *.gch *.info *.html *.css report doc_Maze test_maze.txt .qmake.stash ./$(OUTFILE_TEST) 
