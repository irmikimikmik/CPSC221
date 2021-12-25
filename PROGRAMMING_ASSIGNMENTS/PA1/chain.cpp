#include "chain.h"
#include "chain_given.cpp"
#include <cmath>
#include <iostream>

// PA1 functions

/**
 * Destroys the current Chain. This function should ensure that
 * memory does not leak on destruction of a chain.
 */
Chain::~Chain()
{
    clear();
    width_ = 0;
    height_ = 0;
    head_ = NULL;
    cout << "The current chain has been destroyed." << endl;
}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
void Chain::insertBack(const Block &ndata)
{
    // create a new pointer newNode that points to the data that should be added
    Node *newNode = new Node(ndata);
    // create a new pointer previousNode that points to the last node before tail
    Node *previousNode = tail_->prev;
    // make newNode's tail point to tail
    newNode->next = tail_;
    // make tail's head point to NewNode
    tail_->prev = newNode;
    // make newNode's head point to the previous node
    newNode->prev = previousNode;
    // make previousNode's tail point to newNode
    previousNode->next = newNode;

    //increase length
    length_++;
}


/**
 * Swaps the two nodes at the indexes "node1" and "node2".
 * The indexes of the nodes are 1 based.
 * assumes i and j are valid (in {1,length_} inclusive)
 * 
 */
void Chain::swap(int i, int j)
{
    Node* iAddress = walk(head_, i);
    Node* jAddress = walk(head_, j);

    Node* iAddressPrev = iAddress->prev;
    Node* jAddressPrev = jAddress->prev;
    Node* iAddressNext = iAddress->next;
    Node* jAddressNext = jAddress->next;

    if (i + 1 == j) {
        iAddressPrev->next = jAddress;
        jAddressNext->prev = iAddress;
        iAddress->prev = jAddress;
        jAddress->next = iAddress;
        iAddress->next = jAddressNext;
        jAddress->prev = iAddressPrev;
    } else {
        iAddress->prev = jAddressPrev;
        iAddress->next = jAddressNext;
        jAddress->prev = iAddressPrev;
        jAddress->next = iAddressNext;
        iAddressPrev->next = jAddress;
        iAddressNext->prev = jAddress;
        jAddressPrev->next = iAddress;
        jAddressNext->prev = iAddress;
    }
}

/**
 * Reverses the chain
 */
void Chain::reverse()
{
    if (length_ == 1) {
        return;
    } else {
        for (int i = 1; i <= floor(length_ / 2); i++) {
            swap(i, (length_ - i + 1));
        }
    }
}

/*
* Modifies the current chain by "rotating" every k nodes by one position.
* In every k node sub-chain, remove the first node, and place it in the last 
* position of the sub-chain. If the last sub-chain has length less than k,
* then don't change it at all. 
* Some examples with the chain a b c d e:
*   k = 1: a b c d e
*   k = 2: b a d c e
*   k = 3: b c a d e
*   k = 4: b c d a e
*/
void Chain::rotate(int k)
{
    int numOfRotations = floor(length_ / k);

    for (int i = 0; i < numOfRotations; i++) {
        for (int j = 1; j < k; j++) {
            swap(j + (k*i), j + (k*i) + 1);
        }
    }
}

/**
 * Destroys all dynamically allocated memory associated with the
 * current Chain class.
 */
void Chain::clear()
{
    // start with the first node
    Node* currentNode = head_->next;
    delete head_;
    // then do the rest of the list until you reach NULL
    while(currentNode != NULL) {
       // first, create a pointer NextNode that points to the next element (so that you don't lose the list)
       Node* nextNode = currentNode->next;
       // delete the node before that (current node)
       delete currentNode;
       // make the currentNode pointer point to the next element
       currentNode = nextNode;
    }

    // reset length
    length_ = 0;
}

/* makes the current object into a copy of the parameter:
 * All member variables should have the same value as
 * those of other, but the memory should be completely
 * independent. This function is used in both the copy
 * constructor and the assignment operator for Chains.
 */
void Chain::copy(Chain const &other)
{
    // set length to 0
    length_ = 0;
    // make height_ equal to new height
    height_ = other.height_;
    // make width_ equal to new width
    width_ = other.width_;
    // create new head
    head_ = new Node();
    // create new tail
    tail_ = new Node();
    // make head point to tail
    head_->next = tail_;
    // make tail point to head
    tail_->prev = head_;

    // create a new pointer otherNode that points to what the head of other is pointing to.
    Node* otherNode = other.head_->next;

    // now copy the rest of the elements in the list
    for(int i = 0; i < other.size() ; i ++) {

        // create a new node that points to what otherNode is pointing to
        Node * newNode = new Node(otherNode->data);
        // create a new node previousNode that points to the last element before tail
        Node * previousNode = tail_->prev;
        // make newNode's next point to the tail
        newNode->next = tail_;
        // make tail's previous point to newNode
        tail_->prev = newNode;
        // make newNode's previous point to previousNode
        newNode->prev = previousNode;
        // make previousNode's next point to newNode
        previousNode->next = newNode;
        // make otherNode point to the next element
        otherNode = otherNode->next;
        // increase length
        length_++;
    }
}

/***********************************
 * swapColumns
 * parameters: 1 <= i <= numCols_
 *              1 <= j <= numCols_
 *
 * Swaps the positions of columns i and j
 * in the original grid of blocks by
 * moving nodes in the chain.
 *
 ***********************************/

void Chain::swapColumns(int i, int j) {

    for (int x = 0; x < numRows_; x++) {
        swap(i + (numCols_*x), j + (numCols_*x));
    }
}

/***********************************
 * swapRows
 * parameters: 1 <= i <= numRows_
 *              1 <= j <= numRows_
 *
 * Swaps the positions of rows i and j
 * in the original grid of blocks by
 * moving nodes in the chain.
 *
 ***********************************/
void Chain::swapRows(int i, int j) {

    int initiali = ((i-1)*numCols_) + 1;
    int initialj = ((j-1)*numCols_) + 1;
    
    for (int x = 0; x < numCols_; x++) {
        swap(initiali, initialj);
        initiali++;
        initialj++;
    }
}