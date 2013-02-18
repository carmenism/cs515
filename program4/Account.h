#ifndef ACCOUNT_H
#define ACCOUNT_H

/* this class defines a phone account, which is identified by is
 * phone number.  Each phone account has its phone number, a
 * previous balance and a billing address.
 * Accounts can be input, compared and printed (which prints a bill).
 * Calls can be added to the account for billing purposes.
*/

#include <iostream>
#include <string>
using namespace std;

#include "CallList.h"
#include "Call.h"
#include "PhoneNumber.h"

class Account {

    public:
        Account();
            // default account

        Account(const PhoneNumber & id);
            // generates account with phone number

        void input(istream &s);
            // inputs account in order
            //   phoneNumber prevBalance billingAddress
            // phone number in (aaa) eee-nnnn form
            // billing address end of line terminated

        void addCall(const Call &v);
            // adds call to account, updates lists and charges as
            // appropriate

        void output(ostream &s) const;
            // outputs account in form of a bill, including lists
            // of instate and long distance calls

        bool operator == (const Account &v) const;
        bool operator != (const Account &v) const;
            // equality operators based on phone number

    private:
        PhoneNumber acctNumber;
        string address;
        float prevBalance;
        float current;
        CallList instate;
        CallList outstate;
};

istream & operator >> (istream &s, Account &v);
    // inputs account in form specified above

ostream & operator << (ostream &s, const Account &v);
    // outputs account in form of a bill

#endif
