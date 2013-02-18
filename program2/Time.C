/* this class defines a time measurement which consists of some
 * number of hours, minutes, and seconds.  Times are input
 * (normalized) and output (normalized) in the form
 *        h:mm:ss
 * minutes and seconds will always be input and output
 * as two digits, hours may be input and output as one or more
 * digits.  Times are always non-negative.
 *
 * times may be added and compared.
 *
 * it is assumed that any time input will be normalized (no more
 * than 59 seconds, no more than 59 minutes).  There may be any
 * number of hours.
 *
 * time values will always be non-negative
 */

#include "Time.h"
#include <iostream>

using namespace std;

   // creates a time initialized to 0
   Time::Time()
   {
      hours = 0;
      minutes = 0;
      seconds = 0;
   }

   // creates time initialized to hr:min:sec
   // it is NOT assumed the time is in normalized
   // form
   Time::Time(int hr,int min,int sec)
   {
      seconds = sec % 60;
      minutes = (sec / 60) + (min % 60);
      hours = (sec / 3600) + (min / 60) + hr;
   }

   // inputs next time item from the standard input
   // stream if it exists.  Success fail, returns true
   // if item was read, false if not.  assumes
   // normalized and in correct form
   bool Time::input()
   {
      int hr, min, sec;
      char dummy;

      if (cin >> hr >> dummy >> min >> dummy >> sec)
      {
         seconds = sec % 60;
         minutes = (sec / 60) + (min % 60);
         hours = (sec / 3600) + (min / 60) + hr;
         return true;
      }
      else
         return false;
   }

   // outputs time in form h:mm:ss (normalized) to
   // standard output stream.  There may be more than
   // one hours digit
   void Time::output() const
   {
      cout << hours << ":";

      if (minutes < 10)
         cout << "0" << minutes << ":";
      else
         cout << minutes << ":";

      if (seconds < 10)
         cout << "0" << seconds << " ";
      else
         cout << seconds << " ";
   }

   // adds two time values, returing sum
   Time Time::plus(const Time & t) const
   {
      Time timeSum(hours + t.hours,
                   minutes + t.minutes,
                   seconds + t.seconds);
      return timeSum;
   }

   // greater than operator
   bool Time::gt(const Time & t) const
   {
      int thisTotal = seconds + minutes*60 + hours*3600;
      int tTotal = t.seconds + t.minutes*60 + t.hours*3600;
      if (thisTotal > tTotal)
         return true;
      else
         return false;
   }

   // greater than or equal to operator
   bool Time::ge(const Time & t) const
   {
      int thisTotal = seconds + minutes*60 + hours*3600;
      int tTotal = t.seconds + t.minutes*60 + t.hours*3600;
      if (thisTotal >= tTotal)
         return true;
      else
         return false;
   }

   // less than or equal to operator
   bool Time::le(const Time & t) const
   {
      int thisTotal = seconds + minutes*60 + hours*3600;
      int tTotal = t.seconds + t.minutes*60 + t.hours*3600;
      if (thisTotal <= tTotal)
         return true;
      else
         return false;
   }

   // less than operator
   bool Time::lt(const Time & t) const
   {
      int thisTotal = seconds + minutes*60 + hours*3600;
      int tTotal = t.seconds + t.minutes*60 + t.hours*3600;
      if (thisTotal < tTotal)
         return true;
      else
         return false;
   }

   // equal to operator
   bool Time::eq(const Time & t) const
   {
      int thisTotal = seconds + minutes*60 + hours*3600;
      int tTotal = t.seconds + t.minutes*60 + t.hours*3600;
      if (thisTotal == tTotal)
         return true;
      else
         return false;
   }

   // not equal to operator
   bool Time::ne(const Time & t) const
   {
      int thisTotal = seconds + minutes*60 + hours*3600;
      int tTotal = t.seconds + t.minutes*60 + t.hours*3600;
      if (thisTotal != tTotal)
         return true;
      else
         return false;
   }