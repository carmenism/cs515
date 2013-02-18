#ifndef STRINGBAG_H
#define STRINGBAG_H

/* this class defines a bag of license plate numbers.  Plates may
 * be inserted into the bag, and then the bag can be output,
 * outputting only those plates with a specified number or
 * greater in the bag.  The standard output operator outputs
 * everything in the bag.
 *
 * the bag is ordered.
*/

#include <iostream>
#include <string>
using namespace std;

class StringBag {

    public:

        StringBag();
            // constructs empty bag

        ~StringBag();
            // destructor

        void insert(const string &v);
            // inserts v into bag

        void output(ostream &s, int minCount) const;
            // outputs items in the bag with a count that is at
            // least the value specified

        void printTree(ostream &s) const;
            // outputs tree using inorder scan backwards,
            // indenting tree levels so tree can be viewed

    private:
        
        StringBag(const StringBag &);
        StringBag & operator = (const StringBag &);
            // copy and assignment, not implemented

        enum {maxPerNode=2};

        struct BagItem {
            string info;
            int count;
        };

        struct Node {
            int numItems;
            BagItem item[maxPerNode];
            Node * child[maxPerNode+1];
        };

        Node * root;

        // ---------------------------------------------------
        // private class functions for detailed manipulation of
        // nodes
            
        static void addItem(Node *r, int pos, const BagItem &v,
            Node * newRight);
            // adds v, with its right child, to node r

        static void split(Node *r, int pos, BagItem &mid,
            Node *& newNode);
            // splits info in r and mid (plus its left pointer)
            // into two nodes, with middle value being passed
            // back along with pointer to new node.  Original
            // node stays on the left

        // ---------------------------------------------------

        // recursive work functions for public methods

        static bool insert(Node *&root, const string &v,
            BagItem & mid, Node *&newRight);

        static void deleteAll(Node *root);

        static void output(ostream &s, const Node *root, int minCount);

        static void printTree(ostream &s, const Node *p, int level);
};

ostream & operator << (ostream &s, const StringBag & v);
    // outputs items in bag, along with counts

#endif
