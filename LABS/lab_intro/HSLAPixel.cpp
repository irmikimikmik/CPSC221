#include <iostream>
#include <cstdlib>

#include "HSLAPixel.h"

using namespace cs221util;

HSLAPixel::HSLAPixel()
{
  h = 0;
  s = 0;
  l = 1.0;
  a = 1.0;
}

void HSLAPixel::HSLAPixel3(double hue, double saturation, double luminance)
{
  h = hue;
  s = saturation;
  l = luminance;
}

void HSLAPixel::HSLAPixel4(double hue, double saturation, double luminance,
  double alpha)
{
  h = hue;
  s = saturation;
  l = luminance;
  a = alpha;
}
