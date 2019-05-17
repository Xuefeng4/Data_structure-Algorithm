#include <iostream>
#include "dsets.h"
#include "maze.h"
#include "cs225/PNG.h"

using namespace std;

int main()
{
  SquareMaze m;
  m.makeMaze(50, 50);
  std::cout << "MakeMaze complete" << std::endl;

  cs225::PNG* unsolved = m.drawCreativeMaze();
  unsolved->writeToFile("creative.png");
  delete unsolved;
  std::cout << "drawMaze complete" << std::endl;

  return 0;
}
