#ifndef ACCOUNTLIST_H
#define ACCOUNTLIST_H

/* this class defines an insertion order list of accounts.
 * Accounts are located by the account equality operators, and
 * the list is not assumed to be ordered by accounts.  Accounts
 * can be inserted (to the tail of the list) and found.  The list
 * (accounts) can be printed
*/

#include <iostream>
using namespace std;

#include "Account.h"

class AccountList {

    public:

        AccountList();
            // constructs empty list

        ~AccountList();
            // destructor

        void insert(const Account &v);
            // inserts account to tail of list

        void output(ostream &s) const;
            // outputs accounts to specified stream

        Account * find(const Account &v);
            // finds account matching account (dummy) passed.  If
            // found, address of account found is returned.
            // Otherwise, NULL is returned.

    private:
        AccountList(const AccountList &);
            // copy constructor, not implemented
        AccountList & operator = (const AccountList &);
            // assignment operator, not implemented

        struct Elem {
            Account info;
            Elem * next;
        };

        Elem * head;
        Elem * tail;
};

ostream & operator << (ostream & s, const AccountList &v);
    // outputs accounts to stream

#endif
