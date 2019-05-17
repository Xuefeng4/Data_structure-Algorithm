#include "Image.h"
#include "StickerSheet.h"
using namespace cs225;
int main() {

  //
  // Reminder:
  //   Before exiting main, save your creation to disk as myImage.png
  //

  Image base; base.readFromFile("base.png");
  Image star1; star1.readFromFile("star1.png");
  Image star2; star2.readFromFile("star2.png");
  Image star3; star3.readFromFile("star3.png");
  Image star4; star4.readFromFile("star4.png");
  Image star5; star5.readFromFile("star5.png");
  Image star6; star6.readFromFile("star6.png");

  StickerSheet myCreation(base, 6);
  myCreation.addSticker(star1, 1000, 500);
  myCreation.addSticker(star2, 1700, 500);
  myCreation.addSticker(star3, 900, 1200);
  myCreation.addSticker(star4, 2500, 400);
  myCreation.addSticker(star5, 1600, 1200);
  myCreation.addSticker(star6, 2600, 1200);


  myCreation.render().writeToFile("myImage.png");

  return 0;
}
