#include "colors.h"

const Color darkGrey = 0;
const Color green = 1;
const Color red = 2;
const Color orange = 3;
const Color yellow = 4;
const Color purple = 5;
const Color cyan = 6;
const Color blue = 7;
const Color lightBlue = 8;
const Color darkBlue = 9;

std::vector<Color> GetCellColors() {
  return {darkGrey, green, red, orange, yellow, purple, cyan, blue, lightBlue};
}
