
/* this class defines a ticket, which has an id and a specified
 * number of rides.  Rides may be added to tickets, and tickets
 * may be queried as to how many rides are left.  They may be
 * compared, based on id.
 */

#include "Ticket.h"

   // constructs dummy ticket for comparison purposes.
   // Only the id is set up.  Acts as a type conversion
   // operator (automatic) from an integer (id) into a
   // ticket object.
   Ticket::Ticket(int id)
   {
      myId = id;
   }

   // constructs ticket with given id and specified
   // number of rides
   Ticket::Ticket(int id, int rides)
   {
      myId = id;
      numRides = rides;
   }

   // adds n rides to ticket.  Assumes n is positive
   void Ticket::addRides(int n)
   {
      numRides += n;
   }

   // subtracts a ride from the ticket.
   void Ticket::takeRide()
   {
      numRides--;
   }

   // returns number of rides left
   int Ticket::ridesLeft() const
   {
      return numRides;
   }

   // relational operators based on id
   bool Ticket::operator >= (const Ticket &v) const
   {
      return (myId >= v.myId);
   }

   bool Ticket::operator > (const Ticket &v) const
   {
      return (myId > v.myId);
   }

   bool Ticket::operator < (const Ticket &v) const
   {
      return (myId < v.myId);
   }

   bool Ticket::operator <= (const Ticket &v) const
   {
      return (myId <= v.myId);
   }

   // equality operators based on id
   bool Ticket::operator == (const Ticket &v) const
   {
      return (myId == v.myId);
   }

   bool Ticket::operator != (const Ticket &v) const
   {
      return (myId != v.myId);
   }
