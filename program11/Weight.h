#ifndef WEIGHT_H
#define WEIGHT_H

/* this class provides edge weights for a graph.  Weights are
 * reals, which can also be infinite (no edge).  On input, a negative value
 * is taken as infinity.  Weights may be input (with negatives),
 * output (infinity as "inf"), added, and compared.
*/

#include <iostream>
using namespace std;

class Weight {

    public:
        Weight();
            // constructs weight of 0;

        Weight(float);
            // constructs weight corresponding to the real
            // provided.  If the real is negative, the weight
            // will be infinite

        void input(istream &s);
            // inputs weights (reals).  Negative input will be
            // taken as infinite

        void output(ostream &s) const;
            // outputs weights as reals.  Infinity output as
            // "inf"

        Weight operator + (const Weight &v) const;
            // returns weight formed by adding operands

        Weight & operator += (const Weight &v);
            // adds v to left operand, returns left operand

        bool operator < (const Weight &v) const;
        bool operator <= (const Weight &v) const;
        bool operator >= (const Weight &v) const;
        bool operator > (const Weight &v) const;
            // relational operators

        bool operator == (const Weight &v) const;
        bool operator != (const Weight &v) const;
            // equality operators

        static const Weight & infinity();
            // returns weight used for infinity

    private:
        float value;
};

istream & operator >> (istream &s, Weight &v);
    // inputs weight -- invokes keyword input operation

ostream & operator << (ostream &s, const Weight &v);
    // outputs weight -- invokes keyword output operation

#endif
