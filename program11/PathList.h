/* Carmen St. Jean - CS 515, A11, December 10, 2009
 *
 * This class provides pairs of vertices for the paths.
 * The "left" value is the "from" vertex and the "right"
 * value is the "to" vertex.  This class can find paths
 * between any two vertices or, if a path does not exist,
 * then it reports so.
 */

#ifndef PATHLIST_H
#define PATHLIST_H
#include <iostream>
using namespace std;

class PathList {

    public:

        PathList();
            // constructs empty list

        void insert(int l, int r);
            // inserts pairs of vertices

        void findpath(int from, int to) const;
            // outputs specified path (if it exists)

    private:
        struct Elem {
            int left;
            int right;
            bool forPath;
            Elem * next;
            Elem * prev;
        };

        Elem * head;
        Elem * tail;
};

#endif
