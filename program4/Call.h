#ifndef CALL_H
#define CALL_H

/* this class defines a phone call record.  It consists of the
 * number called from, the number called, and the duration of the
 * call.  Phone numbers may be input, output, compared for
 * equality, the duration obtained, and be tested to determine if
 * local, instate, or out of state.
*/

#include <iostream>
using namespace std;

#include "PhoneNumber.h"

class Call {

    public:
        
        void input(istream &s);
            // inputs call in order
            //   fromNumber toNumber duration
            // where the numbers are in standard form

        void output(ostream &s) const;
            // outputs in same order input

        const PhoneNumber & getFromNumber() const;
            // returns originating phone number

        const int getDuration() const;
            // returns duration of call

        bool isLocalCall() const;
        bool isInStateCall() const;
        bool isOutOfStateCall() const;
            // predicates, based on from and to numbers


    private:
        PhoneNumber fromNumber;
        PhoneNumber toNumber;
        int duration;

};

istream & operator >> (istream & s, Call &v);
   // input call in order specified above 

ostream & operator << (ostream &s, const Call &v);
    // outputs call in order input

#endif
