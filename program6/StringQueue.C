/*  Carmen St. Jean - CS 515 - for A6, 10-28-09 */

/* this class defines a queue of strings.  Values may
    be enqueued to the tail of the queue, and dequeued
    from the front of the queue.  The front value may
    be viewed, and the length of the queue may be
    determined.  In addition, the queue elements may
    be printed in order */

#include "StringQueue.h"

   // constucts empty queue which can hold specified
   // number of string values
   StringQueue::StringQueue(int size) throw(BadSize)
   {
      if (size <= 0)
      {
         throw BadSize();
      }
      else
      {
         numElem = size + 1;
         store = new string[numElem];
         head = 0;
         tail = 0;
      }
   }

   // destructor
   StringQueue::~StringQueue()
   {
      delete [] store;
   }

   // inserts value onto queue
   // throws overflow if already full
   void StringQueue::enqueue(const string & v) throw(Overflow)
   {
      if (head == (tail + 1) % numElem)
      {
         throw Overflow();
      }
      else
      {
         tail = (tail + 1) % numElem;
         store[tail] = v;
      }
   }

   // removes value from queue
   // throws Underflow if empty
   void StringQueue::dequeue() throw(Underflow)
   {
      if (empty())
      {
         throw Underflow();
      }
      else
      {
         head = (head + 1) % numElem;
      }
   }

   // returns front value in queue
   // throws Underflow if empty
   const string & StringQueue::front() const throw(Underflow)
   {
      if (empty())
      {
         throw Underflow();
      }
      else
      {
         return store[(head + 1) % numElem];
      }
   }

   // returns true if queue is empty
   bool StringQueue::empty() const
   {
      return (head == tail);
   }

   // returns count of elements in queue
   int StringQueue::length() const
   {
      if (tail >= head)
      {
         return (tail - head);
      }
      else
      {
         return (numElem - head + tail);
      }
   }

   // prints elements of queue in order
   void StringQueue::output(ostream &s) const
   {
      int tempHead = head;

      for (int i = 0; i < length(); i++)
      {
         s << store[(tempHead + 1 + i) % numElem] << " ";
      }
   }

// outputs elements of queue in order
ostream& operator <<(ostream &s, const StringQueue &v)
{
   v.output(s);
   return s;
}