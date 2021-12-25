/**
 * @file queue.cpp
 * Implementation of the Queue class.
 *
 */

/**
 * Adds the parameter object to the back of the Queue.
 *
 * @param newItem object to be added to the Queue.
 */
template <class T>
void Queue<T>::enqueue(T const& newItem)
{
    inStack.push(newItem);
}

/**
 * Removes the object at the front of the Queue, and returns it to the
 * caller.
 *
 * @return The item that used to be at the front of the Queue.
 */
template <class T>
T Queue<T>::dequeue()
{
    // reverse the instack and store it in outstack so that the first one in the queue can go out first
    // this empties inStack
    // this fills outStack
    while (!inStack.isEmpty()){
        outStack.push(inStack.pop());
    }
    
    // remove the last element of outStack which is the first element of the inStack
    T removedElement = outStack.pop();

    // reverse the outstack and store it in instack
    // this fills the instack back with the first element missing
    // this empties outStack
    while (!outStack.isEmpty()){
        inStack.push(outStack.pop());
    }

    return removedElement;

}

/**
 * Adds an element to the ordering structure.
 *
 * @see OrderingStructure::add()
 */
template <class T>
void Queue<T>::add(const T& theItem)
{
    enqueue(theItem);
}

/**
 * Removes an element from the ordering structure.
 *
 * @see OrderingStructure::remove()
 */
template <class T>
T Queue<T>::remove()
{
    return dequeue();
}

/**
 * Finds the object at the front of the Queue, and returns it to the
 * caller. Unlike pop(), this operation does not alter the queue.
 *
 * @return The item at the front of the queue.
 */
template <class T>
T Queue<T>::peek()
{
    // reverse the instack and store it in outstack so that the first one in the queue can go at the top of the stack
    // this empties inStack
    // this fills outStack
    while (!inStack.isEmpty()){
        outStack.push(inStack.pop());
    }
    
    // peek at the last element of outStack which is the first element of the inStack
    T firstElement = outStack.peek();

    // reverse the outstack and store it in instack
    // this fills the instack back with the first element missing
    // this empties outStack
    while (!outStack.isEmpty()){
        inStack.push(outStack.pop());
    }

    return firstElement;
}

/**
 * Determines if the Queue is empty.
 *
 * @return bool which is true if the Queue is empty, false otherwise.
 */
template <class T>
bool Queue<T>::isEmpty() const
{
    return inStack.isEmpty();

}
