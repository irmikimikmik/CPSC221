/**
 * @file gridColorPicker.h
 * Definition of a grid color picker.
 *
 */
#ifndef GRIDCOLORPICKER_H
#define GRIDCOLORPICKER_H

#include "colorPicker.h"

/**
 * gridColorPicker: a functor that determines the color that should be used
 * given an x and a y coordinate using a grid pattern.
 *
 */
class gridColorPicker : public colorPicker
{
  public:
    /**
     * Constructs a new gridColorPicker.
     *
     * @param fillColor Color for the border between cells of the grid.
     * @param gridSpacing Spacing between cells of the grid.
     */
    gridColorPicker(HSLAPixel fillColor, int gridSpacing);

    /**
     * Picks the color for pixel (x, y). If the x or y coordinate is a
     * multiple of the spacing, it will be filled with the fillColor.
     * otherwise, it will be filled with white.
     *
     * @param x The x coordinate to pick a color for.
     * @param y The y coordinat to pick a color for.
     * @return The color chosen for (x, y).
     */
    virtual HSLAPixel operator()(int x, int y);

  private:
    HSLAPixel color; /**< Color used for the grid border. */
    int spacing;     /**< Spacing for cells in the grid. */
};

#endif
