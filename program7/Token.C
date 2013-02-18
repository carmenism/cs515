/* this class defines an input token which is either a
    symbolic character, an identifier, or an unsigned real.  A
    real contains only digits and an optional imbedded decimal
    point, a symbol is a single non-letter non-digit non-space
    character.  Identifiers start with a letter and contain only
    letters and digits.
*/

#include <ctype.h>
#include "Token.h"

const int buflen = 1024;

// ---------------------------------------------------------
//creates empty token which contains no
//value

Token::Token()
{
    kind = none;
}

// ---------------------------------------------------------
// creates a symbol token

Token::Token(char ch)
{
    kind = issym;
    symbol = ch;
}

// ---------------------------------------------------------
// creates a number token

Token::Token(float num)
{
    kind = isnum; 
    number = num;
}

// ---------------------------------------------------------
// creates id token.  Assumes string passed is in
// correct form for id.

Token::Token(const string & id)
{
    kind = isid;
    identifier = id;
}

// ---------------------------------------------------------
//returns true if token is an real

bool Token::isNumber() const
{
    return kind == isnum;
}

// ---------------------------------------------------------
//returns true if token is a Symbol

bool Token::isSymbol() const
{
    return kind == issym;
}

// ---------------------------------------------------------
// returns true if token is an id

bool Token::isIdentifier() const
{
    return kind == isid;
}

// ---------------------------------------------------------
//returns real value of token  id value of token
// throws exception if not a number token

float Token::numValue() const throw(WrongKind)
{
    if (kind != isnum)
        throw WrongKind();

    return number;
}

// ---------------------------------------------------------
//returns symbol value of token id value of token
// throws exception if not an symbol token

char Token::symValue() const throw(WrongKind)
{
    if (kind != issym)
        throw WrongKind();

    return symbol;
}

// ---------------------------------------------------------
// returns id value of token
// throws exception if not an id token

const string & Token::idValue() const throw(WrongKind)
{
    if (kind != isid)
        throw WrongKind();

    return identifier;
}

// ---------------------------------------------------------
// inputs next token if there is one

void Token::input(istream &s)
{
    char ch;
    char buffer[buflen];
    int i;

    if (s >> ch) {

        if (isalpha(ch)) {
            i = 0;
            while (isalpha(ch) || isdigit(ch)) { 
                buffer[i++] = ch;
                s.get(ch);
            }

            buffer[i] = '\0';

            s.putback(ch);

            kind = isid;
            identifier = string(buffer);
            }

        else if (isdigit(ch) || ch == '.') {
            s.putback(ch);
            s >> number;
            kind = isnum;
        }

        else {
            kind = issym;
            symbol = ch;
        }
    }
}

// ---------------------------------------------------------
// outputs token

void Token::output(ostream &s) const
{
    switch (kind) {

        case isid:
            s << identifier;
            break;

        case issym:
            s << symbol;
            break;

        case isnum:
            s << number;
            break;

        case none:
            cerr << "[not-a-token]";
    }
}

// ---------------------------------------------------------
//inputs next token

istream& operator >>(istream &s, Token &v)
{
    v.input(s);
    return s;
}

// ---------------------------------------------------------
//outputs token

ostream& operator <<(ostream &s, const Token &v)
{
    v.output(s);
    return s;
}
