#include "../cs225/HSLAPixel.h"
#include "../Point.h"
#include "../cs225/PNG.h"
#include "ColorPicker.h"
#include "MyColorPicker.h"

using namespace cs225;

/**
 * Picks the color for pixel (x, y).
 * Using your own algorithm
 */
MyColorPicker::MyColorPicker(PNG png){
  png_ = png;
}

HSLAPixel MyColorPicker::getColor(unsigned x, unsigned y) {
  /* @todo [Part 3] */
  HSLAPixel tmp = png_.getPixel(x,y);
  HSLAPixel rtu;
  rtu.h = tmp.h;
  rtu.s = tmp.s;
  rtu.l = tmp.l;
  rtu.a = tmp.a;

  return rtu;
}
