/**
 * Carmen St. Jean - CS 515, Assignment 7
 * November 6, 2009
 */

/* this class defines a stack of floats for procedural
    design.  floats may be pushed, popped, and topped.
    and the stack may be tested for empty.
*/

#include "NumStack.h"
#include <new>
using namespace std;

   //constructs an empty stack
   NumStack::NumStack()
   {
      topPointer = 0;
   }

   //copy constructor
   NumStack::NumStack(const NumStack &v)
   {
      if (v.empty())
      {
         topPointer = 0;
      }
      else
      {
         topPointer = new Element;
         topPointer->info = v.topPointer->info;
         Element * p1 = topPointer;
         Element * p2 = v.topPointer->next;

         while (p2)
         {
            p1->next = new Element;
            p1 = p1->next;
            p1->info = p2->info;
            p2 = p2->next;
         }

         p1->next = 0;
      }
   }

   //destructor
   NumStack::~NumStack()
   {
      Element * p;

      while (topPointer)
      {
         p = topPointer;
         topPointer = topPointer->next;
         delete p;
      }
   }

   //assignment operator
   NumStack& NumStack::operator =(const NumStack &v)
   {
      if (this != &v)
      {
         // destructor code
         Element * p;

         while (topPointer)
         {
            p = topPointer;
            topPointer = topPointer->next;
            delete p;
         }

         // copy code
         if (v.empty())
         {
            topPointer = 0;
         }
         else
         {
            topPointer = new Element;
            topPointer->info = v.topPointer->info;
            Element * p1 = topPointer;
            Element * p2 = v.topPointer->next;

            while (p2)
            {
               p1->next = new Element;
               p1 = p1->next;
               p1->info = p2->info;
               p2 = p2->next;
            }

            p1->next = 0;
         }
      }

      return *this;
   }

   //modifies stack by inserting v as new top
   //element
   void NumStack::push(float v) throw(Overflow)
   {
      try
      {
         Element * p = new Element;
         p->info = v;
         p->next = topPointer;
         topPointer = p;
      }
      catch (bad_alloc)
      {
         throw Overflow();
      }
   }

   //modifies stack by removing top element
   void NumStack::pop() throw(Underflow)
   {
      if (empty())
      {
         throw Underflow();
      }
      else
      {
         Element * p = topPointer;
         topPointer = topPointer->next;
         delete p;
      }
   }

   //returns value stored in top element
   float NumStack::top() const throw(Underflow)
   {
      if (empty())
      {
         throw Underflow();
      }
      else
      {
         return topPointer->info;
      }
   }

   //returns true if stack contains no elements
   bool NumStack::empty() const
   {
      return (topPointer == 0);
   }
