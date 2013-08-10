//
// lib_misc.cpp
//

#include "lib_misc.h"

bool bounding_box_test(int b1_x, int b1_y, int b1_w, int b1_h, int b2_x, int b2_y, int b2_w, int b2_h) {
  // b1_x = box1_x , b1_w = box1_width , b1_h = box1_height , and so on...
  if ( (b1_x > (b2_x + b2_w) - 1) or (b1_y > (b2_y + b2_h) - 1) or (b2_x > (b1_x + b1_w) - 1) or (b2_y > (b1_y + b1_h) - 1) ) {
    return false;
  } else {
    return true;
  }
}

inline double degreeToRadians(double angle) {
  return (angle - 90) * pi / 180;
}

inline double radiansToDegree(double angle) {
  return angle * 180 / pi + 90;
}

double offsetX(double angle, double radius) {
  return +std::sin(angle / 180 * pi) * radius;
}

double offsetY(double angle, double radius) {
  return -std::cos(angle / 180 * pi) * radius;
}

double angle_from_coords(double fromX, double fromY, double toX, double toY, double def) {
  double distX = toX - fromX;
  double distY = toY - fromY;
  if (distX == 0 && distY == 0)
    return def;
  else
    return fmod(radiansToDegree(std::atan2(distY, distX)), 360);
}

std::vector<std::string> split_string(const std::string s, char delim) {
  std::vector<std::string> elems;
  std::stringstream ss(s);
  std::string item;
  while(std::getline(ss, item, delim)) {
    elems.push_back(item);
  }
  return elems;
}

