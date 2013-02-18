/**
 * Carmen St. Jean - CS 515, Assignment 7
 * November 6, 2009
 */

/* this class defines a table of variables.  Variables may be
 * stored and retrieved.  Variables may be modified while within
 * the table, as long as the id does not change.
*/

#include "Table.h"

   // constructs empty table
   Table::Table(int size)
   {
      numElem = size;
      table = new Elem*[numElem];

      for (int i = 0; i < numElem; i++)
      {
         table[i] = 0;
      }
   }

   // outputs variables stored in table to stream
   void Table::output(ostream &s) const
   {
      int count = 0;
      for (int i = 0; i < numElem; i++)
      {
         if (table[i] != 0)
         {
            Elem * p = table[i];

            while (p)
            {
               cout << p->info << "\n";
               count++;
               p = p->next;
            }
         }
      }

      if (count == 0)
         cout << "(no variables)\n";
   }

   // inserts variable into table.  throws exception if
   // already there
   void Table::insert(const Variable &v) throw (Duplicate)
   {      int index = v.hash(numElem);

      Elem * p = table[index];

      while (p && p->info != v)
      {
         p = p->next;
      }

      if (p != 0)
         throw Duplicate();
      else
      {
         p = new Elem;
         p->info = v;
         p->next = table[index];
         table[index] = p;
      }
   }

   // returns variable found, or null if not found
   Variable * Table::find(const Variable &v)
   {
      int index = v.hash(numElem);

      Elem * p = table[index];

      while (p && p->info != v)
      {
         p = p->next;
      }

      if (p != 0)
         return &p->info;
      else
         return NULL;
   }

   // returns variable found, or null if not found
   const Variable * Table::find(const Variable &v) const
   {
      int index = v.hash(numElem);

      Elem * p = table[index];

      while (p && p->info != v)
      {
         p = p->next;
      }

      if (p != 0)
         return &p->info;
      else
         return NULL;
   }

// outputs variables stored in table to stream
ostream & operator << (ostream &s, const Table &v)
{
   v.output(s);
   return s;
}
