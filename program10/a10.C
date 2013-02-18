/**
 * Carmen St. Jean - CS 515, Assignment 8
 * November 11, 2009
 */

#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
#include "StringBag.h"

int main(int argc, const char *argv[])
{
   if (argc == 1)
   {
      cerr <<"\nno filename(s) given";
      exit(1);
   }

   int fileNumber = 1;

   while (fileNumber < argc)
   {
      ifstream infile;

      infile.open(argv[fileNumber]);

      if (!infile)
      {
         cerr << "\ncannot open [" << argv[fileNumber] << "] for input";
      }
      else
      {
         cerr << "\nopened file [" << argv[fileNumber] << "]";
      }

      infile.close();

      fileNumber++;
   }

   cout << "\n";

   StringBag strbag;

   strbag.insert("231454");
   strbag.insert("435234");
   strbag.insert("first1");

   strbag.insert("2togo");
   strbag.insert("first1");
   strbag.insert("54443y");

   strbag.insert("yy3245");
   strbag.insert("first1");
   strbag.insert("435234");

   strbag.insert("unix1");
   strbag.insert("kj&cj");
   strbag.insert("435234");

   strbag.insert("2togo");

   strbag.insert("oops");
   strbag.insert("first1");

   strbag.insert("yy3245");
   strbag.insert("r2d2");
   strbag.insert("robby");

   strbag.insert("unix1"); strbag.printTree(cout);
   /*while (infile.getline(line, lineLength))
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
            if (str.compare("") != 0)
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
   }*/

   cout << "\nexit\n";

   return 0;
}
