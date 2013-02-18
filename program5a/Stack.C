/*
 * This class defines a stack of parentheses.
 * Parenthesis objects can be pushed and popped.
 * Top will return the value of the top of the stack.
 *
 * This is the implementation to accompany 5A.
 * It uses a dynamically allocated chain of elements
 * to implement the stack.
 */

#include "Stack.h"

   // constructs empty stack
   Stack::Stack()
   {
      head = 0;
   }
   
   // destructor
   Stack::~Stack()
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

   // returns true if contains no elements
   bool Stack::empty()
   {
      return (head == 0);
   }
         
   // adds given value to top of stack
   void Stack::push(const Parenthesis &v)
   {
      Elem * p = new Elem;
      p->info = v;
      p->next = head;
      head = p;
   }
         
   // removes top value from the stack
   void Stack::pop()
   {
      if (empty())
      {
         // error
      }
      else
      {
         Elem * p = head;
         head = head->next;
         delete p;
      }
   }
         
   // returns top value in the stack (no removal)
   Parenthesis Stack::top()
   {
      return head->info;
   }


