#ifndef VARIABLE_H
#define VARIABLE_H

/* this class defines a variable which has a value.  The equality
 * check checks the identifier.  The hash function is based on
 * the identifier.  The value of the variable may be obtained and
 * set.  By default, the value is 0.
*/

#include <string>
#include <iostream>
using namespace std;

class Variable {

    public:
        Variable();
            // empty variable with empty string for id, 0 for
            // value

        Variable(const string &id, float val);
            // constructs variable with given id and value

        Variable(const string &id);
            // constructs variable with given id and value of 0

        float getValue() const;
            // returns value of variable

        void setValue(float newValue);
            // sets value to specified new value

        void output(ostream &s) const;
            // outputs variable id and value to stream

        int hash(int n) const;
            // returns hash index from 0 to n-1 inclusive.  Based
            // on id.

        bool operator == (const Variable &v) const;
        bool operator != (const Variable &v) const;
            // equality operators based on id

    private:

        string myId;
        float myValue;
};

ostream & operator << (ostream &s, const Variable &v);
    // outputs variable id and value to stream

#endif
