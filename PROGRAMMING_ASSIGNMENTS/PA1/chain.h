
/**
 * (PA 1)
 * null terminated doubly linked list 
 * with sentinels 
 *
 */

#ifndef _CHAIN_H_
#define _CHAIN_H_

#include <algorithm>
#include <iostream>
#include "block.h"
using namespace std;

/**
 * Chain: This is a container class for blocks. It is implemented
 * as a linked list of nodes, each of which contains a block.
 *
 * You should not remove anything from this class definition, but
 * you may find it helpful to add your own private helper functions to it.
 */

class Chain
{
private:
   /**
    * The Node class is private to the List class via the principle of
    * encapsulation---the end user does not need to know our node-based
    * implementation details.
    */
   class Node
   {
   public:
      Node();                   // default constructor--GIVEN
      Node(const Block &ndata); // data provided constructor--GIVEN

      Node *next;       // ptr to next node in chain, tail->next NULL 
      Node *prev;       // ptr to prev node in chain, head->prev NULL 

      const Block data; // data held by Node. const for this PA.
   };

public:
   Chain();
   Chain(PNG &imIn, int cols, int rows);
   Chain(const Chain &other);

   Chain &operator=(const Chain &rhs);

   int size() const;
   bool empty() const;
   PNG render(int cols, int rows);
   PNG renderBack(int cols, int rows);

   /* =============== end of given functions ====================*/

   /* =============== public PA1 FUNCTIONS =========================*/

   ~Chain();
   void insertBack(const Block &ndata);
   void reverse();
   void rotate(int k);
   void swap(int i, int j); 
   void swapRows(int i, int j);
   void swapColumns(int i, int j);

   /* =============== end of public PA1 FUNCTIONS =========================*/

private:
   /*
    * Private member variables.
    *
    * You must use these as specified in the spec and may not rename them.
    * You may add more if you need them.
    */

   Node *head_; // ptr to sentinel (non-data) node at front of chain
   Node *tail_; // ptr to sentinel (non-data) node at rear of chain

   int length_; // count of data elts in chain. 
   int numRows_; // number of rows of blocks 
   int numCols_; // number of columns of blocks 
                

   int height_; // height of all blocks in chain.(must be consistent.)
   int width_;  // width of all blocks in chain. (must be consistent.)


   /*
    * Private helper functions.
    *
    * You may place functions here as you need them.
    */


   /* =================== private given functions ============== */

   /* Returns a pointer to the node in the kth position of the list,
    * beyond curr. It effectively walks forward k steps from curr.
    * You may use this function in your solutions
    * to the PA1 functions. GIVEN in chain_given.cpp.
    */
   Node *walk(Node *curr, int k);

   /* =================== end of private given functions ============== */

   /* =================== private PA1 functions ============== */

   /**
    * Destroys all dynamically allocated memory associated with the
    * current Chain class (including sentinels). Called by destructor
    * and op=. Complete for PA1.
    */
   void clear();

   /**
   * Copies the parameter other Chain into the current Chain.
   * Does not free any memory. Called by copy constructor and op=.
   * Complete for PA1.
   * @param other The Chain to be copied.
   */
   void copy(const Chain &other);


   /* =================== end of private PA1 functions ============== */
};

#endif
