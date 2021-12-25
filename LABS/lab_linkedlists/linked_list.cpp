// linked_list.cc -- functions for linked_list lab (cs221) 

#include "linked_list.h"

/**
 * Inserts a new Node (with key=newKey) at the head of the linked_list.
 * PRE: head is the first node in a linked_list (if NULL, linked_list is empty) 
 * PRE: newKey is the value for the key in the new Node 
 * POST: the new Node is now the head of the linked_list
 */ 
void insert(Node*& head, int newKey) {
  Node * curr = new Node;
  curr->key  = newKey;
  curr->next = head;

  head = curr;
}

/**
 * Print the keys of a linked_list in order, from head to tail 
 * PRE: head is the first node in a linked_list (if NULL, linked_list is empty) 
 */ 
void print(Node* head) {
  std::cout << "[";
  for (Node* curr = head; curr != NULL; curr = curr->next){ 
    std::cout << curr->key;
    if (curr->next != NULL) std::cout << ", ";
  }
  std::cout << "]" << std::endl;
}

/** 
 * Returns the size (number of Nodes) of the linked_list  
 * PRE: head is the first node in a linked_list (if NULL, linked_list is empty) 
 */ 
int size(Node* head){ 
  if (! head) return 0; 
  return 1 + size(head->next); 
}

/**
 * Copies the keys in a linked list to a vector.
 * PRE: head is the first node in a linked_list (if NULL, linked_list is empty) 
 * POST: a new vector<int> containing the keys in the correct order has been returned.  
 */ 
std::vector<int> to_vector(Node* head) {
  std::vector<int> result;
  for (Node* curr = head; curr != NULL; curr = curr->next){ 
    result.push_back(curr->key); 
  }
  return result; 
}

/** 
 * Delete the last Node in the linked_list
 * PRE: head is the first Node in a linked_list (if NULL, linked_list is empty) 
 * POST: the last Node of the linked_list has been removed
 * POST: if the linked_list is now empty, head has been changed
 * POST: else head remains the first Node in the linked_list
 */
void delete_last_element(Node*& head){
  // ******** WRITE YOUR CODE HERE ********
  Node* curr = head;

  if (curr == NULL) {                 // list with 0 elements
    return;
  } else if (curr->next == NULL) {    // list with 1 element
    delete head;
    head = NULL;
    return;
  }

  while (curr->next->next != NULL){   // iterate until we reach the element before last
    curr = curr->next;
  }

  if (curr->next->next == NULL) {     // curr points to the element before last
    Node* beforeLast = curr;          // beforeLast points to the element before last
    curr = curr->next;                // curr is now pointing to the last element
    
    beforeLast->next = NULL;
    delete curr;
    curr = NULL;
  }

}

/**
 * Removes an existing Node (with key=oldKey) from the linked_list. 
 * PRE: head is the first node in a linked_list (if NULL, linked_list is empty) 
 * PRE: oldKey is the value of the key in the Node to be removed 
 * PRE: if no Node with key=oldKey exists, the linked_list has not changed 
 * POST: if a Node with key=oldKey was found, then it was deleted
 * POST: other Nodes with key=oldKey might still be in the linked_list
 * POST: head is the new first Node of the linked_list, if updated
 */ 
void remove(Node*& head, int oldKey) {
  // ******** WRITE YOUR CODE HERE ********
  Node* curr = head;

  if (curr == NULL) {                 // list with 0 elements
    return;
  } else if (curr->key == oldKey) {   // head is the oldKey
    if (curr->next != NULL) {         // list has more elements after head
      Node* currNode = curr;
      curr = curr->next;
      head = curr;                    // assign the second element as head
      delete currNode;
      currNode = NULL;
      return;
    } else {                          // list has no elements after head which is oldKey
      delete curr;
      curr = NULL;
      head = NULL;                    // delete head
      return;
    }
  }

  while (curr->next != NULL) {        // go until the element before last

    if (curr->next->key == oldKey) {
      Node* toDelete = curr->next;
      if (toDelete->next == NULL) {   // if the element we are going to delete is the second last element
        curr->next = NULL;
        delete toDelete;
        toDelete = NULL;
        return;
      }
      curr->next = toDelete->next;
      delete toDelete;
      toDelete = NULL;
    }

    curr = curr->next;
  }

  if (curr->next == NULL) {       // now check the last element
    if (curr->key == oldKey) {
      delete_last_element(head);
    }
    return;
  }

}

/**
 * Insert a new Node (with key=newKey) after an existing Node (with key=oldKey)
 * If there is no existing Node with key=oldKey, then no action.
 * PRE: head is the first Node in a linked_list (if NULL, linked_list is empty) 
 * PRE: oldKey is the value to look for (in the key of an existing Node)  
 * PRE: newKey is the value of the key in the new Node (that might be inserted) 
 * POST: if no Node with key=oldKey was found, then the linked_list has not changed
 * POST: else a new Node (with key=newKey) is right after the Node with key = oldKey.
 */
void insert_after(Node* head, int oldKey, int newKey){
  // ******** WRITE YOUR CODE HERE ********
  Node* curr = head;
  Node* newNode = new Node;
  newNode->key = newKey;
  newNode->next = NULL;

  if (curr == NULL) {                   // list with 0 elements
    return;
  } else if (curr->next == NULL) {      // list with 1 element
    if (curr->key == oldKey) {
      curr->next = newNode;
    }
    return;
  }

  while (curr != NULL) {
    if (curr->key == oldKey) {
      Node* initialNext = curr->next;
      curr->next = newNode;
      newNode->next = initialNext;
    }

    curr = curr->next;
  }

  return;

}

/** 
 * Create a new linked_list by merging two existing linked_lists. 
 * PRE: list1 is the first Node in a linked_list (if NULL, then it is empty)
 * PRE: list2 is the first Node in another linked_list (if NULL, then it is empty)
 * POST: A new linked_list is returned that contains new Nodes with the keys from 
 * the Nodes in list1 and list2, starting with the key of the first Node of list1, 
 * then the key of the first Node of list2, etc. 
 * When one list is exhausted, the remaining keys come from the other list.
 * For example: [1, 2] and [3, 4, 5] would return [1, 3, 2, 4, 5]
 */
Node* interleave(Node* list1, Node* list2){
  // ******** WRITE YOUR CODE HERE ********

  Node* head = NULL;

  if (list2 == NULL) {      // if list2 is empty
    return list1;
  }

  if (list1 == NULL) {      // if list1 is empty
    return list2;
  }

  Node* curr1 = list1;
  Node* curr2 = list2;

    if (list1 == list2) {    // check if the two lists are the same
    head = list1;        
    int count = size(list1);           
    for (int i = 0; i < count; i++) {
      insert_after(list1, curr1->key, curr1->key);
      curr1 = curr1->next->next;
    }
    return head;
  }

  int count1 = size(list1);
  int count2 = size(list2);
  head = list1;

  //!!!!

  if (count1 >= count2) {

    for(int i = 0; i < count2; i++) {

      Node* curr1next = curr1->next;
      curr1->next = curr2;
      Node* curr2next = curr2->next;
      curr2->next = curr1next;

      if (curr2next->next == NULL){                // if we're at the last element of list2
          curr1next->next = curr2next;
          return head;
      }

      curr1 = curr1next;
      curr2 = curr2next;
    }
    return head;
  } else {

    for(int i = 0; i < count1 - 1; i++) {

      Node* curr1next = curr1->next;
      curr1->next = curr2;
      Node* curr2next = curr2->next;
      curr2->next = curr1next;

      if (curr1next->next == NULL){
        curr1next->next = curr2next;
        return head;
      }

      curr1 = curr1next;
      curr2 = curr2next;
      
    }
    return head;
  }
  
}