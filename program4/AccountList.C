/* this class defines an insertion order list of accounts.
 * Accounts are located by the account equality operators, and
 * the list is not assumed to be ordered by accounts.  Accounts
 * can be inserted (to the tail of the list) and found.  The list
 * (accounts) can be printed
*/

#include "AccountList.h"

   // constructs empty list
   AccountList::AccountList()
   {
      head = 0;
      tail = 0;
   }

   // destructor
   AccountList::~AccountList()
   {
      Elem * p;
      while (head)
      {
         p = head;
         head = head->next;
         delete p;
      }
   }

   // inserts account to tail of list
   void AccountList::insert(const Account &v)
   {
      Elem * p = new Elem;
      p->info = v;
      p->next = 0;

      if (find(v) == 0)
      {
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
      else
      {
         //account already in list
      }
   }

   // outputs accounts to specified stream
   void AccountList::output(ostream &s) const
   {
      Elem * p = head;
      while (p)
      {
         s << "-------------------------------------------\n";
         s << p->info << '\n';
         p = p->next;
      }
   }

   // finds account matching account (dummy) passed.  If
   // found, address of account found is returned.
   // Otherwise, NULL is returned.
   Account * AccountList::find(const Account &v)
   {
      Elem * p = head;

      while (p && v != (p->info))
      {
         p = p->next;
      }

      if (p)
      {
         return &(p->info);
      }
      else
      {
         return 0;
      }
   }

// outputs accounts to stream
ostream & operator << (ostream & s, const AccountList &v)
{
   v.output(s);
   return s;
}


