/*
 * program4.C
 *
 * Carmen St. Jean
 * CS 515, Assignment 4
 * October 14, 2009
 *
 * Assignment 4 uses dynamically allocated chains to
 * process phone bill information.  The data input
 * consists of an integer for the number of accounts,
 * a list of accounts, and a list of phone calls.  The
 * program reads in the input and silently calculates
 * the charges to each account while recording calls.
 * At the end, the program reports the final bill.
 *
 * A phone number is formatted as follows:
 *    (aaa) eee-nnnn
 * The "aaa" represents the area code, the "eee"
 * represents the exchange, and the "nnnn" represents
 * the rest of the number.
 *
 * An account is formatted as follows:
 *    phoneNumber prevBalance address
 * The phone number is formatted as above and is what
 * will be used to refer to this account.  prevBalance
 * is an integer which refers to the previous balance.
 * (A negative value means the user overpayed.)  The
 * address (which also includes a name) is simply a
 * string which is terminated by a new-line char.
 *
 * A call is formated as follows:
 *    fromPhoneNumber toPhoneNumber duration
 * The two phone numbers are formatted as seen above
 * and the duration is an integer.
 *
 * Note: local calls have no charge and are not added
 * to the bill.  Only non-local, in-state calls and
 * out-of-state calls have charges.
 */

#include <iostream>
#include "charges.h"
#include "AccountList.h"
#include "CallList.h"

using namespace std;


int main()
{
   AccountList * accts = new AccountList;
   Account * a, * fromId, * foundAcct;

   int n;
   int count = 0;
   cin >> n;

   if (n <= 0)
      cout << "\nno account data, quitting\n";

   while (cin && n > 0)
   {
      if (count < n)
      {
         a = new Account;

         if (cin >> (*a))
         {
            (*accts).insert(*a);
            count++;
         }
         else
         {
            n = 0;
         }
      }
      else
      {
         Call * c = new Call;

         if (cin >> (*c))
         {
            PhoneNumber p = (*c).getFromNumber();
            fromId = new Account(p);
            foundAcct = (*accts).find(*fromId);
            if (foundAcct !=0)
            {
               (*foundAcct).addCall(*c);
            }
            else
            {
               cout << "\ningoring call: ";
               cout << (*c) << "\n";
            }
         }
         else
         {
            n = 0;
         }
      }
   }

   cout << "\n" << (*accts);

   delete accts;

   return 0;
}
