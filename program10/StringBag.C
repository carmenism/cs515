/* this class defines a bag of license plate numbers.  Plates may
 * be inserted into the bag, and then the bag can be output,
 * outputting only those plates with a specified number or
 * greater in the bag.  The standard output operator outputs
 * everything in the bag.
 *
 * the bag is ordered.
 */

#include "StringBag.h"

// ------------------------------------------------------
// constructs empty bag

StringBag::StringBag()
{
    root = 0;
}

// ------------------------------------------------------
// destructor

StringBag::~StringBag()
{
    deleteAll(root);
}

// ------------------------------------------------------
// inserts v into bag

void StringBag::insert(const string &v)
{
    BagItem mid;
    Node * newRight;
    Node * left;

    if (!insert(root, v, mid, newRight)) {
        left = root;
        root = new Node;
        root->numItems = 1;
        root->item[0] = mid;
        root->child[0] = left;
        root->child[1] = newRight;
        root->child[2] = 0;
        }
}

// ------------------------------------------------------
// outputs items in the bag with a count that is at
// least the value specified

void StringBag::output(ostream &s, int minCount) const
{
    output(s, root, minCount);
}

// ------------------------------------------------------
// outputs items in the bag with a count in tree format

void StringBag::printTree(ostream &s) const
{
    printTree(s, root, 0);
}

// ------------------------------------------------------
// outputs items in bag, along with counts

ostream & operator << (ostream &s, const StringBag & v)
{
    v.output(s, 1);
    return s;
}

// ------------------------------------------------------
// work function for insertion

bool StringBag::insert(Node *&r, const string &v, BagItem & mid,
    Node *& newRight)
{
    int i;
    bool success;

    if (r == 0) {
        mid.info = v;
        mid.count = 1;
        newRight = 0;
        return false;
        }

    else {
        for (i=0; i<r->numItems && r->item[i].info < v; i++); //cout << "\ni: " << i << "\n";

        if (i < r->numItems && r->item[i].info == v) {
            r->item[i].count++;
            return true;
            }

        else {
            success = insert(r->child[i], v, mid, newRight);

            if (success)
                return true;

            else if (r->numItems < maxPerNode) { //cout << "\n add at i: " << i << "\n";
                addItem(r, i, mid, newRight);
                return true;
                }

            else {
                split(r, i, mid, newRight); //cout << "\nsplit at i: " << i << "\n";
                return false;
            }
        }
    }
}

// ------------------------------------------------------
// work function for destructor

void StringBag::deleteAll(Node *r)
{
    // *** to be filled in -- recursively deletes all the
    // *** nodes in the tree
}

// ------------------------------------------------------
// work function for output operation -- outputs strings with
// count >= minimum specified

void StringBag::output(ostream &s, const Node *r, int minCount)
{
    // *** to be filled in -- recursively goes through the
    // *** nodes in the tree in a normal in-order traversal
    // *** so the values are processed in order.  It prints
    // *** out only those items whose count is >= the specified
    // *** minimum
}

// ------------------------------------------------------
// work function for printTree operation -- outputs strings with
// count in tree format.

void StringBag::printTree(ostream &s, const Node *r, int level)
{
    int i;

    if (r) {
        printTree(s, r->child[r->numItems], level+1);
        for (i = r->numItems-1; i>=0; i--) {
            for (int j=0; j<level; j++)
                s << "    ";
            s << r->item[i].count << " --- " <<
                r->item[i].info << '\n';
            printTree(s, r->child[i], level+1);
        }

    }
}
// ------------------------------------------------------
/* this procedure adds v (with its right pointer) to the current
 * node pointed to by r.  It's position in the node will be
 * determined the values already in the node.  Pos is the
 * position of the child pointer the insertion attempted.
*/

void StringBag::addItem(Node *r, int pos, const BagItem &v,
        Node * newRight)
{
    // *** to be filled in

    // *** pre condition -- node pointed to by r contains only
    // ***    one item and 2 valid child pointers
    // *** pre condition -- pos is child index that was followed,
    // ***    and thus is where v would have fit had there been
    // ***    room below
    // *** pre condition -- newRight points to node with values
    // **     larger than that in v

    if (pos == 0)
    {
       cerr << "\nadd item - case 1: " << r->item[0].info << " pos: " << pos << " v: " << v.info << "\n";
       BagItem temp = r->item[0];
       r->item[0] = v;
       r->item[1] = temp;
       r->numItems++;
       r->child[1] = newRight;
    }
    else if (pos == 1)
    {
       cerr << "\nadd item - case 2: " << r->item[0].info << " pos: " << pos << " v: " << v.info<< "\n";
       r->item[1] = v;
       r->numItems++;
       r->child[2] = newRight;
    }
    else if (pos == 2) // probably unnecessary
    {
       cout << "\n will we ever get here????";
    }

    // *** post condition -- node pointed to by r will contain
    // ***    two items, and they will be in the correct (lexical)
    // ***    order.  The node pointed to by newRight will be to
    // ***    the right of where the new item was placed.
}

// ------------------------------------------------------
// this procedure is provided with an item and its new right
// child pointer, along with the position in r where the split is
// coming from.  The procedure splits r into the original and a
// new node, which it passes back, along with the middle value.

void StringBag::split(Node *r, int pos, BagItem &mid,
        Node *& newNode)
{
    // *** to be filled in
    cout << "\nSPLIT\n";
    // *** pre condition -- node pointed to by r contains two
    // ***   items and 3 valid child pointers
    // *** pre condition -- pos is child index that was followed,
    // ***    and thus is where mid would have fit had there been
    // ***    room below
    // *** pre condition -- newRight points to node with values
    // **     larger than that in mid

//    cout << mid.info;
///    cerr << "r: " << r->item[0].info;
///    cout << "\npos: " << pos << "\n";

    if (pos == 0)
    {
       cerr << "case 1\n";

     //  if (newNode == NULL)
     //  {
          BagItem temp = r->item[0];
          r->item[0] = mid;
          mid = temp;

          r->numItems = 1;

          Node * largestNode = new Node;
          largestNode->item[0] = r->item[1];
          largestNode->numItems = 1;
          largestNode->child[0] = r->child[1];
          largestNode->child[1] = r->child[2];

          r->child[1] = newNode;

          newNode = largestNode;
      // }
    }
    else if (pos == 1)
    {
       cerr << "case 2\n";
     //  if (newNode == NULL)
     //  {
          Node * largestNode = new Node;
          largestNode->item[0] = r->item[1];
          largestNode->numItems = 1;
          largestNode->child[0] = newNode;
          largestNode->child[1] = r->child[2];

 //         mid = r->item[1];
          r->numItems = 1;

          newNode = largestNode;
      // }
    }
    else if (pos == 2)
    {
       cerr << "case 3\n";

     //  if (newNode == NULL)
    //   {
          Node * largestNode = new Node;
          largestNode->item[0] = mid;
          largestNode->numItems = 1;
          largestNode->child[0] = r->child[2];
          largestNode->child[1] = newNode;

          mid = r->item[1];
          r->numItems = 1;

          newNode = largestNode;
     //  }
       //cout << "\n 2 split pos = " << pos;
    }

    // *** post condition -- mid now contains middle item
    // *** post condition -- r points to original node with
    // ***    one item (smallest) and two child pointers
    // *** post condition -- newNode points to a new node with
    // ***    one item (largest) and two child pointers
    // *** post condition -- original newNode is one of children
    // ***    of the two nodes
}
