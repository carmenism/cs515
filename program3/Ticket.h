#ifndef TICKET_H
#define TICKET_H

/* this class defines a ticket, which has an id and a specified
 * number of rides.  Rides may be added to tickets, and tickets
 * may be queried as to how many rides are left.  They may be
 * compared, based on id.
*/

class Ticket {

    public:

        Ticket(int id);
            // constructs dummy ticket for comparison purposes.
            // Only the id is set up.  Acts as a type conversion
            // operator (automatic) from an integer (id) into a
            // ticket object.

        Ticket(int id, int rides);
            // constructs ticket with given id and specified
            // number of rides

        void addRides(int n);
            // adds n rides to ticket.  Assumes n is positive

        void takeRide();
            // subtracts a ride from the ticket.

        int ridesLeft() const;
            // returns number of rides left

        bool operator >= (const Ticket &v) const;
        bool operator > (const Ticket &v) const;
        bool operator < (const Ticket &v) const;
        bool operator <= (const Ticket &v) const;
            // relational operators based on id

        bool operator == (const Ticket &v) const;
        bool operator != (const Ticket &v) const;
            // equality operators based on id

    private:
        int myId;
        int numRides;
};

#endif
