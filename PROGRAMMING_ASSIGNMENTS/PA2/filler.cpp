/**
 * @file filler.cpp
 * Implementation of functions in the filler namespace. 
 *
 */
#include "filler.h"
#include "vector"

animation filler::fillSolidDFS(PNG& img, int x, int y, HSLAPixel fillColor,
                                 double tolerance, int frameFreq)
{
    solidColorPicker solidDFS(fillColor);
    return filler::fill<Stack>(img, x, y, solidDFS, tolerance, frameFreq);
    
}

animation filler::fillGridDFS(PNG& img, int x, int y, HSLAPixel gridColor,
                                int gridSpacing, double tolerance, int frameFreq)
{
    gridColorPicker gridDFS(gridColor, gridSpacing);
    return filler::fill<Stack>(img, x, y, gridDFS, tolerance, frameFreq);

}

animation filler::fillGradientDFS(PNG& img, int x, int y,
                                    HSLAPixel fadeColor1, HSLAPixel fadeColor2,
                                    int radius, double tolerance, int frameFreq)
{
    gradientColorPicker gradientDFS(fadeColor1, fadeColor2, radius, x, y);
    return filler::fill<Stack>(img, x, y, gradientDFS, tolerance, frameFreq);
}


animation filler::fillRainDFS(PNG& img, int x, int y,
                                    long double freq, double tolerance, int frameFreq)
{
    /**
     *  Our code here!
     */

    rainbowColorPicker a(freq);
    return filler::fill<Stack>(img, x, y, a, tolerance, frameFreq);
}

animation filler::fillSolidBFS(PNG& img, int x, int y, HSLAPixel fillColor,
                                 double tolerance, int frameFreq)
{
    solidColorPicker solidBFS(fillColor);
    return filler::fill<Queue>(img, x, y, solidBFS, tolerance, frameFreq);
}

animation filler::fillGridBFS(PNG& img, int x, int y, HSLAPixel gridColor,
                                int gridSpacing, double tolerance, int frameFreq)
{
    gridColorPicker gridBFS(gridColor, gridSpacing);
    return filler::fill<Queue>(img, x, y, gridBFS, tolerance, frameFreq);
}

animation filler::fillGradientBFS(PNG& img, int x, int y,
                                    HSLAPixel fadeColor1, HSLAPixel fadeColor2,
                                    int radius, double tolerance, int frameFreq)
{
    gradientColorPicker gradientBFS(fadeColor1, fadeColor2, radius, x, y);
    return filler::fill<Queue>(img, x, y, gradientBFS, tolerance, frameFreq);
}

animation filler::fillRainBFS(PNG& img, int x, int y,
                                    long double freq, double tolerance, int frameFreq)
{
    /**
     * Our code here!
     */
    rainbowColorPicker a(freq);
    return filler::fill<Queue>(img, x, y, a, tolerance, frameFreq);
}


bool filler::isWithinTolerance(HSLAPixel originalPixel, double tolerance, HSLAPixel *currPixel){

    return currPixel->dist(originalPixel) <= tolerance;
}

template <template <class T> class OrderingStructure>
animation filler::fill(PNG& img, int x, int y, colorPicker& fillColor,
                       double tolerance, int frameFreq)
{
    int k = 0;

    // here is a 2d array representing the coordinates of an image, the value is true if processed and false if not processed
    vector<vector<bool>> processing;

    // initialize the entire 2d array to be unprocessed at the beginning
    for(unsigned int i = 0; i < img.width(); i++){
        vector<bool> vertical;
        for(unsigned int j = 0; j < img.height(); j++){
            vertical.push_back(false);
        }
        processing.push_back(vertical);
    }

    animation a;
    // create the ordering structure
    OrderingStructure<vector<int>> os;
    
    // create the first coordinates
    vector<int> firstCoordinates;
    firstCoordinates.push_back(x);
    firstCoordinates.push_back(y);

    // a)
    // add coordinates to ordering structure
    os.add(firstCoordinates);
    // mark the coordinates processed
    processing[x][y] = true;
    

    // b)
    HSLAPixel *firstPixel = img.getPixel(x, y);
    HSLAPixel originalFirstPixel = *firstPixel;
    *firstPixel = fillColor(x, y);

    // c)
    k++;
    if (k % frameFreq == 0){
        a.addFrame(img);
    }

    while (!os.isEmpty()){

        vector<int> coordinatesToRemove;
        coordinatesToRemove = os.remove();
        int xCor = coordinatesToRemove[0];
        int yCor = coordinatesToRemove[1];

        
        // check if inside image width and height
        if (xCor+1 < img.width() && yCor < img.height() && !(processing[xCor+1][yCor])){
            vector<int> rightNeighboringCoordinate;
            // puts x+1 as the x coordinate
            rightNeighboringCoordinate.push_back(xCor+1);
            // puts y as the y coordinate
            rightNeighboringCoordinate.push_back(yCor);
            // create a pixel pointer to the neighboring pixel
            HSLAPixel *rightNeighboringPixel = img.getPixel(xCor+1, yCor);

            // check if the neighboring pixel is within the tolerance and unprocessed
            if(isWithinTolerance(originalFirstPixel, tolerance, rightNeighboringPixel)){
                // set the new color
                *rightNeighboringPixel = fillColor(xCor+1, yCor);
                // send to frame
                k++;
                if (k % frameFreq == 0){
                    a.addFrame(img);
                }
                os.add(rightNeighboringCoordinate);
                // mark as processed
                processing[xCor+1][yCor] = true;
            }
            
        }
        
        

        // check if inside image width and height
        if (xCor < img.width() && yCor+1 < img.height() && !(processing[xCor][yCor+1])){
            vector<int> downNeighboringCoordinate;
            // puts x as the x coordinate
            downNeighboringCoordinate.push_back(xCor);
            // puts y+1 as the y coordinate
            downNeighboringCoordinate.push_back(yCor+1);
            // create a pixel pointer to the neighboring pixel
            HSLAPixel *downNeighboringPixel = img.getPixel(xCor, yCor+1);

            // check if the neighboring pixel is within the tolerance and unprocessed
            if(isWithinTolerance(originalFirstPixel, tolerance, downNeighboringPixel)){
            
                // set the new color
                *downNeighboringPixel = fillColor(xCor, yCor+1);
                
                k++;
                // send to frame
                if (k % frameFreq == 0){
                    a.addFrame(img);
                }
                // add to os
                os.add(downNeighboringCoordinate);
                
                // mark as processed
                processing[xCor][yCor+1] = true;
            }
            
        }


        

        
        if (xCor-1 < img.width() && yCor < img.height() && !(processing[xCor - 1][yCor])){
            // check if the neighboring pixel is within the tolerance and unprocessed
            vector<int> leftNeighboringCoordinate;
            // puts x-1 as the x coordinate
            leftNeighboringCoordinate.push_back(xCor-1);
            // puts y as the y coordinate
            leftNeighboringCoordinate.push_back(yCor);
            // create a pixel pointer to the neighboring pixel
            HSLAPixel *leftNeighboringPixel = img.getPixel(xCor-1, yCor);

            if(isWithinTolerance(originalFirstPixel, tolerance, leftNeighboringPixel)){
            // check if inside image width and height
            
                // set the new color
                *leftNeighboringPixel = fillColor(xCor-1, yCor);
                
                k++;
                // send to frame
                if (k % frameFreq == 0){
                    a.addFrame(img);
                }
                // add to os
                os.add(leftNeighboringCoordinate);
                
                // mark as processed
                processing[xCor-1][yCor] = true;           
            }
            
        }
        
        

    
        // check if inside image width and height
        if (xCor < img.width() && yCor-1 < img.height() && !(processing[xCor][yCor-1])){
            // check if the neighboring pixel is within the tolerance and unprocessed
            vector<int> upNeighboringCoordinate;
            // puts x as the x coordinate
            upNeighboringCoordinate.push_back(xCor);
            // puts y-1 as the y coordinate
            upNeighboringCoordinate.push_back(yCor-1);
            // create a pixel pointer to the neighboring pixel
            HSLAPixel *upNeighboringPixel = img.getPixel(xCor, yCor-1);

            if(isWithinTolerance(originalFirstPixel, tolerance, upNeighboringPixel)){
                
                // set the new color
                *upNeighboringPixel = fillColor(xCor, yCor-1);
                
                k++;
                // send to frame
                if (k % frameFreq == 0){
                    a.addFrame(img);
                }
                // add to os
                os.add(upNeighboringCoordinate);
                
                // mark as processed
                processing[xCor][yCor-1] = true;
            }
        }
    }

    // send one last frame to the animation
    a.addFrame(img);
    return a;

    
    /**
     * @todo You need to implement this function!
     *
     * This is the basic description of a flood-fill algorithm: Every fill
     * algorithm requires an ordering structure, which is passed to this
     * function via its template parameter. For a breadth-first-search
     * fill, that structure is a Queue, for a depth-first-search, that
     * structure is a Stack. 
     *
     * To begin the algorithm, you simply:
     * a) place the given point in the ordering structure, 
     * marking it processed (the way you mark it is a design 
     * decision you'll make yourself).
     *
     * b) We have a choice to either change the color, if appropriate, 
     * when we * add the point to the OS, or when we take it off. 
     * In our test cases, * we have assumed that you will change 
     * the color when a point is added to the structure. 
     *
     * c) Add the first image to the animation (it's convenient to 
     * think of this as the 0th image). 
     *
     * THEN, until the structure is empty, you do the following:
     *
     * 1.     Remove a point from the ordering structure, and then...
     *
     *        a.    add its unprocessed neighbors whose color values are 
     *              within (or equal to) tolerance distance from the 
     *              center's color, to the ordering structure, set their
     *              new color, and mark them as processed.
     *        b.    if it is an appropriate frame, send the current 
     *              PNG to the animation (as described below).
     *
     * 2.     When implementing your breadth-first-search and
     *        depth-first-search fills, you will need to explore 
     *        neighboring pixels in some order.
     *
     *        While the order in which you examine neighbors does 
     *        not matter for a proper fill, you must use the same 
     *        order as we do for your animations to come out like 
     *        ours! The order you should put neighboring pixels 
     *        **ONTO** the queue or stack is as follows:
     *        RIGHT(+x), DOWN(+y), LEFT(-x), UP(-y). 
     *        IMPORTANT NOTE: *UP* here means towards the top of 
     *        the image, so since an image has smaller y coordinates 
     *        at the top, this is in the *negative y*
     *        direction. Similarly, *DOWN* means in the *positive y*
     *        direction. 
     *
     *        To reiterate, when you are exploring 
     *        (filling out) from a given pixel, you must first try 
     *        to fill the pixel to
     *        it's RIGHT, then the one DOWN from it, then to the LEFT and
     *        finally UP. If you do them in a different order, your fill may
     *        still work correctly, but your animations will be different
     *        from the grading scripts!
     *
     * 3.     For every k pixels filled, **starting at the kth pixel**, you
     *        must add a frame to the animation, where k = frameFreq.
     *
     *        For example, if frameFreq is 4, then after the 4th pixel has
     *        been filled you should add a frame to the animation, then 
     *        again after the 8th pixel, etc.  You must only add 
     *        frames for the number of pixels that have been filled, 
     *        not the number that have been checked. So if frameFreq 
     *        is set to 1, a pixel should be filled every frame.
     *
     * 4.     Finally, as you leave the function, send one last frame to the
     *        animation. This frame will be the final result of the 
     *        fill, and it will be the one we test against.
     */

} 
