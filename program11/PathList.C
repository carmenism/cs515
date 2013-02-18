/* Carmen St. Jean - CS 515, A11, December 10, 2009
 *
 * This class provides pairs of vertices for the paths.
 * The "left" value is the "from" vertex and the "right"
 * value is the "to" vertex.  This class can find paths
 * between any two vertices or, if a path does not exist,
 * then it reports so.
 */

#include "PathList.h"

   // constructs empty list
   PathList::PathList()
   {
      head = new Elem;
      head->left = -1;
      head->right = -1;
      head->next = 0;
      tail = head;
   }

   // inserts pairs of vertices
   void PathList::insert(int l, int r)
   {
      Elem * p = new Elem;
      p->left = l;
      p->right = r;
      p->forPath = false;
      p->next = 0;

      tail->next = p;
      p->prev = tail;
      tail = p;

      Elem * pp = head->next;
   }

   // outputs specified path (if it exists)
   void PathList::findpath(int from, int to) const
   {
      Elem * p = tail;
      Elem * stack;

      while (p->left != -1)
      {
         if (p->left == from && p->right == to)
         {
            p->forPath = true;
            to = p->left;
            break;
         }
         if (p->right == to)
         {
            p->forPath = true;
            to = p->left;
         }

         p = p->prev;
      }

      if (p->left == from)
      {
         Elem * pp = head->next;

         while (p)
         {
            if (p->forPath)
            {
               cout << " (" << p->left << ","
                            << p->right << ")";
               p->forPath = false;
            }
            p = p->next;
         }
      }
      else
      {
         cout << " no path";
      }
   }