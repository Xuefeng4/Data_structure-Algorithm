/**
 * @file StickerSheet.h
 * Contains your declaration of the interface for the StickerSheet class.
 */
#pragma once

namespace cs225{
class StickerSheet {
public:
  StickerSheet(const Image & picture, unsigned max);
  ~StickerSheet();
  StickerSheet(const StickerSheet & other);
  const StickerSheet & operator = (const StickerSheet & other);//do not understand

  void changeMaxStickers(unsigned max);
  int addSticker(Image & sticker, unsigned x, unsigned y);
  bool translate(unsigned index, unsigned x, unsigned y);
  void removeSticker(unsigned index);

  Image * getSticker(unsigned index);

  Image render() const;

private:
  Image ** stickersheetimage;
  const Image & picture_;
  unsigned int max_;
  unsigned int cur;
  unsigned int *coordinatex;
  unsigned int *coordinatey;
  void _destory();
  void _copy(const StickerSheet & other);
};
}
