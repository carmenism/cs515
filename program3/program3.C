/*
 * program3.C
 *
 * Carmen St. Jean
 * CS 515, Assignment 3
 * September 29, 2009
 *
 * Assignment 3 simulates a simple multiride
 * ticket-based transportation system.  The
 * program prompts for commands:
 *    p rides    = purchase ticket (ride:int)
 *    c id       = check ticket (id:int)
 *    a id rides = add rides (id:int, rides:int)
 *    r id       = use ride (id:int)
 *    q          = terminate program
 * This program utilizes chains with the Ticket
 * class to store the tickets.  Upon the 'q'
 * command, all elements of the chain are
 * released from memory.
 */

#include <iostream>
#include "Ticket.h"
#include "chains.h"
using namespace std;

void purchaseTicket(Elem *&head, int r);
void checkTicket(Elem *&head);
void addToTicket(Elem *&head);
void rideTicket(Elem *&head);

int main()
{
   int curId = 1;
   Elem * head = 0;
   char command;

   cout << "\nenter commands, end with q\n";
   cin >> command;

   while (command != 'q')
   {
      if (command == 'p')
      {
         purchaseTicket(head, curId);
         curId++;
      }
      if (command == 'c')
      {
         checkTicket(head);
      }
      if (command == 'a')
      {
         addToTicket(head);
      }
      if (command == 'r')
      {
         rideTicket(head);
      }
      cout << "\n";
      cin >> command;
   }
   cout << "\n";
   removeChain(head);
   return 0;
}

// purchases a new ticket with the specified
// number of rides, uses a new unique ID
void purchaseTicket(Elem *&head, int r)
{
   int rides;
   cin >> rides;
   Ticket *t = new Ticket(r, rides);
   insert(head, t);
   cout << "\nnew ticket: " << r;
   cout << " with " << rides << " rides";
}

// check specified ticket from input and print
// the number of remaining rides
void checkTicket(Elem *&head)
{
   int id;
   cin >> id;
   Ticket t1(id);
   Ticket * t2 = find(head, t1);
   if (t2)
   {
      cout << "\nticket " << id << " has ";
      cout << (*t2).ridesLeft();
      cout << " rides left";
   }
   else
   {
      cout << "\nticket " << id;
      cout << " not in the system";
   }
}

// add specified number of rides from input to
// the specified ticket if it exists
void addToTicket(Elem *&head)
{
   int id, rides;
   cin >> id >> rides;
   Ticket t1(id);
   Ticket * t2 = find(head, t1);
   if (t2)
   {
      (*t2).addRides(rides);
      cout << "\nadded " << rides;
      cout << " to ticket " << id;
   }
   else
   {
      cout << "\nticket " << id;
      cout << " not in the system";
   }
}


// uses ticket ID from input for one ride and
// removes the ticket if all rides have been used
void rideTicket(Elem *&head)
{
   int id;
   cin >> id;
   Ticket t1(id);
   Ticket * t2 = find(head, t1);
   if (t2)
   {
      (*t2).takeRide();
      cout << "\nusing ticket ";
      cout << id;
      if ((*t2).ridesLeft() == 0)
      {
         remove(head, *t2);
         cout << "\nticket " << id;
         cout << " used up";
      }
   }
   else
   {
      cout << "\nticket " << id;
      cout << " not in the system";
   }
}

// inserts ticket to tail of chain, assumes id
// numbers are inserted in ascending order and
// assumes no duplication
void insert(Elem *&head, Ticket *ticketPtr)
{
   Elem * p = head;
   Elem * prev = 0;
   while (p && *(p->infoPtr) <= *ticketPtr)
   {
      prev = p;
      p = p->next;
   }

   p = new Elem;
   p->infoPtr = ticketPtr;

   if (prev == 0)
   {
      p->next = head;
      head = p;
   }
   else
   {
      p->next = prev->next;
      prev->next = p;
   }
}

// finds and removes ticket from chain.  Assumes
// ticket is present
void remove(Elem *&head, Ticket ticket)
{
   Elem * p = head;
   Elem * prev = 0;
   while (p && ticket != *(p->infoPtr))
   {
      prev = p;
      p = p->next;
   }
   if (p == 0)
   {
      // element not found
   }
   else if (prev == 0)
   {
      head = head->next;
      delete p;
   }
   else
   {
      prev->next = p->next;
      delete p;
   }
}

// tries to find ticket in chain.  If there, a
// pointer to the ticket found is returned.  If
// not found, null (0) is returned.
Ticket * find(Elem *head, Ticket ticket)
{
   Elem * p = head;
   while (p && ticket != *(p->infoPtr))
   {
      p = p->next;
   }
   if (p)
   {
      return (p->infoPtr);
   }
   else
   {
      return 0;
   }
}

// removes and deallocates all elements of the
// chain.  Head is set to 0
void removeChain(Elem *&head)
{
   Elem * p = head;
   while (head)
   {
      p = head;
      head = head->next;
      delete p->infoPtr;
      delete p;
   }
   head = 0;
}