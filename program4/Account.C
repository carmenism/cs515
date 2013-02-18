/* this class defines a phone account, which is identified by is
 * phone number.  Each phone account has its phone number, a
 * previous balance and a billing address.
 * Accounts can be input, compared and printed (which prints a bill).
 * Calls can be added to the account for billing purposes.
 */

#include "charges.h"
#include "Account.h"

   // default account
   Account::Account()
   {
      prevBalance = 0;
      current = 0;
      instate = *(new CallList());
      outstate = *(new CallList());
      acctNumber = *(new PhoneNumber());
   }

   // generates account with phone number
   Account::Account(const PhoneNumber & id)
   {
      prevBalance = 0;
      current = 0;
      instate = *(new CallList());
      outstate = *(new CallList());
      address = "dummy";
      acctNumber = id;
   }

   // inputs account in order
   //   phoneNumber prevBalance billingAddress
   // phone number in (aaa) eee-nnnn form
   // billing address end of line terminated
   void Account::input(istream &s)
   {
      s >> acctNumber >> prevBalance;
      getline(s, address, '\n');
      current += prevBalance + serviceCharge;
   }

   // adds call to account, updates lists and charges as
   // appropriate
   void Account::addCall(const Call &v)
   {
      if (v.isLocalCall())
      {
         // no charge
      }
      else if (v.isInStateCall())
      {
         instate.insert(v);
         current += instateCharge * v.getDuration();
      }
      else if (v.isOutOfStateCall())
      {
         outstate.insert(v);
         current += outstateCharge * v.getDuration();
      }

   }

   // outputs account in form of a bill, including lists
   // of instate and long distance calls
   void Account::output(ostream &s) const
   {
      float newCharges = current - prevBalance - serviceCharge;
      s << address << '\n';
      s << "  number: " << acctNumber << "\n";
      s << "  previous balance: " << prevBalance << "\n";
      s << "  new charges: " << newCharges << "\n";
      s << "  service charge: " << serviceCharge << "\n";
      s << "  new balance: " << current << "\n\n";
      s << "instate calls\n" << instate;
      s << "\nout of state calls\n" << outstate;
   }

   // equality operators based on phone number
   bool Account::operator == (const Account &v) const
   {
      return (acctNumber == v.acctNumber);
   }

   bool Account::operator != (const Account &v) const
   {
      return (acctNumber != v.acctNumber);
   }

// inputs account in form specified above
istream & operator >> (istream &s, Account &v)
{
   v.input(s);
   return s;
}

// outputs account in form of a bill
ostream & operator << (ostream &s, const Account &v)
{
   v.output(s);
   return s;
}


