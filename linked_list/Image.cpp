#include <iostream>
#include "Image.h"
#include "cs225/PNG.h"


namespace cs225{
Image::Image(unsigned int w, unsigned int h):
PNG(w,h){}

Image::Image(Image const & other):PNG(other){
}

Image::Image():PNG(){}

void Image::lighten(){
  for(unsigned int x = 0; x<width(); x++){
    for(unsigned int y = 0; y< height();y++){
      HSLAPixel & pixel = getPixel(x,y);
      if (pixel.l+0.1 >= 0 && pixel.l+0.1<=1){
        pixel.l = pixel.l+0.1;
      }
      else {
        pixel.l = 1;
      }
    }
  }
}

void Image::lighten(double amount){
  for(unsigned int x = 0; x< width(); x++){
    for(unsigned int y = 0; y< height();y++){
      HSLAPixel & pixel = getPixel(x,y);
      if (pixel.l+ amount >= 0 && pixel.l+amount<=1){
        pixel.l = pixel.l + amount;
      }
      else {pixel.l = 1;}
    }
  }
}

void Image::darken(){
  for(unsigned int x = 0; x< width(); x++){
    for(unsigned int y = 0; y< height();y++){
      HSLAPixel & pixel = getPixel(x,y);
      if (pixel.l-0.1 >= 0 && pixel.l-0.1<=1){
        pixel.l = pixel.l-0.1;
      }
      else {pixel.l = 0;}
    }
  }
}
void Image::darken(double amount){
  for(unsigned int x = 0; x<width(); x++){
    for(unsigned int y = 0; y< height();y++){
      HSLAPixel & pixel = getPixel(x,y);
      if (pixel.l-amount >= 0 && pixel.l-amount<=1){
        pixel.l = pixel.l-amount;
      }
      else {pixel.l = 0;}
    }
  }
}
void Image::saturate(){
  for(unsigned int x = 0; x<width(); x++){
    for(unsigned int y = 0; y< height();y++){
      HSLAPixel & pixel = getPixel(x,y);
      if (pixel.s+0.1 >= 0 && pixel.s+0.1<=1){
        pixel.s = pixel.s+0.1;
      }
      else {pixel.s = 1;}
    }
  }
}


void Image::saturate(double amount){
  for(unsigned int x = 0; x<width(); x++){
    for(unsigned int y = 0; y< height();y++){
      HSLAPixel & pixel = getPixel(x,y);
      if (pixel.s+amount >= 0 && pixel.s+amount<=1){
        pixel.s = pixel.s+amount;
      }
      else {pixel.s = 1;}
    }
  }
}

void Image::desaturate(){
  for(unsigned int x = 0; x<width(); x++){
    for(unsigned int y = 0; y< height();y++){
      HSLAPixel & pixel = getPixel(x,y);
      if (pixel.s-0.1 >= 0 && pixel.s-0.1<=1){
        pixel.s = pixel.s-0.1;
      }
      else {pixel.s = 0;}
    }
  }
}


void Image::desaturate(double amount){
  for(unsigned int x = 0; x<width(); x++){
    for(unsigned int y = 0; y< height();y++){
      HSLAPixel & pixel = getPixel(x,y);
      if (pixel.s - amount >= 0 && pixel.s-amount<=1){
        pixel.s = pixel.s - amount;
      }
      else {pixel.s = 0;}
    }
  }
}

void Image::grayscale(){
  for (unsigned x = 0; x < width(); x++) {
    for (unsigned y = 0; y < height(); y++) {
      HSLAPixel & pixel = getPixel(x, y);
      pixel.s = 0;
    }
  }
}

void Image::rotateColor(double degrees){
  for (unsigned x = 0; x < width(); x++) {
    for (unsigned y = 0; y < height(); y++) {
      HSLAPixel & pixel = getPixel(x, y);

      pixel.h =pixel.h+degrees;
      if(pixel.h >360)
        pixel.h -= 360;
      if(pixel.h <0)
        pixel.h += 360;
    }
  }
}
void Image::illinify(){
  for(unsigned int x = 0; x < width(); x++){
    for(unsigned int y = 0; y < height(); y++){
      HSLAPixel & pixel = getPixel(x,y);
      double distance_or = pixel.h - 11;
      double distance_bl = pixel.h - 216;
      if(distance_or < 0){
        distance_or = 0 - distance_or;
      }
      if(distance_or > 180) distance_or =  360 - distance_or;
      if(distance_bl < 0){
              distance_bl = 0 - distance_bl;
      }
      if(distance_or > 180) distance_bl =  360 - distance_bl;
      if(distance_or > distance_bl){
              pixel.h = 216;
      }
      else{
        pixel.h = 11;
      }
    }
  }
}

void Image::scale(double factor){
  int widthold = width(), heightold = height();

  unsigned int width1 = this-> width()*factor;
  unsigned int height1= this->height()*factor;

  HSLAPixel * oldimage =new HSLAPixel[width()*height()];
  for(unsigned int x = 0; x < width();x++){
    for(unsigned int y=0; y< height();y++){

      HSLAPixel & pixel =  getPixel(x,y);
      oldimage[x+(y*width())].h = pixel.h;
      oldimage[x+(y*width())].s = pixel.s;
      oldimage[x+(y*width())].l = pixel.l;
      oldimage[x+(y*width())].a = pixel.a;
    }
  }

  PNG::resize(width1, height1);

  for(unsigned int x = 0; x < width1;x++){
    for(unsigned int y = 0; y< height1;y++){
      HSLAPixel & pixel2 = getPixel(x,y);

      pixel2.h = oldimage[(int)(x/factor)+(int)(y/factor)*widthold].h;
      pixel2.s = oldimage[(int)(x/factor)+(int)(y/factor)*widthold].s;
      pixel2.l = oldimage[(int)(x/factor)+(int)(y/factor)*widthold].l;
      pixel2.a = oldimage[(int)(x/factor)+(int)(y/factor)*widthold].a;
}
}
}

void Image::scale(unsigned w, unsigned h){

  unsigned int widthold = width(),heightold = height();
  double factor = 1.0*w/widthold;
  Image::scale(factor);
}

}
