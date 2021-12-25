#include "block.h"
#include <cmath>
#include <iostream>

/* Returns the width, in pixels
 * of the current block
 */
int Block::width() const
{
    return data.size();
}

/* Returns the width, in pixels
 * of the current block
 */
int Block::height() const
{
    if (this->width() != 0) {
        return data[0].size();
    }
    return 0;
}

/* Given an image whose size is large enough, place
 * the current block in the image so that its upper left corner
 * is at position column, row. Existing pixels in the image
 * will be replaced by those of the block.
 */
void Block::render(PNG &im, int column, int row) const
{
    for (int x = column; x < column + width(); x++) {
        for (int y = row; y < row + height(); y++) {
            // point to the pixel from inputted image
            HSLAPixel* currPixel = im.getPixel(x,y);
            // change the value of the pointer with the one saved in block
            *currPixel = data[x-column][y-row];
        }
    }
}

/* create a block of pixels whose color values are the same as the
 * rectangle in the image described by the upper left corner (column, row)
 * whose size is width x height.
 */
void Block::build(PNG &im, int column, int row, int width, int height)
{

    for (int x = column; x < column + width; x++) {

        vector<HSLAPixel> cols;

        for (int y = row; y < row + height; y++) {
            // get the pixel from the PNG
            HSLAPixel* currPixel = im.getPixel(x,y);

            // place the pixel at the end of it's col's vector
            cols.push_back(*currPixel);
        }

        // add the cols to the columns a.k.a. data vector
        data.push_back(cols);
    }

}

/* Flip the current block across its horizontal midline.
 * This function changes the existing block.
 */
void Block::flipVert()
{
    for (int x = 0; x < width(); x++) {
        std::reverse(data[x].begin(), data[x].end());
    }
}

/* Flip the current block across its vertical midline.
 * This function changes the existing block.
 */
void Block::flipHoriz()
{
    std::reverse(data.begin(), data.end());
}

/* Rotate the current block 90 degrees counterclockwise.
 * This function changes the existing block.
 */
void Block::rotateRight()
{
    HSLAPixel temp;
    
    for (int x = 0; x < width(); x++){
        for (int y = x; y < height(); y++){
            temp = data[x][y];
            data[x][y] = data[y][x];
            data[y][x] = temp;
        }
    }

    std::reverse(data.begin(), data.end());
}
