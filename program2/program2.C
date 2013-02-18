/*
 * program2.C
 *
 * Carmen St. Jean
 * CS 515, Assignment 2
 * September 21, 2009
 *
 * Assignment 2 reads in data about audio tracks
 * from a file.  From a maximum time limit for
 * each recording medium, the program determines
 * the disk and track numbers.  The tracks are
 * laid out in their input order and input
 * terminates when the end of the file is reached.
 *
 * input has the following format:
 * h:mm:ss word1 word2 word3 ... wordn ;
 *
 * The first three values are integers denoting
 * time values, with a colon between them.  The
 * words are the track titles.  The end of a line
 * is denoted by a semicolon.
 */

#include <iostream>
#include "Time.h"

using namespace std;

int main()
{
   Time maxTime;
   if (maxTime.input())
   {
      cout << "\neach recording medium ";
      cout << "has a capacity of ";
      maxTime.output();
      cout << "\n";
   }
   else
   {
      cout << "Error: no max time provided.";
   }

   Time t;
   Time totalTime(0,0,0);
   int disk = 1;
   int track = 1;
   string description;

   while (t.input())
   {
      getline(cin, description, ';');
      Time newTime = totalTime.plus(t);
      if (newTime.le(maxTime) && t.le(maxTime))
      {
         totalTime = newTime;
         if (track == 1)
         {
            cout << "\n\n-----------";
            cout << "------------  ";
            cout << disk;
            cout << "  -------------";
            cout << "----------\n\n";
         }
         cout << track << "       ";
         t.output();
         cout << " " << description << "\n";
         track++;
      }
      else if (t.le(maxTime))
      {
         cout << "total: ";
         totalTime.output();
         totalTime = t;
         track = 1;
         disk++;
         if (track == 1)
         {
            cout << "\n\n-----------";
            cout << "------------  ";
            cout << disk;
            cout << "  -------------";
            cout << "----------\n\n";
         }
         cout << track << "       ";
         t.output();
         cout << " " << description << "\n";
         track++;
      }
      else
      {
         cout << "Error: track exceeds max";
         cout << " time, ignoring track and";
         cout << " continuing with ";
         cout << " remaining data\n";
      }
   }
   cout << "total: ";
   totalTime.output();
   cout << "\n\n";
   return 0;
}
