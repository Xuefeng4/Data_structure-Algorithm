/* Your code here! */
#pragma once
#include <vector>
#include <stdlib.h>     /* srand, rand */
#include <time.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stack>
#include "cs225/PNG.h"
#include "dsets.h"
using namespace cs225;
class SquareMaze {
  public:
    SquareMaze();
    void makeMaze(int width, int height);
    bool canTravel (int x, int y, int dir) const;
    void setWall (int x, int y, int dir, bool exists);
    std::vector<int> solveMaze();
    PNG * drawMaze() const;
    PNG * drawMazeWithSolution();
    void dfs(int x, int y, std::vector<std::vector<bool>>& visited,
              std::vector<int>& curr, std::vector<int>& result, int ry,int op);
      PNG * drawCreativeMaze() const;
  private:
    int width_;
    int height_;
    std::vector<bool> down;
    std::vector<bool> right;
    std::vector<int> longest;





};
