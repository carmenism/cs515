/* this class defines a class which stores placement information
	for several different types of parentheses.  Information includes
	the parenthesis character itself, the line number and character
	number within the line on which the parenthesis appears.
*/

#include "Parenthesis.h"

   //outputs parenthesis character with line and character number
   ostream& operator <<(ostream&s, const Parenthesis &v)
   {
      s << v.parenChar << " line: " << v.lineNumber;
      s << " char pos: " << v.charNumber;
      return s;
   }
		

   //uninitialized object
   Parenthesis::Parenthesis()
   {
   }

   //constructs parenthesis object at given line and character
   //number within line.
   Parenthesis::Parenthesis(char paren, int linenum, int charnum)
   {
      parenChar = paren;
      lineNumber = linenum;
      charNumber = charnum;
   }

   //returns true if closeParen is correct kind to match
   //opening paren on left.  If left is not an open paren
   //result will be false.
   bool Parenthesis::match(const Parenthesis &closeParen) const
   {
      if (parenChar == '(')
         return (closeParen.parenChar == ')');
      else if (parenChar == '{')
         return (closeParen.parenChar == '}');
      else if (parenChar == '[')
         return (closeParen.parenChar == ']');
      else
         return false;
   }

   //returns true if character is an open parenthesis recognized
   //by the class
   bool Parenthesis::isOpenParen(char ch)
   {
      return (ch == '(' || ch == '{' || ch == '[');
   }

   //returns true if character is a close parenthesis recognized
   //by the class
   bool Parenthesis::isCloseParen(char ch)
   {
      return (ch == ')' || ch == '}' || ch == ']');
   }
