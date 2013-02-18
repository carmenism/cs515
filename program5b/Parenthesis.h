#ifndef PARENTHESIS_H
#define PARENTHESIS_H

/* this class defines a class which stores placement information
	for several different types of parentheses.  Information includes
	the parenthesis character itself, the line number and character
	number within the line on which the parenthesis appears.
*/

#include <iostream>
using namespace std;

class Parenthesis {
	friend ostream& operator <<(ostream&, const Parenthesis &);
		//outputs parenthesis character with line and character number

	public:
		Parenthesis();
			//uninitialized object

		Parenthesis(char paren, int linenum, int charnum);
			//constructs parenthesis object at given line and character
			//number within line.

		bool match(const Parenthesis &closeParen) const;
			//returns true if closeParen is correct kind to match
			//opening paren on left.  If left is not an open paren
			//result will be false.

		static bool isOpenParen(char ch);
			//returns true if character is an open parenthesis recognized
			//by the class

		static bool isCloseParen(char ch);
			//returns true if character is a close parenthesis recognized
			//by the class

	private:
		char parenChar;
		int lineNumber;
		int charNumber;
};
		
#endif

