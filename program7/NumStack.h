#ifndef PARENSTACK_H
#define PARENSTACK_H

/* this class defines a stack of floats for procedural
	design.  floats may be pushed, popped, and topped.
    and the stack may be tested for empty.
*/


class NumStack {
	public:
        // exceptions

            class Underflow{};
            class Overflow{};

		NumStack();
			//constructs an empty stack

		NumStack(const NumStack &);
			//copy constructor

		~NumStack();
			//destructor

		NumStack& operator =(const NumStack &);
			//assignment operator

		void push(float v) throw(Overflow);
			//modifies stack by inserting v as new top 
			//element

		void pop() throw(Underflow);
			//modifies stack by removing top element

		float top() const throw(Underflow);
			//returns value stored in top element

		bool empty() const;
			//returns true if stack contains no elements

	private:

		struct Element {
			float info;
			Element *next;
		};

		Element *topPointer;
};

#endif
