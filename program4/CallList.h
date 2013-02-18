#ifndef CALLLIST_H
#define CALLLIST_H

/* this class defines an insertion order list of phone calls.
 * Calls * can be inserted (to the tail of the list).  The list
 * (calls) can be printed
*/

#include <iostream>
using namespace std;

#include "Call.h"

class CallList {

    public:

        CallList();
            // constructs empty list

        CallList(const CallList &);
            // copy constructor

        ~CallList();
            // destructor

        CallList & operator = (const CallList &);
            // assignment operator

        void insert(const Call &v);
            // inserts call to tail of list

        void output(ostream &s) const;
            // outputs calls to specified stream

    private:
        struct Elem {
            Call info;
            Elem * next;
        };

        Elem * head;
        Elem * tail;
};

ostream & operator << (ostream & s, const CallList &v);
    // outputs calls to stream

#endif
