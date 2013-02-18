#ifndef PRIQUEUE_H
#define PRIQUEUE_H

/* this class defines a priority queue of strings.  The
    priority is an integer in the range 1 through 999999.
    Items may be enqueued, dequeued, and
    the length of the queue found.  The queue may be
    tested to see if it is empty.  In addition, all the
    elements of the queue may be printed.  If an item
    with invalid priority is enqueued, an exception is thrown.
    High numbers are higher priority than low numbers.  Only
    a limited number of items may be enqueued at any one priority*/

#include <string>
#include <iostream>
using namespace std;
#include "StringQueue.h"

class PriQueue {

    public:

        // exceptions

            class Overflow{};
            class Underflow{};
            class BadPriority{};

        PriQueue();
            // creates empty priority queue

        ~PriQueue();
            //destructor

        void enqueue(int pri, string v)
            throw(BadPriority, Overflow);
            //inserts value onto queue at specified priority
            // throws BadPriority if priority is out of range,
            // Overflow if queue is filled for that priority

        void dequeue() throw(Underflow);
            //removes head value from queue 
            // throws Underflow if empty

        const string & front() const throw(Underflow);
            //returns front value in queue
            // throws underflow if empty

        int length() const;
            //returns length of queue

        bool empty() const;
            //returns true if queue is empty

        void output(ostream&) const;
            //outputs contents of queue, including priorities

    private:

        PriQueue(const PriQueue&);  //copy constructor - not implemented
        PriQueue& operator =(const PriQueue&);  //assignment - not implemented

        static const int lowPri = 1;
        static const int highPri = 999999;

        // implementation is a doubly linked chain of queues,
        // with both head and tail sentinels.  Note: normally a
        // count data member would have been provided to inprove
        // efficiency of empty and length operations.  It was NOT
        // PROVIDED to give you more practice at manipulating the
        // chain of elements.

        struct Elem {
            int priority;
            StringQueue queue;
            Elem * next;
            Elem * back;
        };

        Elem * head;
};

    ostream& operator << (ostream&, const PriQueue &obj);
        //outputs contents of priority queue, including priorities

#endif
