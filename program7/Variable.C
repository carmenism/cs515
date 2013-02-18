/**
 * Carmen St. Jean - CS 515, Assignment 7
 * November 6, 2009
 */

/* this class defines a variable which has a value.  The equality
 * check checks the identifier.  The hash function is based on
 * the identifier.  The value of the variable may be obtained and
 * set.  By default, the value is 0.
*/

#include "Variable.h"

   // empty variable with empty string for id, 0 for
   // value
   Variable::Variable()
   {
      myId = "";
      myValue = 0;
   }

   // constructs variable with given id and value
   Variable::Variable(const string &id, float val)
   {
      myId = id;
      myValue = val;
   }

   // constructs variable with given id and value of 0
   Variable::Variable(const string &id)
   {
      myId = id;
      myValue = 0;
   }

   // returns value of variable
   float Variable::getValue() const
   {
      return myValue;
   }

   // sets value to specified new value
   void Variable::setValue(float newValue)
   {
      myValue = newValue;
   }

   // outputs variable id and value to stream
   void Variable::output(ostream &s) const
   {
      s << myId << " --> " << myValue;
   }

   // returns hash index from 0 to n-1 inclusive.  Based
   // on id.
   int Variable::hash(int n) const
   {
      int num = myId.size();
      int index = 0;

      for (int i = 0; i < num; i++)
      {
         index += myId[i];
      }

      index = (index + 1) % n;

      if (index < 0)
         return 0;
      else if (index >= n)
         return (n-1);
      else
         return index;
   }

   // equality operators based on id
   bool Variable::operator == (const Variable &v) const
   {
      return (this->myId.compare(v.myId) == 0);
   }

   bool Variable::operator != (const Variable &v) const
   {
      return (this->myId.compare(v.myId) != 0);
   }

// outputs variable id and value to stream
ostream & operator << (ostream &s, const Variable &v)
{
   v.output(s);
   return s;
}
