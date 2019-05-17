/**
 * @file Image.h
 * Contains your declaration of the interface for the Image class.
 */

#pragma once
#include "cs225/PNG.h"

namespace cs225{
class Image : public PNG
{
   public:
      Image();
     Image(unsigned width, unsigned height);
     Image(Image const & other);
/*Lighten an Image by increasing the luminance of every pixel by 0.1.
This function ensures that the luminance remains in the range [0, 1].*/
    void lighten();
    void lighten(double amount);
    void darken();
    void darken(double amount);
    void saturate();
    void saturate(double amount);
    void desaturate();
    void desaturate(double amount);
    void grayscale();
    void rotateColor(double degrees);
    void illinify();
    void scale(double factor);
    void scale(unsigned w, unsigned h);

    private:

};
}
