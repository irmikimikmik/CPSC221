#include "gridColorPicker.h"

gridColorPicker::gridColorPicker(HSLAPixel gridColor, int gridSpacing)
{
    /* Your code here! */
    color = gridColor;
    spacing = gridSpacing;
}

HSLAPixel gridColorPicker::operator()(int x, int y)
{
    HSLAPixel white;

    white.h = 0.0;
    white.s = 0.0;
    white.l = 1.0;

    if (x % spacing == 0 || y % spacing == 0){
        return color;
    } else {
        return white;
    }
    
}
