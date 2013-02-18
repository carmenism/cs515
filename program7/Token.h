#ifndef TOKEN_H
#define TOKEN_H

/* this class defines an input token which is either a
    symbolic character, an identifier, or an unsigned real.  A
    real contains only digits and an optional imbedded decimal
    point, a symbol is a single non-letter non-digit non-space
    character.  Identifiers start with a letter and contain only
    letters and digits.
*/

#include <string>
#include <iostream>
using namespace std;

class Token {

    public:

        // execptions

            class WrongKind{};

        Token();
            //creates empty token which contains no
            //value

        Token(char);
            // creates a symbol token

        Token(float);
            // creates a number token

        Token(const string &);
            // creates id token.  Assumes string passed is in
            // correct form for id.

        bool isNumber() const;
            //returns true if token is an real

        bool isSymbol() const;
            //returns true if token is a Symbol

        bool isIdentifier() const;
            // returns true if token is an id

        float numValue() const throw(WrongKind);
            //returns real value of token  id value of token
            // throws exception if not a number token

        char symValue() const throw(WrongKind);
            //returns symbol value of token id value of token
            // throws exception if not an symbol token

        const string & idValue() const throw(WrongKind);
            // returns id value of token
            // throws exception if not an id token

        void input(istream &s);
            // inputs token if there is one

        void output(ostream &s) const;
            // outputs token
    
    private:
        enum Kind {none, isnum, issym, isid};
        Kind kind;

        float number;
        char symbol;
        string identifier;
};

    istream& operator >>(istream&, Token&);
        //inputs next token

    ostream& operator <<(ostream&, const Token&);
        //outputs token

#endif
