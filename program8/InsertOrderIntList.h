#ifndef INSERTORDERINTLIST_H
#define INSERTORDERINTLIST_H

#include <iostream>
using namespace std;

class InsertOrderIntList {

    public:

        InsertOrderIntList();
            // constructs empty list

        InsertOrderIntList(const InsertOrderIntList &);
            // copy constructor

        ~InsertOrderIntList();
            // destructor

        InsertOrderIntList & operator = (const InsertOrderIntList &);
            // assignment operator

        void insert(int v);
            // inserts integer in order

        void output(ostream &s) const;
            // outputs list to specified stream

    private:
        struct Elem {
            int info;
            Elem * next;
        };

        Elem * head;
        Elem * tail;
};

ostream & operator << (ostream & s, const InsertOrderIntList &v);
    // outputs calls to stream

#endif
