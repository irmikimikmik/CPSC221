
/**
 *
 * twoDtree (pa3)
 * slight modification of a Kd tree of dimension 2.
 * twoDtree.cpp
 * This file will be used for grading.
 *
 */

#include "twoDtree.h"

/* node constructor given */
twoDtree::Node::Node(pair<int,int> ul, pair<int,int> lr, HSLAPixel a)
	:upLeft(ul),lowRight(lr),avg(a),LT(NULL),RB(NULL)
	{}

/* destructor given */
twoDtree::~twoDtree(){
	clear();
}

/* copy constructor given */
twoDtree::twoDtree(const twoDtree & other) {
	copy(other);
}


/* operator= given */
twoDtree & twoDtree::operator=(const twoDtree & rhs){
	if (this != &rhs) {
		clear();
		copy(rhs);
	}
	return *this;
}

/* twoDtree constructor */
twoDtree::twoDtree(PNG & imIn){ 

	width  = imIn.width();
	height = imIn.height();

   // build stats
	stats imStats = stats(imIn);

	pair<int,int> upLeftCorner;
	upLeftCorner.first = 0;
	upLeftCorner.second = 0;
	pair<int,int> lowRightCorner;
	lowRightCorner.first  =  width - 1;
	lowRightCorner.second = height - 1;

	root = buildTree(imStats, upLeftCorner, lowRightCorner, true);

}

/* buildTree helper for twoDtree constructor */
twoDtree::Node * twoDtree::buildTree(stats & s, pair<int,int>& ul, pair<int,int>& lr, bool vert) {

	double minEntropy = 1000000000000000000000000000.0;

	int upperLeftX  = ul.first;
	int upperLeftY  = ul.second;
	int lowerRightX = lr.first;
    int lowerRightY = lr.second;
	int totalArea = s.rectArea(ul,lr);

	pair<int,int> upperLeftCorner;
	pair<int,int> lowerRightCorner;

	double areaOfSplit1;
	double areaOfSplit2;
	double entropyOfSplit1;
	double entropyOfSplit2;
	bool nextVert = !vert;

	if(upperLeftX - lowerRightX == 0 && upperLeftY - lowerRightY == 0){		// the last node is just going to be a pixel
		HSLAPixel avg = s.getAvg(ul, lr);								    // this is the base case
		Node *pixelNode = new Node(ul, lr, avg);
		pixelNode->LT = nullptr;
		pixelNode->RB = nullptr;
		return pixelNode;
	} else if(upperLeftX - lowerRightX == 0){                       		// width is only 1 -> horizontal
		vert = false;
	} else if (upperLeftY - lowerRightY == 0){             			 		// height is only 1 -> vertical
		vert = true;
	}

	if(vert){

		for(int i = upperLeftX; i < lowerRightX; i++){
			// find area of split
			areaOfSplit1 = s.rectArea(ul, make_pair(i, lr.second));			// Split 1 is the left rectangle
			areaOfSplit2 = s.rectArea(make_pair(i+1, ul.second), lr);		// Split 2 is the right rectangle
			// find entropies of splits (weighted averages in other words)
			entropyOfSplit1 = (areaOfSplit1 * s.entropy(ul, make_pair(i, lr.second)))   / totalArea; 
			entropyOfSplit2 = (areaOfSplit2 * s.entropy(make_pair(i+1, ul.second), lr)) / totalArea; 

			double sumOfEntropies = entropyOfSplit1 + entropyOfSplit2;
			if (sumOfEntropies <= minEntropy) {
				minEntropy = sumOfEntropies;
				upperLeftCorner  = make_pair(i+1, ul.second);				// upper left of right rectangle
				lowerRightCorner = make_pair(i, lr.second);					// lower right of left rectangle
			}
		}

	} else {

		for(int j = upperLeftY; j < lowerRightY; j++){
			// find area of split
			areaOfSplit1 = s.rectArea(ul, make_pair(lr.first, j));			// Split 1 is the upper rectangle
			areaOfSplit2 = s.rectArea(make_pair(ul.first, j+1), lr);		// Split 2 is the lower rectangle
			// find entropies of splits (weighted averages in other words)
			entropyOfSplit1 = (areaOfSplit1 * s.entropy(ul, make_pair(lr.first, j)))   / totalArea; 
			entropyOfSplit2 = (areaOfSplit2 * s.entropy(make_pair(ul.first, j+1), lr)) / totalArea; 

			double sumOfEntropies = entropyOfSplit1 + entropyOfSplit2;
			if (sumOfEntropies <= minEntropy) {
				minEntropy = sumOfEntropies;
				upperLeftCorner  = make_pair(ul.first, j+1);				// upper left of lower rectangle
				lowerRightCorner = make_pair(lr.first, j);					// lower right of upper rectangle
			}
		}
	}

	HSLAPixel averageColor = s.getAvg(ul, lr);
	Node *result = new Node(ul, lr, averageColor);
	
	result->LT = buildTree(s,               ul, lowerRightCorner, nextVert);
	result->RB = buildTree(s, upperLeftCorner,                lr, nextVert);

	return result;
	
}

/* render your twoDtree into a png */
PNG twoDtree::render(){

	PNG *png = new PNG(width, height);
	PNG *out = render_helper(root, *png);
	out->writeToFile("rendered.png");
	return *out;

}

PNG *twoDtree::render_helper(Node *subRoot, PNG & png){


	if (subRoot == nullptr){									
		// not a possible case
		return &png;
	}

	int upLeftX      = subRoot->upLeft.first;
	int upLeftY      = subRoot->upLeft.second;
	int lowRightX    = subRoot->lowRight.first;
	int lowRightY    = subRoot->lowRight.second;
	HSLAPixel *currPixel;


	if(subRoot->LT == nullptr && subRoot->RB == nullptr) {

		for(int i = upLeftX; i <= lowRightX; i++){
			for(int j = upLeftY; j <= lowRightY; j++){
				currPixel = png.getPixel(i, j);					// base case
				*currPixel = subRoot->avg;
			}
		}

		return &png;
		
	} else {

		if(subRoot->LT != nullptr){
			render_helper(subRoot->LT, png);
		}

		if(subRoot->RB != nullptr){
			render_helper(subRoot->RB, png);
		}

	}

	return &png;

}

bool twoDtree::isInTol(Node *subRoot, double tol, HSLAPixel& avg){

	if(subRoot == nullptr){
		return true;
	}

	// to do on each leaf
	if (subRoot->LT == nullptr && subRoot->RB == nullptr){
		return abs(avg.dist(subRoot->avg)) <= tol;
	}
	else {
		// recursive step
		return isInTol(subRoot->LT, tol, avg) && isInTol(subRoot->RB, tol, avg);
	}

}

// A subtree is pruned (cleared) if all of the subtree's leaves are within
// tol of the average color stored in the root of the subtree.
void twoDtree::prune_helper(Node *subRoot, double tol){

	if(subRoot == nullptr){
		return;
	}
	
	if(subRoot->LT == nullptr || subRoot->RB == nullptr){
		return;
	}
	
	if (isInTol(subRoot->LT, tol, subRoot->avg) && isInTol(subRoot->RB, tol, subRoot->avg)){

		clear_helper(subRoot->LT);
		clear_helper(subRoot->RB);
		
	} else {
		prune_helper(subRoot->LT, tol);
		prune_helper(subRoot->RB, tol);
	}

}


void twoDtree::prune(double tol){

	prune_helper(root, tol);

}

void twoDtree::clear_helper(Node *&subRoot) {

	if(subRoot == nullptr){
		return;
	}

	if(subRoot->LT != nullptr){
		clear_helper(subRoot->LT);
	}
	
	if(subRoot->RB != nullptr){
		clear_helper(subRoot->RB);
	}

	delete subRoot;
	subRoot = nullptr;
	
}

/* helper function for destructor and op= */
/* frees dynamic memory associated w the twoDtree */
void twoDtree::clear() {
	clear_helper(root);
	width = 0;
	height = 0;
}

twoDtree::Node * twoDtree::copy_helper(Node *subRoot) {

	Node *newNode = new Node(subRoot->upLeft, subRoot->lowRight, subRoot->avg);

	if(subRoot->LT != nullptr){
		newNode->LT = copy_helper(subRoot->LT);
	}

	if(subRoot->RB != nullptr){
		newNode->RB = copy_helper(subRoot->RB);
	}

	return newNode;

}

/* helper function for copy constructor and op= */
void twoDtree::copy(const twoDtree & orig){
	Node *rootNodePointer = orig.root;
	root = copy_helper(rootNodePointer);
	width = orig.width;
	height = orig.height;
}