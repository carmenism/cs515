/* Carmen St. Jean - CS 515, A11, December 10, 2009 */

/* this class provides edge weights for a graph.  Weights are
 * reals, which can also be infinite (no edge).  On input, a negative value
 * is taken as infinity.  Weights may be input (with negatives),
 * output (infinity as "inf"), added, and compared.
*/

#include "Weight.h"

   // constructs weight of 0;
   Weight::Weight()
   {
      value = 0;
   }

   // constructs weight corresponding to the real
   // provided.  If the real is negative, the weight
   // will be infinite
   Weight::Weight(float v)
   {
      value = v;
   }

   // inputs weights (reals).  Negative input will be
   // taken as infinite
   void Weight::input(istream &s)
   {
      s >> value;

      if (value < 0)
         value = (0xFFL << 23);
   }

   // outputs weights as reals.  Infinity output as
   // "inf"
   void Weight::output(ostream &s) const
   {
      s.width(7);
      if (value == (0xFFL << 23))
         s << left << "inf";
      else
         s << left << value;
   }

   // returns weight formed by adding operands
   Weight Weight::operator + (const Weight &v) const
   {
      if (v == infinity() || (*this) == infinity())
         return infinity();

      Weight w(value + v.value);

      return w;
   }

   // adds v to left operand, returns left operand
   Weight & Weight::operator += (const Weight &v)
   {
      if (v == infinity() || (*this) == infinity())
      {
         Weight * w = new Weight(-1);
         return *w;
      }

      value += v.value;

      return (*this);
   }

   // relational operators
   bool Weight::operator < (const Weight &v) const
   {
      if (v == infinity() && (*this) != infinity())
         return true;
      else if (v == infinity() && (*this) == infinity())
         return false;
      else if ((*this) == infinity())
         return false;
      else
         return (value < v.value);
   }

   bool Weight::operator <= (const Weight &v) const
   {
      if (v == infinity())
         return true;
      else if ((*this) == infinity())
         return false;
      else
         return (value <= v.value);
   }

   bool Weight::operator >= (const Weight &v) const
   {
      if ((*this) == infinity())
         return true;
      else if (v == infinity())
         return false;
      else
         return (value >= v.value);
   }

   bool Weight::operator > (const Weight &v) const
   {
      if (v == infinity() && (*this) != infinity())
         return false;
      else if (v == infinity() && (*this) == infinity())
         return false;
      else if ((*this) == infinity())
         return true;
      else
         return (value > v.value);
   }

   // equality operators
   bool Weight::operator == (const Weight &v) const
   {
      return (value == v.value);
   }

   bool Weight::operator != (const Weight &v) const
   {
      return (value != v.value);
   }

   // returns weight used for infinity
   const Weight & Weight::infinity()
   {
     static Weight w(-1);
     return w;
   }

// inputs weight -- invokes keyword input operation
istream & operator >> (istream &s, Weight &v)
{
   v.input(s);
   return s;
}

// outputs weight -- invokes keyword output operation
ostream & operator << (ostream &s, const Weight &v)
{
   v.output(s);
   return s;
}