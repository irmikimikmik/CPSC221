/**
 * @file filler.h
 * Defintion of a filler namespace.
 *
 */
#ifndef _FILLER_H_
#define _FILLER_H_

#include "cs221util/PNG.h"
#include "stack.h"
#include "queue.h"
#include "solidColorPicker.h"
#include "gridColorPicker.h"
#include "gradientColorPicker.h"
#include "rainbowColorPicker.h"
#include "animation.h"
using namespace cs221util;

/**
 * filler namespace: specifies a set of functions for performing flood
 * fills on images. A namespace is a mechanism for placing several
 * functions within the same "scope". To call the functions in 
 * the namespace, you simply preface them with "filler::".
 *
 */
namespace filler
{
        /**
         * Performs a flood fill on the given image using a solid color,
         * employing a depth-first-search approach.
         *
         * @param img The image to be filled.
         * @param x The starting x coordinate for the fill.
         * @param y The starting y coordinate for the fill.
         * @param fillColor The color of the fill.
         * @param tolerance How far away colors are allowed to be to
         *  still be included in the fill.
         * @param frameFreq How frequently to add a frame to the
         *  animation, in pixels. For instance, if frameFreq == 1, a frame is
         *  added when every pixel is filled. If frameFreq == 10, a frame is
         *  added after every 10 pixels is filled.
         * @return An animation that shows the fill progressing over the image.
         */
        animation fillSolidDFS(PNG& img, int x, int y, HSLAPixel fillColor,
                double tolerance, int frameFreq);

        /**
         * Performs a flood fill on the given image using a grid,
         * employing a depth-first-search approach.
         *
         * @param img The image to be filled.
         * @param x The starting x coordinate for the fill.
         * @param y The starting y coordinate for the fill.
         * @param gridColor The color the lines of the grid should appear.
         * @param gridSpacing The width and height of the cells of the grid.
         * @param tolerance How far away colors are allowed to be to 
         * still be included in the fill.
         * @param frameFreq How frequently to add a frame to the 
         * animation, in pixels. For instance, if frameFreq == 1, 
         * a frame is added when every pixel is filled. If 
         * frameFreq == 10, a frame is added after every 10
         *  pixels is filled.
         *
         * @return An animation that shows the fill progressing 
         * over the image.
         */
        animation fillGridDFS(PNG& img, int x, int y, HSLAPixel gridColor,
                           int gridSpacing, double tolerance, int frameFreq);

        /**
         * Performs a flood fill on the given image using a gradient, employing
         * a depth-first-search approach.
         *
         * @param img The image to be filled.
         * @param x The starting x coordinate for the fill.
         * @param y The starting y coordinate for the fill.
         * @param fadeColor1 The starting color of the gradient.
         * @param fadeColor2 The ending color of the gradient.
         * @param radius The radius for the gradient.
         * @param tolerance How far away colors are allowed to be to still be
         *  included in the fill.
         * @param frameFreq How frequently to add a frame to the animation, in
         *  pixels. For instance, if frameFreq == 1, a frame is added when every
         *  pixel is filled. If frameFreq == 10, a frame is added after every 10
         *  pixels is filled.
         * @return An animation that shows the fill progressing over the image.
         */
        animation fillGradientDFS(PNG& img, int x, int y, HSLAPixel fadeColor1,
                HSLAPixel fadeColor2, int radius, double tolerance,
                int frameFreq);

        /**
         * Performs a flood fill on the given image using a solid color,
         * employing a breadth-first-search approach.
         *
         * @param img The image to be filled.
         * @param x The starting x coordinate for the fill.
         * @param y The starting y coordinate for the fill.
         * @param fillColor The color of the fill.
         * @param tolerance How far away colors are allowed to be to still be
         *  included in the fill.
         * @param frameFreq How frequently to add a frame to the animation, in
         *  pixels. For instance, if frameFreq == 1, a frame is added when every
         *  pixel is filled. If frameFreq == 10, a frame is added after every 10
         *  pixels is filled.
         * @return An animation that shows the fill progressing over the image.
         */
        animation fillSolidBFS(PNG& img, int x, int y, HSLAPixel fillColor,
                double tolerance, int frameFreq);

        /**
         * Performs a flood fill on the given image using a grid, employing a
         * breadth-first-search approach.
         *
         * @param img The image to be filled.
         * @param x The starting x coordinate for the fill.
         * @param y The starting y coordinate for the fill.
         * @param gridColor The color the lines of the grid should appear.
         * @param gridSpacing The width and height of the cells of the grid.
         * @param tolerance How far away colors are allowed to be to still be
         *  included in the fill.
         * @param frameFreq How frequently to add a frame to the animation, in
         *  pixels. For instance, if frameFreq == 1, a frame is added when every
         *  pixel is filled. If frameFreq == 10, a frame is added after every 10
         *  pixels is filled.
         * @return An animation that shows the fill progressing over the image.
         */
        animation fillGridBFS(PNG& img, int x, int y, HSLAPixel gridColor,
                int gridSpacing, double tolerance, int frameFreq);

        /**
         * Performs a flood fill on the given image using a gradient,
         * employing a breadth-first-search approach.
         *
         * @param img The image to be filled.
         * @param x The starting x coordinate for the fill.
         * @param y The starting y coordinate for the fill.
         * @param fadeColor1 The starting color of the gradient.
         * @param fadeColor2 The ending color of the gradient.
         * @param radius The radius for the gradient.
         * @param tolerance How far away colors are allowed to be to still
         *  be included in the fill.
         * @param frameFreq How frequently to add a frame to the animation,
         *  in pixels. For instance, if frameFreq == 1, a frame is added
         *  when every pixel is filled. If frameFreq == 10, a frame is added
         *  after every 10 pixels is filled.
         * @return An animation that shows the fill progressing over the
         *  image.
         */
        animation fillGradientBFS(PNG& img, int x, int y, HSLAPixel fadeColor1,
                HSLAPixel fadeColor2, int radius, double tolerance,
                int frameFreq);

        /* The following two functions are given to you as examples of 
         * working fill functions. 
        */
        animation fillRainDFS(PNG& img, int x, int y, long double freq, double tolerance, int frameFreq);

        animation fillRainBFS(PNG& img, int x, int y, long double freq, double tolerance, int frameFreq);

        void sendToFrame(int k, int frameFreq, animation a, PNG& img);

        bool isWithinTolerance(HSLAPixel originalPixel, double tolerance, HSLAPixel *currPixel);

        /**
         * General filling function: a general helper that should be invoked by
         * all of the public fill functions with the appropriate color picker
         * for that type of fill.
         *
         * For examples, a) filler::dfs::fillSolid should call fill with the
         * correct ordering structure as its template parameter, passing in a
         * solidColorPicker object.
         *
         * b) filler::bfs::fillGradient should call fill with a different 
         * ordering structure as its template parameter, passing in a
         * gradientColorPicker object.
         *
         * @param img Image to do the filling on.
         * @param x X coordinate to start the fill from.
         * @param y Y coordinate to start the fill from.
         * @param fillColor The colorPicker to be used for the fill.
         * @param tolerance How far away colors are allowed to be to still be
         *  included in the fill.
         * @param frameFreq How frequently to add a frame to the animation, in
         *  pixels. For instance, if frameFreq == 1, a frame is added when every
         *  pixel is filled. If frameFreq == 10, a frame is added after every 10
         *  pixels is filled.
         * @return An animation that shows the fill progressing over the image.
         * 
         * Note: implementation instructions are in the .cpp file
         *
         */
        template <template <class T> class OrderingStructure>
        animation fill(PNG& img, int x, int y, colorPicker& fillColor,
                        double tolerance, int frameFreq);

}
#include "filler.cpp"
#endif
