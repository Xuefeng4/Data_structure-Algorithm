#include <cmath>
#include <iterator>
#include <iostream>

#include "../cs225/HSLAPixel.h"
#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"

/**
 * Calculates a metric for the difference between two pixels, used to
 * calculate if a pixel is within a tolerance.
 *
 * @param p1 First pixel
 * @param p2 Second pixel
 * @return the difference between two HSLAPixels
 */
double ImageTraversal::calculateDelta(const HSLAPixel & p1, const HSLAPixel & p2) {
  double h = fabs(p1.h - p2.h);
  double s = p1.s - p2.s;
  double l = p1.l - p2.l;

  // Handle the case where we found the bigger angle between two hues:
  if (h > 180) { h = 360 - h; }
  h /= 360;

  return sqrt( (h*h) + (s*s) + (l*l) );
}

/**
 * Default iterator constructor.
 */
ImageTraversal::Iterator::Iterator() {
  /** @todo [Part 1] */
  tra_ = NULL;
}

ImageTraversal::Iterator::Iterator(ImageTraversal * traversal, PNG png, double tolerance,Point start){
  png_ = png;
  curr_ = start;
  start_ = start;
  tolerance_ = tolerance;
  tra_ = traversal;
  for(unsigned i = 0; i < png.width()*png.height();i++){
    path_.push_back(false);
  }
  if(isvalid(start_))
  path_[start_.x + png_.width()*start.y] = true;
}


/**
 * Iterator increment opreator.
 *
 * Advances the traversal of the image.
 */
ImageTraversal::Iterator & ImageTraversal::Iterator::operator++() {
  /** @todo [Part 1] */
  curr_ = tra_->pop();
  path_[curr_.x + png_.width()*curr_.y] = true;

  Point right(curr_.x+1,curr_.y);
  Point bottom(curr_.x,curr_.y+1);
  Point left(curr_.x-1,curr_.y);
  Point top(curr_.x,curr_.y-1);
  if (isvalid(right)) {
    tra_->add(right);
  }
  if (isvalid(bottom)) {
    tra_->add(bottom);
  }
  if (isvalid(left)){
    tra_->add(left);
  }
  if (isvalid(top)){
     tra_->add(top);
   }
  if (tra_->empty()){
    curr_ = Point(0x7fffffff,0);
    return *this;
  }

  curr_ = tra_->peek();
  while(path_[curr_.x + curr_.y* png_.width()]){
    tra_->pop();
    if(tra_->empty()){
      curr_ = Point(0x7fffffff,0);
      return *this;
    }
    curr_ = tra_->peek();
  }
  // while (std::find(visited_.begin(), visited_.end(), curr_) != visited_.end()){
  //   tra_->pop();
  //   if(tra_->empty()){
  //     curr_ = Point(0x7fffffff,0);
  //     return *this;
  //   }
  //   curr_ = tra_->peek();
  // }
  return *this;
}

/**
 * Iterator accessor opreator.
 *
 * Accesses the current Point in the ImageTraversal.
 */
Point ImageTraversal::Iterator::operator*() {
  /** @todo [Part 1] */
  return curr_;
}

/**
 * Iterator inequality operator.
 *
 * Determines if two iterators are not equal.
 */
bool ImageTraversal::Iterator::operator!=(const ImageTraversal::Iterator &other) {
  /** @todo [Part 1] */
  return !(this->curr_ == other.curr_);
}

bool ImageTraversal::Iterator::isvalid(Point p){
  bool rtu = true;
  if (p.x>=png_.width()) rtu = false;
  else if (p.y>=png_.height()) rtu = false;
  else if(calculateDelta(png_.getPixel(start_.x,start_.y),png_.getPixel(p.x,p.y))>=tolerance_)
    rtu = false;
  return rtu;

}
