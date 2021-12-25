/**
 * @file quackfun.cpp
 * This is where you will implement the required functions for the
 *  stacks and queues portion of the lab.
 */

namespace QuackFun {

    /**
     * Sums items in a stack.
     * @param s A stack holding values to sum.
     * @return The sum of all the elements in the stack, leaving the original
     *  stack in the same state (unchanged).
     *
     * @note You may modify the stack as long as you restore it to its original
     *  values.
     * @note You may use only two local variables of type T in your function.
     *  Note that this function is templatized on the stack's type, so stacks of
     *  objects overloading the + operator can be summed.
     * @note We are using the Standard Template Library (STL) stack in this
     *  problem. Its pop function works a bit differently from the stack we
     *  built. Try searching for "stl stack" to learn how to use it.
     * @hint Think recursively!
     */
    template <typename T>
    T sum(stack<T>& s)
    {
        if (s.empty()){                     // base case
            return 0;
        }

        T *topElement = new T();
        *topElement = s.top();
        s.pop();                             // iterative step - get rid of the top element from the original stack
        T *sumOfPrevS = new T();
        *sumOfPrevS = sum(s);                // recursive step

        s.push(*topElement);                 // get the stack back to its original state
        return *topElement + *sumOfPrevS;
    }

    /**
     * Reverses even sized blocks of items in the queue. Blocks start at size
     * one and increase for each subsequent block.
     * @param q A queue of items to be scrambled
     *
     * @note Any "leftover" numbers should be handled as if their block was
     *  complete.
     * @note We are using the Standard Template Library (STL) queue in this
     *  problem. Its pop function works a bit differently from the stack we
     *  built. Try searching for "stl stack" to learn how to use it.
     * @hint You'll want to make a local stack variable.
     */
    template <typename T>
    void scramble(queue<T>& q)
    {
        //before starting, reverse the queue to make the operations using stack easier

        int originalSize = q.size();
        stack<T> reverseTheQueue;
        T* element = new T();

        // put the queue in a stack
        for(int i = 0; i < originalSize; i++) {
            *element = q.front();
            q.pop();
            reverseTheQueue.push(*element);
        }

        // put the stack back in the queue
        for(int i = 0; i < originalSize; i++) {
            *element = reverseTheQueue.top();
            reverseTheQueue.pop();
            q.push(*element);
        }

        stack<T> originalS;
        stack<T> tempReversedS;
        stack<T> reversedS;

        // empty the original queue and fill originalS in the order that we remove elements
        for(int i = 0; i < originalSize; i++){
            *element = q.front();
            q.pop();
            originalS.push(*element);
        }

        T *curr = new T();
        int reverseOrNot = 0;                   // 0 means dont reverse, 1 means reverse. start from not reversing.
        int grouping = 1;
        int index = 0;

        while(index + grouping < originalSize) {

            if (reverseOrNot == 0){                 // don't reverse
                reverseOrNot++;                     // reverse it the next time

                for(int i = 0; i < grouping; i++) {
                    *curr = originalS.top();
                    originalS.pop();
                    reversedS.push(*curr);
                }

            } else {                                // reverse
                reverseOrNot--;                     // don't reverse it the next time

                for(int i = 0; i < grouping; i++) {
                    *curr = originalS.top();
                    originalS.pop();
                    tempReversedS.push(*curr);
                }
                
                for(int i = 0; i < grouping; i++) {
                    *curr = tempReversedS.top();
                    tempReversedS.pop();
                    reversedS.push(*curr);
                }
            }

            index = index + grouping;
            grouping++;
        }

        int leftoverSize = originalS.size();

        // once we get out of the while loop, there may be an incomplete group at the end

        if (leftoverSize > 0) {   // there is an incomplete group at the end

            if (reverseOrNot == 0){     // dont reverse them

                for(int i = 0; i < leftoverSize; i++){
                    *curr = originalS.top();
                    originalS.pop();
                    reversedS.push(*curr);
                }

            } else {            // reverse them
                
                for(int i = 0; i < leftoverSize; i++) {
                    *curr = originalS.top();
                    originalS.pop();
                    tempReversedS.push(*curr);
                }

                for(int i = 0; i < leftoverSize; i++){
                    *curr = tempReversedS.top();
                    tempReversedS.pop();
                    reversedS.push(*curr);
                }

            }

        } else if (leftoverSize == 0) {
            // do nothing
        } else {
            printf("u fucked up");
        }

        for (int i = 0; i < originalSize; i++){
            *curr = reversedS.top();
            reversedS.pop();
            q.push(*curr);
        }

        // reverse the queue back to original but scrambled

        for(int i = 0; i < originalSize; i++) {
            *element = q.front();
            q.pop();
            reverseTheQueue.push(*element);
        }

        // put the stack back in the queue
        for(int i = 0; i < originalSize; i++) {
            *element = reverseTheQueue.top();
            reverseTheQueue.pop();
            q.push(*element);
        }

        return;
    }

    /**
     * @return true if the parameter stack and queue contain only elements of
     *  exactly the same values in exactly the same order; false, otherwise.
     *
     * @note You may assume the stack and queue contain the same number of items!
     * @note There are restrictions for writing this function.
     * - Your function may not use any loops
     * - In your function you may only declare ONE local boolean variable to use in
     *   your return statement, and you may only declare TWO local variables of
     *   parametrized type T to use however you wish.
     * - No other local variables can be used.
     * - After execution of verifySame, the stack and queue must be unchanged. Be
     *   sure to comment your code VERY well.
     */
    template <typename T>
    bool verifySame(stack<T>& s, queue<T>& q)
    {
        bool retval = true; // optional
        //T temp1; // rename me
        //T temp2; // rename :)

        return retval;
    }
}
