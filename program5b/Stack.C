/*
 * This class defines a stack of parentheses.
 * Parenthesis objects can be pushed and popped.
 * Top will return the value of the top of the stack.
 *
 * This is the implementation to accompany 5B.
 * It uses an array to implement the stack.
 */

#include "Stack.h"

   // constructs empty stack
   Stack::Stack(int m)
   {
      max = m;
      topIndex = -1;
      arr = new Parenthesis[max];
   }
   
   // destructor
   Stack::~Stack()
   {
      delete [] arr;
   }

   // returns true if contains no elements
   bool Stack::empty()
   {
      return (topIndex == -1);
   }
         
   // adds given value to top of stack
   void Stack::push(const Parenthesis &v)
   {
      if (topIndex + 1 == max)
      {
         // full
      }
      else
      {
         topIndex++;
         arr[topIndex] = v;
      }
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
         topIndex--;
      }
   }
         
   // returns top value in the stack (no removal)
   Parenthesis Stack::top()
   {
      return arr[topIndex];
   }


