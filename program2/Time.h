#ifndef TIME_H
#define TIME_H

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

class Time {

    public:
        Time();
            // creates a time initialized to 0

        Time(int hr,int min,int sec);
            // creates time initialized to hr:min:sec
            // it is NOT assumed the time is in normalized
            // form

        bool input();
            // inputs next time item from the standard input
            // stream if it exists.  Success fail, returns true
            // if item was read, false if not.  assumes
            // normalized and in correct form

        void output() const;
            // outputs time in form h:mm:ss (normalized) to
            // standard output stream.  There may be more than
            // one hours digit

        Time plus(const Time &) const;
            // adds two time values, returing sum

         bool gt(const Time &) const;
         bool ge(const Time &) const;
         bool le(const Time &) const;
         bool lt(const Time &) const;
         bool eq(const Time &) const;
         bool ne(const Time &) const;
            // relational and equality operators

    private:
        int hours;
        int minutes;
        int seconds;
};

#endif
