/* this class defines a phone call record.  It consists of the
 * number called from, the number called, and the duration of the
 * call.  Phone numbers may be input, output, compared for
 * equality, the duration obtained, and be tested to determine if
 * local, instate, or out of state.
 */

#include "Call.h"

   // inputs call in order
   //   fromNumber toNumber duration
   // where the numbers are in standard form
   void Call::input(istream &s)
   {
      s >> fromNumber >> toNumber >> duration;
   }

   // outputs in same order input
   void Call::output(ostream &s) const
   {
      s << fromNumber << " " << toNumber << " ";
      s << duration << '\n';
   }

   // returns originating phone number
   const PhoneNumber & Call::getFromNumber() const
   {
      return fromNumber;
   }

   // returns duration of call
   const int Call::getDuration() const
   {
      return duration;
   }

   // predicates, based on from and to numbers
   bool Call::isLocalCall() const
   {
      return (fromNumber.sameExchange(toNumber));
   }

   bool Call::isInStateCall() const
   {
      return (fromNumber.sameState(toNumber));
   }

   bool Call::isOutOfStateCall() const
   {
      return !(fromNumber.sameState(toNumber));
   }

// input call in order specified above
istream & operator >> (istream & s, Call &v)
{
   v.input(s);
   return s;
}

// outputs call in order input
ostream & operator << (ostream &s, const Call &v)
{
   v.output(s);
   return s;
}

