#include <cstdlib>
#include <cmath>
#include <iostream>
#include "cs221util/PNG.h"
#include "cs221util/HSLAPixel.h"

using namespace cs221util;
using namespace std;

// sets up the output image
PNG* setupOutput(unsigned w, unsigned h) {
    PNG* image = new PNG(w, h);
    return image;
}

// Returns my favorite color
HSLAPixel* myFavoriteColor(double saturation) {
    HSLAPixel* pixel = new HSLAPixel(170, saturation, 0.5);
    // HSLAPixel* pixelAddress = &pixel;
    return pixel;
}

// Returns a score determining if the pixel is an edge
// requires 1 <= x < width - 1; 1 <= y < height - 1
double edgeScore(PNG* im, unsigned x, unsigned y) {
    double score = 0;

    // calculate score based on the luminance of the curret pixel
    // and the 8 neighboring pixels around it
    for (int i = -1; i < 2; i++){
        for (int j = -1; j < 2; j++){
            if (i == 0 && j == 0) {
                score += 8 * (im->getPixel(x,y)->l);
            } else {
                score -= im->getPixel(x+i, y+j)->l;
            }
        }
    }
    return score;
}

void sketchify(std::string inputFile, std::string outputFile) {
    // Load in.png
    PNG* original = new PNG();
    cout << "Reached line 45 while loading in.png." << endl;
    original->readFromFile(inputFile);
    unsigned width = original->width();
    unsigned height = original->height();
    // Create out.png
    PNG* output = setupOutput(width, height);
    cout << "Reached line 51 and the output has been set up." << endl;

    // Load our favorite color to color the outline
    HSLAPixel* myPixel = myFavoriteColor(0.5);

    cout << "Reached line 56, before the for loops and after loading and creating input and output images." << endl;

    // Go over the whole image, and if a pixel is likely to be an edge,
    // color it my favorite color in the output
    for (unsigned int y = 1; y < height-1; y++) {
        for (unsigned int x = 1; x < width-1; x++) {

            double score = edgeScore(original, x, y);

            HSLAPixel* currOutPixel = (*output).getPixel(x, y);

            // If the pixel is an edge pixel,
            // color the output pixel with my favorite color
            if (score > 0.3) {
                *currOutPixel = *myPixel;
            }
            
        }
    }

    cout << "Reached line 76, after both for loop" << endl;

    // Save the output file
    output->writeToFile(outputFile);

    cout << "Reached line 81, after saving the output" << endl;
 
    // Clean up memory
    // delete myPixel;
    delete output;
    delete original;
}
