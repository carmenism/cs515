#ifndef PHONENUMBER_H
#define PHONENUMBER_H

/* this class defines a three part phone number.  Phone numbers
 * may be input, output, and compared for equality.  Phone
 * numbers may be compared for same state and/or same exchange.
*/

#include <iostream>
using namespace std;

class PhoneNumber {
    
    public:

        void input(istream &s);
            // inputs in form (aaa) eee-nnnn

        void output(ostream &s) const;
            // outputs in form input

        bool operator == (const PhoneNumber &v) const;
        bool operator != (const PhoneNumber &v) const;
            // equality operators, based on all parts

        bool sameState(const PhoneNumber &v) const;
            // returns true if both numbers in same state

        bool sameExchange(const PhoneNumber &v) const;
            // returns true if both numbers in same state and
            // same exchange

    private:
        int areaCode;
        int exchange;
        int number;
};

istream & operator >> (istream &s, PhoneNumber &v);
    // inputs in form specified above

ostream & operator << (ostream &s, const PhoneNumber &v);
    // outputs in same form as input

#endif
