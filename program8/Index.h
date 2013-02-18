#ifndef INDEX_H
#define INDEX_H

#include <string>
#include <iostream>
using namespace std;
#include "InsertOrderIntList.h"

class Index {

    public:

        Index();
            // constucts empty index tree

        ~Index();
            // destructor

        void insert(string v, int line);
            // inserts value onto tree in alphabetical order

        InsertOrderIntList * find(string v);
            // finds value in tree, returns null if not found

        void output(ostream &) const;
            // prints elements of tree in order

        bool empty();
            // returns true if the tree is empty

        struct Node {
           string item;
           InsertOrderIntList references;
           Node * left;
           Node * right;
        };

    private:
        Index(const Index&); //not implemented
        Index& operator =(const Index&); //not implemented

        static void nodeDeleter(Node * r);
            // helper method for destructor, deletes using recursion

        static void nodeInserter(Node * &r, string v, int line);
            // helper method for insert, inserts using recursion

        static void traversePrint(Node * r, ostream &s);
            // helper method for output, prints in-order using recursion

        Node * root;
};

ostream& operator <<(ostream&, const Index&);
    // outputs elements of tree in alphabetical order

#endif
