#ifndef TABLE_H
#define TABLE_H

/* this class defines a table of variables.  Variables may be
 * stored and retrieved.  Variables may be modified while within
 * the table, as long as the id does not change.
*/

#include <iostream>
using namespace std;

#include "Variable.h"

class Table {

    public:
        // exceptions

            class Duplicate{};

        Table(int size = 1000);
            // constructs empty table

        void output(ostream &s) const;
            // outputs variables stored in table to stream

        void insert(const Variable &v) throw(Duplicate);
            // inserts variable into table.  throws exception if
            // already there

         Variable * find(const Variable &v);
            // returns variable found, or null if not found

         const Variable * find(const Variable &v) const;
            // returns variable found, or null if not found

    private:
        int numElem;

        struct Elem {
            Variable info;
            Elem * next;
        };

        Elem **table; // array of head pointers

};

ostream & operator << (ostream &s, const Table &v);
    // outputs variables stored in table to stream

#endif
