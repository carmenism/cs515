/* this header file provides the structure definition and forward
 * declaration for a number of functions and procedures which
 * manipluate chains of elements which contain pointers to
 * tickets.
 *
 * the chain is maintained in reverse id order, it assumes
 * tickets are entered in ascending id order
 *
 * the operations are tailored to the transport ticket problem
 * (assignment 3, CS515, fall 2009)
*/

class Ticket;

struct Elem {
    Ticket * infoPtr;
    Elem * next;
};

void insert(Elem *&head, Ticket *ticketPtr);
    // inserts ticket to tail of chain, assumes id numbers are
    // inserted in ascending order and assumes no duplication

void remove(Elem *&head, Ticket ticket);
    // finds and removes ticket from chain.  Assumes ticket is
    // present

Ticket * find(Elem *head, Ticket ticket);
    // tries to find ticket in chain.  If there, a pointer to the
    // ticket found is returned.  If not found, null (0) is
    // returned.

void removeChain(Elem *&head);
    // removes and deallocates all elements of the chain.  Head
    // is set to 0
