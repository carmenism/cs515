/* this class defines an insertion order list of phone calls.
 * Calls * can be inserted (to the tail of the list).  The list
 * (calls) can be printed
*/

#include "CallList.h"

   // constructs empty list
   CallList::CallList()
   {
      head = 0;
      tail = 0;
   }

   // copy constructor
   CallList::CallList(const CallList &v)
   {
      Elem * p1;
      Elem * p2 = v.head;

      if (p2 == 0)
      {
         head = 0;
         tail = 0;
      }
      else
      {
         head = new Elem;
         head->info = v.head->info;
         p1 = head;
         p2 = v.head->next;

         while (p2)
         {
            p1->next = new Elem;
            p1 = p1->next;
            p1->info = p2->info;
            p2 = p2->next;
         }

         p1->next = 0;
         tail = p1;
      }
   }

   // destructor
   CallList::~CallList()
   {
      Elem * p;
      while (head)
      {
         p = head;
         head = head->next;
         delete p;
      }
   }

   // assignment operator
   CallList & CallList::operator = (const CallList &v)
   {
      if (this != &v)
      {
         // destructor code
         Elem * p;
         while (head)
         {
            p = head;
            head = head->next;
            delete p;
         }

         // copy code
         Elem * p1;
         Elem * p2 = v.head;

         if (p2 == 0)
         {
            head = 0;
            tail = 0;
         }
         else
         {
            head = new Elem;
            head->info = v.head->info;
            p1 = head;
            p2 = v.head->next;

            while (p2)
            {
               p1->next = new Elem;
               p1 = p1->next;
               p1->info = p2->info;
               p2 = p2->next;
            }

            p1->next = 0;
            tail = p1;
         }
      }

      return *this;
   }

   // inserts call to tail of list
   void CallList::insert(const Call &v)
   {
      Elem * p = new Elem;
      p->info = v;
      p->next = 0;

      if (head == 0)
      {
         head = p;
         tail = head;
      }
      else
      {
         tail->next = p;
         tail = p;
      }
   }

   // outputs calls to specified stream
   void CallList::output(ostream &s) const
   {
      Elem * p = head;
      while (p)
      {
         s << p->info;// << '\n';
         p = p->next;
      }
   }

// outputs calls to stream
ostream & operator << (ostream & s, const CallList &v)
{
   v.output(s);
   return s;
}


