#ifndef HSLAPIXEL_H
#define HSLAPIXEL_H

namespace cs221util {

  class HSLAPixel
  {  
    public:
    
    double h, s, l, a;
    HSLAPixel();
    void HSLAPixel3(double hue, double saturation, double luminance);
    void HSLAPixel4(double hue, double saturation, double luminance, double alpha);
    
  };

}

#endif