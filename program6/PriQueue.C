/*  Carmen St. Jean - CS 515 - for A6, 10-28-09 */

/* this class defines a priority queue of strings.  The
    priority is an integer in the range 1 through 999999.
    Items may be enqueued, dequeued, and
    the length of the queue found.  The queue may be
    tested to see if it is empty.  In addition, all the
    elements of the queue may be printed.  If an item
    with invalid priority is enqueued, an exception is thrown.
    High numbers are higher priority than low numbers.  Only
    a limited number of items may be enqueued at any one priority*/

#include "PriQueue.h"

   // creates empty priority queue
   PriQueue::PriQueue()
   {
      head = new Elem;
      head->priority = highPri + 1;
      head->back = 0;

      Elem * tail = new Elem;
      tail->priority = lowPri - 1;
      tail->next = 0;

      head->next = tail;
      tail->back = head;
   }

   //destructor
   PriQueue::~PriQueue()
   {
      Elem * p;

      while (head)
      {
         p = head;
         head = head->next;
         delete p;
      }

      delete head;
   }

   //inserts value onto queue at specified priority
   // throws BadPriority if priority is out of range,
   // Overflow if queue is filled for that priority
   void PriQueue::enqueue(int pri, string v)
   throw(BadPriority, Overflow)
   {
      if (pri < lowPri || pri > highPri)
      {
         throw BadPriority();
      }

      Elem * p = head->next;

      while (p->priority >= lowPri && p->priority >= pri)
      {
         p = p->next;
      }

      if (p->back->priority == pri)
      {
         try
         {
            p->back->queue.enqueue(v);
         }
         catch(StringQueue::Overflow)
         {
            throw Overflow();
         }
      }
      else
      {
         Elem * ptr = new Elem;
         ptr->priority = pri;
         ptr->queue.enqueue(v);
         ptr->next = p;
         ptr->back = p->back;
         p->back->next = ptr;
         p->back = ptr;
      }
   }

   //removes head value from queue
   // throws Underflow if empty
   void PriQueue::dequeue() throw(Underflow)
   {
      if (empty())
      {
         throw Underflow();
      }
      else
      {
         head->next->queue.dequeue();
         if (head->next->queue.empty())
         {
            Elem * p = head->next;
            head->next = p->next;
            p->next->back = head;
            delete p;
         }
      }
   }

   //returns front value in queue
   // throws underflow if empty
   const string & PriQueue::front() const throw(Underflow)
   {
      if (empty())
      {
         throw Underflow();
      }
      else
      {
         return head->next->queue.front();
      }
   }

   //returns length of queue
   int PriQueue::length() const
   {
      int count = 0;
      Elem * p = head->next;

      while (p->priority >= lowPri)
      {
         count += p->queue.length();
         p = p->next;
      }

      return count;
   }

   //returns true if queue is empty
   bool PriQueue::empty() const
   {
      return (head->next->priority < lowPri);
   }

   //outputs contents of queue, including priorities
   void PriQueue::output(ostream &s) const
   {
      Elem * p = head->next;

      while (p->priority >= lowPri)
      {
         s << "\npriority: " << p->priority;
         s << " ==> " << p->queue;
         p = p->next;
      }
   }

//outputs contents of priority queue, including priorities
ostream& operator << (ostream &s, const PriQueue &obj)
{
   obj.output(s);
   return s;
}


