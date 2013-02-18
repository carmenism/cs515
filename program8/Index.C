/*  Carmen St. Jean - CS 515 - for A8  */

#include "Index.h"

   // constucts empty index tree
   Index::Index()
   {
      root = 0;
   }

   // destructor
   Index::~Index()
   {
      nodeDeleter(root);
   }

   // inserts value onto tree in alphabetical order
   void Index::insert(string v, int line)
   {
      InsertOrderIntList * list = find(v);

      if (list)
      {
         (*list).insert(line);
      }
      else
      {
         nodeInserter(root, v, line);
      }
   }

   // finds value in tree, returns null if not found
   InsertOrderIntList * Index::find(string v)
   {
      Node * p = root;

      while (p && v.compare(p->item) != 0)
      {
         if (v.compare(p->item) < 0)
            p = p->left;
         else
            p = p->right;
      }

      if (p == 0)
         return 0;
      else
         return &(p->references);
   }

   // prints elements of tree in order
   void Index::output(ostream &s) const
   {
      traversePrint(root, s);
   }

   // returns true if the tree is empty
   bool Index::empty()
   {
      return (root == 0);
   }

   // helper method for destructor, deletes using recursion
   void Index::nodeDeleter(Node * r)
   {
      if (r)
      {
         nodeDeleter(r->left);
         nodeDeleter(r->right);
         delete r;
      }
   }

   // helper method for insert, inserts using recursion
   void Index::nodeInserter(Node * &r, string v, int line)
   {
      if (r == 0)
      {
         r = new Node;
         r->item = v;
         InsertOrderIntList i;
         i.insert(line);
         r->references = i;
         r->left = 0;
         r->right = 0;
      }
      else if (v.compare(r->item) < 0)
      {
         nodeInserter(r->left, v, line);
      }
      else
      {
         nodeInserter(r->right, v, line);
      }
   }

   // helper method for output, prints in-order using recursion
   void Index::traversePrint(Node * r, ostream &s)
   {
      if (r)
      {
         traversePrint(r->left, s);
         s << r->item << " -- " << r->references << "\n";
         traversePrint(r->right, s);
      }
   }

// outputs elements of tree in alphabetical order
ostream& operator <<(ostream &s, const Index &v)
{
   v.output(s);
   return s;
}