#ifndef STACK_H
#define STACK_H

/*
 * This class defines a stack of parentheses.
 * Parenthesis objects can be pushed and popped.
 * Top will return the value of the top of the stack.
 *
 * This is the implementation to accompany 5A.
 * It uses a dynamically allocated chain of elements
 * to implement the stack.
 */

#include <iostream>
using namespace std;

#include "Parenthesis.h"

class Stack {

    public:

        Stack();
            // constructs empty stack

        ~Stack();
            // destructor

        bool empty();
            // returns true if contains no elements

        void push(const Parenthesis &v);
            // adds given value to top of stack

        void pop();
            // removes top value from the stack

        Parenthesis top();
            // returns top value in the stack (no removal)

//        void output(ostream &s) const;
            // outputs calls to specified stream

    private:
        struct Elem {
            Parenthesis info;
            Elem * next;
        };

        Elem * head;

        Stack(const Stack &);
            // copy constructor, not implemented

        Stack & operator = (const Stack &v);
            // assignment operator, not implemented
};

//ostream & operator << (ostream & s, const Stack &v);
    // outputs calls to stream

#endif
