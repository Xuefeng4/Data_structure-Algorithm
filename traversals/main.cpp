
#include "cs225/PNG.h"
#include "FloodFilledImage.h"
#include "Animation.h"

#include "imageTraversal/DFS.h"
#include "imageTraversal/BFS.h"

#include "colorPicker/RainbowColorPicker.h"
#include "colorPicker/GradientColorPicker.h"
#include "colorPicker/GridColorPicker.h"
#include "colorPicker/SolidColorPicker.h"
#include "colorPicker/MyColorPicker.h"
#include <iostream>
using namespace cs225;

int main() {

  // @todo [Part 3]
  // - The code below assumes you have an Animation called `animation`
  // - The code provided below produces the `myFloodFill.png` file you must
  //   submit Part 3 of this assignment -- uncomment it when you're ready.

  PNG test1;
  test1.readFromFile("test1.png");
  PNG test2;
  test2.readFromFile("test2.png");
  PNG test3;
  test3.readFromFile("test3.png");

  Point p;
  BFS tra1(test1,p,0.2);
  Point p2(88,174);
  DFS tra2(test1,p2,0.2);
  MyColorPicker col(test2);
  MyColorPicker col2(test3);

  FloodFilledImage image(test1);
  image.addFloodFill(tra1, col);
  image.addFloodFill(tra2, col2);

  Animation animation = image.animate(600);
  PNG lastFrame = animation.getFrame( animation.frameCount() - 1 );
  lastFrame.writeToFile("myFloodFill.png");
  animation.write("myFloodFill.gif");
  return 0;
}
