/* this program acts as a test harness for a priority queue which
 * stores strings.  It is an interactive interpreter which
 * exercises the queue.  The program then responds to the
 * following commands
 *
 *  enqueue priority string 
 *  dequeue 
 *  front 
 *  dump 
 *  length
 *  done
 *
 * where "priority" is an integer, and "string" is a space
 * delimited string.
 * 
 * the "enqueue" command inserts the string (space delimited)
 * into the appropriate position in the priority queue. The
 * program will print an error message if an incorrect priority
 * is used.  The "dequeue" command removes the highest priority
 * string.  The "front" command prints the highest priority
 * string, but does not remove it from the queue.  The "dump"
 * command prints out the contents of the queue, including the
 * priorities, while the "length" command simply prints out its
 * length.  The "done" command is used to terminate the program.
 * When the program terminates, if there are values left in the
 * queue, a "queue not empty" message is printed.  A "queue
 * empty" message is printed if an attempt to front or dequeue an
 * empty queue is attempted.
 *
 * at the end of the program, if the queue is empty, unprotected
 * calls to dequeue and front are made, and the exceptions
 * caught, to insure the exceptions are thrown correctly.  In
 * addition, many enqueues are done, with the intent of causing
 * the queue to overflow
*/

#include <string>
#include <iostream>
using namespace std;
#include "PriQueue.h"

//constants
    const string done_com = "done";
    const string enqueue_com = "enqueue";
    const string dequeue_com = "dequeue";
    const string length_com = "length";
    const string print_com = "dump";
    const string front_com = "front";

int main()
{
    string command;
    string info;
    int priority;
    PriQueue queue;
    
    cerr << "enter commands, terminate with " << done_com << '\n';

    do {
        cerr << "\n?> ";
        cin >> command;

        if (command == enqueue_com) {
            cin >> priority >> info;
            try {
                queue.enqueue(priority,info);
            }
                catch(PriQueue::BadPriority) {
                    cerr << "  bad priority\n";
                    }
                catch(PriQueue::Overflow) {
                    cerr << "  too many at that priority\n";
                }
            }

        else if (command == dequeue_com) {
            if (queue.empty())
                cerr << "    queue is empty\n";
            else
                queue.dequeue();
            }

        else if (command == print_com) {
            cerr << queue << '\n';
            }

        else if (command == length_com) {
            cerr << "   queue length: " <<    queue.length() << '\n';
            }

        else if (command == front_com) {
            if (queue.empty())
                cerr << "   queue is empty\n";
            
            else
                cerr << "   front value: " << queue.front() << '\n';
            }

        else if (command != done_com) {
            cerr << "   ** bad command **\n";
            }

    } while (command != done_com);

    cerr << "program terminating\n";
    if (!queue.empty())
        cerr << "    and the queue is not empty\n";

    else {
        try {
            cerr << "testing throw from front\n";
            cerr << queue.front();
        }
            catch(PriQueue::Underflow) {
                cerr << "caught PriQueue::Underflow\n";
                }
            catch(StringQueue::Underflow) {
                cerr << "caught StringQueue::Underflow\n";
                }

        try {
            cerr << "testing throw from dequeue\n";
            queue.dequeue();
        }
            catch(PriQueue::Underflow) {
                cerr << "caught PriQueue::Underflow\n";
                }
            catch(StringQueue::Underflow) {
                cerr << "caught StringQueue::Underflow\n";
                }

        try {
            cerr << "testing throw from enqueue\n";
            for (int i = 0; i<10000000; i++)
                queue.enqueue(1,"testing");
        }
            catch(PriQueue::Overflow) {
                cerr << "caught PriQueue::Overflow\n";
                }
            catch(StringQueue::Overflow) {
                cerr << "caught StringQueue::Overflow\n";
                }
    }

    return 0;
}

