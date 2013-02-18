/*
 * program5a.C
 *
 * Carmen St. Jean
 * CS 515, Assignment 5A
 * October 21, 2009
 * 
 * Assignment 5 in general uses stacks to analyse
 * parentheses of different kinds in a document:
 *      Normal: ( )
 *      Square: [ ]
 *      Curly:  { }
 * The program searches for matches and reports
 * them.  Otherwise, it indicates a closing or
 * opening parenthesis has no provided match.
 *
 * When a parenthesis is printed, its position,
 * which is specified by line number and character
 * number, is also printed.
 *
 * ---------------------------------------------
 *
 * Assignment 5A uses dynamically allocated
 * chains of elements to implement the stack.
 * 
 */

#include <iostream>
#include <string>
#include "Stack.h"
using namespace std;

int main()
{
   Stack * stack = new Stack;
   Parenthesis * open = new Parenthesis;
   Parenthesis * close = new Parenthesis;
   string s;
   int line = 1;

   while (getline(cin, s, '\n'))
   {
      int length = s.length();
      for (int i = 0; i < length; i++)
      {      
         char temp = s[i];
         if (Parenthesis::isOpenParen(temp))
         {
            open = new Parenthesis(temp, line, i+1);
            (*stack).push(*open);
         }
         else if (Parenthesis::isCloseParen(temp))
         {
            close = new Parenthesis(temp, line, i+1);
            Parenthesis m;
            if (!(*stack).empty())
            {
               m = (*stack).top();
               if (m.match(*close))
               {
                  cout << "open " << m << " matched by ";
                  cout << (*close) << "\n";
                  (*stack).pop();
               }
               else
               {
                  cout << "no open for " << (*close);
                  cout << " possible is " << m << "\n";
               }
            }
         }
      }
      line++;
   }

   while (!(*stack).empty())
   {
      Parenthesis m = (*stack).top();
      cout << "no close parenthesis for " << m << "\n";
      (*stack).pop();
   }

   delete close;
   delete open;
   delete stack;

   return 0;
}





