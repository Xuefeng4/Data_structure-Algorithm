#include "Image.h"
#include "StickerSheet.h"
#include <iostream>
#include "Image.h"


namespace cs225{

  void StickerSheet::_destory(){
    delete[] stickersheetimage;
    delete[] coordinatex;
    delete[] coordinatey;
  }

  void StickerSheet::_copy(const StickerSheet & other){
    max_ =  other.max_;
    cur = other.cur ;
    coordinatex = new unsigned int[max_];
    for(unsigned int i = 0; i < cur; i++){
      coordinatex[i] = other.coordinatex[i];
    }

    coordinatey = new unsigned int[max_];
    for(unsigned int i = 0; i < cur; i++){
      coordinatey[i] = other.coordinatey[i];
    }

    stickersheetimage= new Image*[max_];
    for(unsigned int i = 0; i < cur; i++){
      stickersheetimage[i] = new Image(*other.stickersheetimage[i]);
    }
    }

  StickerSheet::StickerSheet(const Image & picture, unsigned max):
  picture_(picture){
    max_ = max;
    cur = 0;
    stickersheetimage = new Image*[max_];
    coordinatex = new unsigned int[max_];
    coordinatey = new unsigned int[max_];
  }

  StickerSheet::~StickerSheet(){
    _destory();
  }

  StickerSheet::StickerSheet(const StickerSheet & other):
  picture_(other.picture_){
    //stickersheetimage = NULL; do not know why still do not underestand the copy constructor and the operator
    _copy(other);
  }

  const StickerSheet & StickerSheet::operator =	(const StickerSheet & other)	{
    if(this != &other){
      _destory();
      _copy(other);
    }
    return *this;

  }

int StickerSheet::addSticker(Image & sticker, unsigned x, unsigned y){
  if(cur == max_)
      return -1;
  else{
  stickersheetimage[cur] = new Image(sticker);
  coordinatex[cur] = x;
  coordinatey[cur] = y;
  cur++;
  return cur-1;
  }
}

  void StickerSheet::changeMaxStickers(unsigned max){
    Image ** stickersheetimage_new= new Image*[max];
    if (max > max_){
      for(unsigned int i=0 ; i < max_; i++){
        stickersheetimage_new[i]= stickersheetimage[i];
      }
    }
    else{
      for(unsigned int i=0; i< max; i++){
      stickersheetimage_new[i]= stickersheetimage[i];
      }
      if (cur>max) cur = max;
    }
      max_ = max;
      delete[] stickersheetimage;
      stickersheetimage = stickersheetimage_new;
  }



  bool StickerSheet::translate(unsigned index, unsigned x, unsigned y){
    if (index>cur){
      return false;
    }
    else{
      coordinatex[index] = x;
      coordinatey[index] = y;
      return true;
    }
  }

  void StickerSheet::removeSticker(unsigned index){
    if(index<cur){
      delete stickersheetimage[index];
      stickersheetimage[index] = NULL;

      for(unsigned int x = index; x< cur-1; x++){
        stickersheetimage[x] = stickersheetimage[x+1];
        stickersheetimage[x+1] = NULL;
        coordinatex[x] = coordinatex[x+1];
        coordinatex[x+1] = 0;
        coordinatey[x] = coordinatey[x+1];
        coordinatey[x+1] = 0;

      }
      cur =cur-1;
    }
  }

  Image * StickerSheet::getSticker(unsigned index){
     if(index< cur){
        return stickersheetimage[index];
      }
      else {return NULL;}
   }


  Image StickerSheet::render() const{
    unsigned int maxwidth =picture_.width();
    unsigned int maxheight = picture_.height();
    for (unsigned int z=0; z<cur; z++){
      unsigned int stickerwidth = stickersheetimage[z]->width()+coordinatex[z];
      if (stickerwidth>maxwidth){
        maxwidth = stickerwidth;
      }
      unsigned int stickerheight= stickersheetimage[z]->height()+coordinatey[z];
      if (stickerheight>maxheight){
        maxheight = stickerheight;
      }
    }
    Image * canvas = new Image(maxwidth,maxheight);

    for(unsigned int x=0; x<maxwidth;x++){
      for(unsigned int y=0; y<maxheight;y++){
        HSLAPixel & canvas_pixel = canvas->getPixel(x,y);
        canvas_pixel.a = 0;
      }
    }
    for(unsigned int x=0; x<picture_.width();x++){
      for(unsigned int y=0; y<picture_.height();y++){
        HSLAPixel & picture_pixel = picture_.getPixel(x,y);
        HSLAPixel & canvas_pixel = canvas->getPixel(x,y);
          canvas_pixel.h = picture_pixel.h;
          canvas_pixel.s = picture_pixel.s;
          canvas_pixel.l = picture_pixel.l;
          canvas_pixel.a = picture_pixel.a;
        }
      }
      for (unsigned int z=0; z<cur; z++){
        unsigned int w = stickersheetimage[z]->width();
        unsigned int h = stickersheetimage[z]->height();
        for(unsigned int x=0; x<w;x++){
          for(unsigned int y=0; y<h;y++){
            HSLAPixel & sticker_pixel = stickersheetimage[z]->getPixel(x,y);
            HSLAPixel & canvas_pixel = canvas->getPixel(x+coordinatex[z],y+coordinatey[z]);
            if(sticker_pixel.a != 0){
            canvas_pixel.h = sticker_pixel.h;
            canvas_pixel.s = sticker_pixel.s;
            canvas_pixel.l = sticker_pixel.l;
            canvas_pixel.a = sticker_pixel.a;
            }
           }
          }
         }

    return *canvas;
    }

}
