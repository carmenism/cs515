/* this class defines a three part phone number.  Phone numbers
 * may be input, output, and compared for equality.  Phone
 * numbers may be compared for same state and/or same exchange.
 */

#include "PhoneNumber.h"

   // inputs in form (aaa) eee-nnnn
   void PhoneNumber::input(istream &s)
   {
      char d;   // a dummy character
      s >> d >> areaCode >> d >> exchange >> d >> number;
   }

   // outputs in form input
   void PhoneNumber::output(ostream &s) const
   {
      s << "(" << areaCode << ") " << exchange << "-" << number;
   }

   // equality operators, based on all parts
   bool PhoneNumber::operator == (const PhoneNumber &v) const
   {
      return (sameExchange(v) && number == v.number);
   }

   bool PhoneNumber::operator != (const PhoneNumber &v) const
   {
      return !(sameExchange(v) && number == v.number);
   }

   // returns true if both numbers in same state
   bool PhoneNumber::sameState(const PhoneNumber &v) const
   {
      return (areaCode == v.areaCode);
   }

   // returns true if both numbers in same state and
   // same exchange
   bool PhoneNumber::sameExchange(const PhoneNumber &v) const
   {
      return (sameState(v) && exchange == v.exchange);
   }

// inputs in form specified above
istream & operator >> (istream &s, PhoneNumber &v)
{
   v.input(s);
   return s;
}

// outputs in same form as input
ostream & operator << (ostream &s, const PhoneNumber &v)
{
   v.output(s);
   return s;
}

