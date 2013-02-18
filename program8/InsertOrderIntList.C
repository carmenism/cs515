#include "InsertOrderIntList.h"

   // constructs empty list
   InsertOrderIntList::InsertOrderIntList()
   {
      head = new Elem;
      head->info = 0;
      head->next = 0;
      tail = head;
   }

   // copy constructor
   InsertOrderIntList::InsertOrderIntList(const InsertOrderIntList &v)
   {
      Elem * p1;
      Elem * p2 = v.head;

      if (v.head == v.tail)
      {
         head = new Elem;
         head->info = 0;
         head->next = 0;
         tail = head;
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
   InsertOrderIntList::~InsertOrderIntList()
   {
      Elem * p = head;
      while (head)
      {
         p = head;
         head = head->next;
         delete p;
      }
   }

   // assignment operator
   InsertOrderIntList & InsertOrderIntList::operator = (const InsertOrderIntList &v)
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

         if (v.head == v.tail)
         {
            head = new Elem;
            head->info = 0;
            head->next = 0;
            tail = head;
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

   // inserts integer in order
   void InsertOrderIntList::insert(int v)
   {
      Elem * p = new Elem;
      p->info = v;
      p->next = 0;

      if (head == tail)
      {
         tail = p;
         head->next = tail;
      }
      else
      {
         tail->next = p;
         tail = p;
      }
   }

   // outputs calls to specified stream
   void InsertOrderIntList::output(ostream &s) const
   {
      Elem * p = head->next;

      if (p)
      {
         s << p->info;
         p = p->next;
      }

      while (p)
      {
         s << ", " << p->info;
         p = p->next;
      }
   }

// outputs calls to stream
ostream & operator << (ostream & s, const InsertOrderIntList &v)
{
   v.output(s);
   return s;
}


