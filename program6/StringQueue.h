#ifndef STRINGQUEUE_H
#define STRINGQUEUE_H

/* this class defines a queue of strings.  Values may
    be enqueued to the tail of the queue, and dequeued
    from the front of the queue.  The front value may
    be viewed, and the length of the queue may be 
    determined.  In addition, the queue elements may
    be printed in order */

#include <string>
#include <iostream>
using namespace std;

class StringQueue {

    public:

        // exceptions

            class Underflow{};
            class Overflow{};
            class BadSize{};

        StringQueue(int size = 10) throw(BadSize);
            // constucts empty queue which can hold specified
            // number of string values

        ~StringQueue();
            // destructor

        void enqueue(const string & v) throw(Overflow);
            // inserts value onto queue
            // throws overflow if already full

        void dequeue() throw(Underflow);
            // removes value from queue
            // throws Underflow if empty

        const string & front() const throw(Underflow);
            // returns front value in queue
            // throws Underflow if empty

        bool empty() const;
            // returns true if queue is empty

        int length() const;
            // returns count of elements in queue

        void output(ostream &) const;
            // prints elements of queue in order

    private:
        StringQueue(const StringQueue&); //not implemented
        StringQueue& operator =(const StringQueue&); //not implemented

        // implementation is dynamically allocated "circular
        // array".  Empty slot since no count data member

        static int next(int index, int numElem);
            // returns next index in cycle, given current index
            // and number of elements in array

        int numElem; // number of elements in array
        int head;
        int tail;
        string *store; // for dynamically allocated array
};

ostream& operator <<(ostream&, const StringQueue&);
    // outputs elements of queue in order

#endif
