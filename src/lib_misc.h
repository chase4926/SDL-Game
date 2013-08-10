//
// lib_misc.h
//

#ifndef LIB_MISC_H
#define LIB_MISC_H

#include <string>
#include <sstream>
#include <vector>
#include <cmath>

const double pi = 3.1415926536;

bool bounding_box_test(int, int, int, int, int, int, int, int);

inline double degreeToRadians(double);

inline double radiansToDegree(double);

double offsetX(double, double);

double offsetY(double, double);

double angle_from_coords(double, double, double, double, double);

std::vector<std::string> split_string(const std::string, char);

#endif

