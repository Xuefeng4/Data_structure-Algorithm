#include "List.h"


#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#include "./cs225/PNG.h"
#include "./cs225/HSLAPixel.h"


int main() {
  List<int> list;

  for (unsigned i = 0; i < 10; i++) { list.insertFront(i); }
  std::cout << list <<std::endl;
  return 0;
}
