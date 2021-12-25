#include <math.h>
#include "stats.h"

stats::stats(PNG & im){
    
    image = &im;
    unsigned int width = im.width();
    unsigned int height = im.height();

    sumHueX.resize(width, vector<double>(height, 0));
    sumHueY.resize(width, vector<double>(height, 0));
    sumSat.resize (width, vector<double>(height, 0));
    sumLum.resize (width, vector<double>(height, 0));
    hist.resize(width, vector<vector<int>>(height, vector<int>(36, 0)));

    HSLAPixel *currPixel;

    for(unsigned int i = 0; i < width; i++){             // i represents the x coordinate
        for(unsigned int j = 0; j < height; j++){        // j represents the y coordinate 

            currPixel = im.getPixel(i, j);
            double hueDegree = currPixel->h;
            int bucketNum = trunc(hueDegree / 10);

            makeHistogram(i,j, hist);
            if (bucketNum >= 36){
                printf("Error\n");
            }
            hist[i][j][bucketNum]++;
            

            double xHue = cos((PI * hueDegree)/180);
            double yHue = sin((PI * hueDegree)/180);
            double saturation = currPixel->s;
            double luminance = currPixel->l;

            if (i == 0 && j == 0) {
                sumHueX[i][j] = xHue;
                sumHueY[i][j] = yHue;
                sumSat[i][j]  = saturation;
                sumLum[i][j]  = luminance;
            } else if (j == 0) {
                sumHueX[i][j] = sumHueX[i - 1][j] + xHue;
                sumHueY[i][j] = sumHueY[i - 1][j] + yHue;
                sumSat[i][j]  =  sumSat[i - 1][j] + saturation;
                sumLum[i][j]  =  sumLum[i - 1][j] + luminance;
            } else if (i == 0) {
                sumHueX[i][j] = sumHueX[i][j - 1] + xHue;
                sumHueY[i][j] = sumHueY[i][j - 1] + yHue;
                sumSat[i][j]  =  sumSat[i][j - 1] + saturation;
                sumLum[i][j]  =  sumLum[i][j - 1] + luminance;
            } else {
                sumHueX[i][j] = sumHueX[i][j - 1] + sumHueX[i - 1][j] - sumHueX[i - 1][j - 1] + xHue;
                sumHueY[i][j] = sumHueY[i][j - 1] + sumHueY[i - 1][j] - sumHueY[i - 1][j - 1] + yHue;
                sumSat[i][j]  =  sumSat[i][j - 1] +  sumSat[i - 1][j] -  sumSat[i - 1][j - 1] + saturation;
                sumLum[i][j]  =  sumLum[i][j - 1] +  sumLum[i - 1][j] -  sumLum[i - 1][j - 1] + luminance;
            }
        }
    }
}

void stats::makeHistogram(int x, int y, vector<vector<vector<int>>>& histogram){
    for(int k = 0; k < 36; k++){
        if (x== 0 && y == 0){
            // do nothing
        } else if (x == 0) {
            hist[x][y][k] = hist[x][y-1][k];
        } else if(y == 0) {
            hist[x][y][k] = hist[x-1][y][k];
        } else {
            hist[x][y][k] = hist[x-1][y][k] + hist[x][y-1][k] - hist[x-1][y-1][k];
        }
    }
}

long stats::rectArea(pair<int,int> ul, pair<int,int> lr){

    int upperLeftX  = ul.first;
    int upperLeftY  = ul.second;
    int lowerRightX = lr.first;
    int lowerRightY = lr.second;

    if(lowerRightX - upperLeftX < 0){
        // this impossible
        printf("Impossible coordinates.\n");
    }

    long widthOfRect   = lowerRightX - upperLeftX + 1;
    long heightOfRect  = lowerRightY - upperLeftY + 1;
    long areaOfRect    = widthOfRect * heightOfRect;

    return areaOfRect;
}

HSLAPixel stats::getAvg(pair<int,int> ul, pair<int,int> lr){

    long area = rectArea(ul, lr);

    int upperLeftX  = ul.first;
    int upperLeftY  = ul.second;
    int lowerRightX = lr.first;
    int lowerRightY = lr.second;

    // initialize
    double totalSat;
    double totalLum;
    double totalXHue;
    double totalYHue;
    double diagonalRegionSat  = 0.0;
    double diagonalRegionLum  = 0.0;
    double diagonalRegionXHue = 0.0;
    double diagonalRegionYHue = 0.0;
    double leftRegionSat      = 0.0;
    double leftRegionLum      = 0.0;
    double leftRegionXHue     = 0.0;
    double leftRegionYHue     = 0.0;
    double upperRegionSat     = 0.0;
    double upperRegionLum     = 0.0;
    double upperRegionXHue    = 0.0;
    double upperRegionYHue    = 0.0;

    if(lowerRightX - upperLeftX == 0 && lowerRightY - upperLeftY == 0){
        // this represents a single pixel
        return *(image->getPixel(upperLeftX, upperLeftY));
    } else {
        totalSat  =  sumSat[lowerRightX][lowerRightY];
        totalLum  =  sumLum[lowerRightX][lowerRightY];
        totalXHue = sumHueX[lowerRightX][lowerRightY];
        totalYHue = sumHueY[lowerRightX][lowerRightY];
    }

    if(upperLeftX == 0 && upperLeftY == 0){
        //do nothing
    } else if (upperLeftX == 0){
        upperRegionSat  =  sumSat[lowerRightX][upperLeftY - 1];
        upperRegionLum  =  sumLum[lowerRightX][upperLeftY - 1];
        upperRegionXHue = sumHueX[lowerRightX][upperLeftY - 1];
        upperRegionYHue = sumHueY[lowerRightX][upperLeftY - 1];
    } else if (upperLeftY == 0){
        leftRegionSat  =  sumSat[upperLeftX - 1][lowerRightY];
        leftRegionLum  =  sumLum[upperLeftX - 1][lowerRightY];
        leftRegionXHue = sumHueX[upperLeftX - 1][lowerRightY];
        leftRegionYHue = sumHueY[upperLeftX - 1][lowerRightY];
    } else {
        upperRegionSat  =  sumSat[lowerRightX][upperLeftY - 1];
        upperRegionLum  =  sumLum[lowerRightX][upperLeftY - 1];
        upperRegionXHue = sumHueX[lowerRightX][upperLeftY - 1];
        upperRegionYHue = sumHueY[lowerRightX][upperLeftY - 1];

        leftRegionSat  =  sumSat[upperLeftX - 1][lowerRightY];
        leftRegionLum  =  sumLum[upperLeftX - 1][lowerRightY];
        leftRegionXHue = sumHueX[upperLeftX - 1][lowerRightY];
        leftRegionYHue = sumHueY[upperLeftX - 1][lowerRightY];

        diagonalRegionSat  =  sumSat[upperLeftX - 1][upperLeftY - 1];
        diagonalRegionLum  =  sumLum[upperLeftX - 1][upperLeftY - 1];
        diagonalRegionXHue = sumHueX[upperLeftX - 1][upperLeftY - 1];
        diagonalRegionYHue = sumHueY[upperLeftX - 1][upperLeftY - 1];
    }

    double resultSat  = totalSat  - upperRegionSat  - leftRegionSat  + diagonalRegionSat;
    double resultLum  = totalLum  - upperRegionLum  - leftRegionLum  + diagonalRegionLum;
    double resultXHue = totalXHue - upperRegionXHue - leftRegionXHue + diagonalRegionXHue;
    double resultYHue = totalYHue - upperRegionYHue - leftRegionYHue + diagonalRegionYHue;

    double saturation = resultSat / area;
    double luminance  = resultLum / area;
    double hue;

    if (atan2(resultYHue, resultXHue) < 0) {
        hue = (atan2(resultYHue, resultXHue) * 180 / PI) + 360;
    } else {
        hue = atan2(resultYHue, resultXHue) * 180 / PI;
    }

    return HSLAPixel(hue, saturation, luminance, 1.0);

}

double stats::entropy(pair<int,int> ul, pair<int,int> lr){

    // an integer has been used instead of an integer vector for runtime purposes
    int distn;
    long area = rectArea(ul, lr);

    int upperLeftX  = ul.first;
    int upperLeftY  = ul.second;
    int lowerRightX = lr.first;
    int lowerRightY = lr.second;
    
    double entropy = 0.0;

    int *totalHist = &hist[lowerRightX][lowerRightY][0];
   
    if(upperLeftX == 0 && upperLeftY == 0){

        for(int k = 0; k < 36; k++){
            distn = *(totalHist + k);
            if (distn > 0){
                entropy += ((double) distn/(double) area) * log2((double) distn/(double) area);
            }
        }

    } else if (upperLeftX == 0){

        int *upperHist = &hist[lowerRightX][upperLeftY - 1][0];
       
       for(int k = 0; k < 36; k++){
           distn = *(totalHist + k) - *(upperHist + k);
           if (distn > 0){
                entropy += ((double) distn/(double) area) * log2((double) distn/(double) area);
            }
        }

        upperHist = NULL;
        
    } else if (upperLeftY == 0){

        int *leftHist = &hist[upperLeftX - 1][lowerRightY][0];
        
        for(int k = 0; k < 36; k++){
            distn = *(totalHist + k) - *(leftHist + k);

            if (distn > 0){
                entropy += ((double) distn/(double) area) * log2((double) distn/(double) area);
            }
        }

        leftHist = NULL;
    
    } else {

        int *upperHist = &hist[lowerRightX][upperLeftY - 1][0];
        int *leftHist = &hist[upperLeftX - 1][lowerRightY][0];
        
        for(int k = 0; k < 36; k++){
            distn = *(totalHist + k) - *(leftHist + k) - *(upperHist + k) + hist[upperLeftX - 1][upperLeftY - 1][k];

            if (distn > 0){
                entropy += ((double) distn/(double) area) * log2((double) distn/(double) area);
            }
        }

        upperHist = NULL;
        leftHist = NULL;
    }

    totalHist = NULL;

    return  -1 * entropy;
}
