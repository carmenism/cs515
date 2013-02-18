/**
 * Carmen St. Jean - CS 515, Assignment 8
 * November 11, 2009
 */

#include <stdlib.h>
#include <ctype.h>
#include <iostream>
#include <fstream>
#include <string>
#include "InsertOrderIntList.h"
#include "Index.h"
using namespace std;

   // constants
   const char pipeChar = '|';

   const int lineLength = 1024;

int main(int argc, const char *argv[])
{
   ifstream infile;
   char line[lineLength];
   int lineNumber = 0;
   Index * index = new Index;

   if (argc == 1)
   {
      cerr <<"\nNo command filename given.\n";
      exit(1);
   }
   else if (argc > 2)
   {
      cerr << "\nToo many command line arguments given.\n";
      exit(1);
   }

   infile.open(argv[1]);

   if (!infile)
   {
      cerr << "\nCannot open [" << argv[1] << "] for input\n";
      exit(1);
   }

   while (infile.getline(line, lineLength))
   {
      lineNumber++;

      string s(line);
      string str = "";
      bool forIndex = false;

      if (lineNumber < 10)
         cout << lineNumber << ":  ";
      else
         cout << lineNumber << ": ";

      for (int i = 0; i < s.size(); i++)
      {
         if (s[i] == pipeChar && !forIndex)
         {
            forIndex = true;
         }
         else if (s[i] == pipeChar && forIndex)
         {
            forIndex = false;
            (*index).insert(str, lineNumber);
            str = "";
         }
         else if (forIndex)
         {
            cout << s[i];
            str += tolower(s[i]);
         }
         else
         {
            cout << s[i];
         }
      }

      cout << "\n";
   }

   infile.close();

   if (lineNumber == 0)
   {
      cout << "File was empty.\n";
   }
   else
   {
      cout << "\n\nINDEX\n-----\n\n";

      if ((*index).empty())
         cout << "Nothing was indexed.\n";
      else
         cout << (*index);
   }

   delete index;

   cout << "\nexit\n";

   return 0;
}