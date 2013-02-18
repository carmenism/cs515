/**
 * Carmen St. Jean - CS 515, Assignment 7
 * November 6, 2009
 *
 * This program evulates post-fix expressions.
 * The operations the calculator is to implement
 * are:
 *      (+) addition,
 *      (-) subtraction,
 *      (*) multiplication,
 *      (/) division,
 *      (^) exponentiation,
 * and  (~) negation.
 *
 * The end of an expression is either marked with
 * a semicolon (;), or a number sign (#) followed
 * by a variable name.  The semicolon termination
 * will simply cause the expression result to
 * print.  The number sign termination with a
 * variable name will store the result into the
 * variable name.
 *
 * All numbers must be real and positive (though
 * results and variable contents can be negative).
 * Expressions can involve any combination of
 * numbers and already defined variables.  If
 * any part of an expression is invalid, then
 * the whole expression will be ignored and a
 * message will be printed.
 *
 * Variable names must start with a letter and
 * contain letters and digits.
 *
 * This calculator is implemented with a tokenizer,
 * a stack to store numeric values, and a hashtable
 * to store variables.
 */

#include <string>
#include <iostream>
#include <math.h>
using namespace std;
#include "NumStack.h"
#include "Token.h"
#include "Table.h"

// procedure declarations
bool addition(NumStack &numbers);
bool subtraction(NumStack &numbers);
bool multiplication(NumStack &numbers);
bool division(NumStack &numbers);
bool exponentiation(NumStack &numbers);
bool negation(NumStack &numbers);
void endExpression(NumStack &numbers);
void endExpressionVar(NumStack &numbers, Table &table, Token &t);
void cleanup(NumStack &numbers);

   // constants
   const char add = '+';
   const char subtract = '-';
   const char multiply = '*';
   const char divide = '/';
   const char exponent = '^';
   const char negation_sign = '~';
   const char end_exp = ';';
   const char end_exp_var = '#';

int main()
{
   NumStack numbers;
   Table table;
   Token t;
   bool valid = true;

   cout << "enter postfix expressions, end with ctrl D\n\n";

   while (cin >> t)
   {
      if (t.isNumber() && valid)
      {
         float num = t.numValue();

         try
         {
            numbers.push(num);
         }
         catch(NumStack::Overflow)
         {
            cout << "overflow, ignoring expression";
            cleanup(numbers);
            valid = false;
         }
      }
      else if (t.isIdentifier() && valid)
      {
         string id = t.idValue();
         Variable v(id);
         Variable * var = table.find(v);

         if (var)
         {
            float num = var->getValue();

            try
            {
               numbers.push(num);
            }
            catch(NumStack::Overflow)
            {
               cout << "overflow, ignoring expression";
               cleanup(numbers);
               valid = false;
            }
         }
         else
         {
            cout << "undefined variable ["
                 << id << "]\n\n";
            cleanup(numbers);
            valid = false;
         }
      }
      else if (t.isSymbol())
      {
         char sym = t.symValue();

         if (sym == add && valid)
         {
            valid = addition(numbers);
         }
         else if (sym == subtract && valid)
         {
            valid = subtraction(numbers);
         }
         else if (sym == multiply && valid)
         {
            valid = multiplication(numbers);
         }
         else if (sym == divide && valid)
         {
            valid = division(numbers);
         }
         else if (sym == exponent && valid)
         {
            valid = exponentiation(numbers);
         }
         else if (sym == negation_sign && valid)
         {
            valid = negation(numbers);
         }
         else if (sym == end_exp)
         {
            if (valid)
            {
               endExpression(numbers);
            }
            valid = true;
         }
         else if (sym == end_exp_var)
         {
            if (valid)
            {
               endExpressionVar(numbers, table, t);
            }
            else
            {
               cout << "syntax error\n\n";
               cleanup(numbers);
            }
            valid = true;
         }
      }
   }

   cout << "variables:\n" << table << "\nexit\n";

   return 0;
}

bool addition(NumStack &numbers)
{
   float first, second;

   try
   {
      second = numbers.top();
      numbers.pop();
      first = numbers.top();
      numbers.pop();
      numbers.push(first + second);
      return true;
   }
   catch (NumStack::Underflow)
   {
      cout << "syntax error\n\n";
      cleanup(numbers);
      return false;
   }
   catch(NumStack::Overflow)
   {
      cout << "overflow, ignoring expression";
      cleanup(numbers);
      return false;
   }
}

bool subtraction(NumStack &numbers)
{
   float first, second;

   try
   {
      second = numbers.top();
      numbers.pop();
      first = numbers.top();
      numbers.pop();
      numbers.push(first - second);
      return true;
   }
   catch (NumStack::Underflow)
   {
      cout << "syntax error\n\n";
      cleanup(numbers);
      return false;
   }
   catch(NumStack::Overflow)
   {
      cout << "overflow, ignoring expression";
      cleanup(numbers);
      return false;
   }
}

bool multiplication(NumStack &numbers)
{
   float first, second;

   try
   {
      second = numbers.top();
      numbers.pop();
      first = numbers.top();
      numbers.pop();
      numbers.push(first * second);
      return true;
   }
   catch (NumStack::Underflow)
   {
      cout << "syntax error\n\n";
      cleanup(numbers);
      return false;
   }
   catch(NumStack::Overflow)
   {
      cout << "overflow, ignoring expression";
      cleanup(numbers);
      return false;
   }
}

bool division(NumStack &numbers)
{
   float num, denom;

   try
   {
      denom = numbers.top();
      numbers.pop();

      if (denom == 0)
      {
         cout << "cannot divide by zero\n\n";
         cleanup(numbers);
         return false;
      }
      else
      {
         num = numbers.top();
         numbers.pop();
         numbers.push(num / denom);
         return true;
      }
   }
   catch (NumStack::Underflow)
   {
      cout << "syntax error\n\n";
      cleanup(numbers);
      return false;
   }
   catch(NumStack::Overflow)
   {
      cout << "overflow, ignoring expression";
      cleanup(numbers);
      return false;
   }
}

bool exponentiation(NumStack &numbers)
{
   float base, power;

   try
   {
      power = numbers.top();
      numbers.pop();
      base = numbers.top();
      numbers.pop();
      numbers.push(pow(base, power));
      return true;
   }
   catch (NumStack::Underflow)
   {
      cout << "syntax error\n\n";
      cleanup(numbers);
      return false;
   }
   catch(NumStack::Overflow)
   {
      cout << "overflow, ignoring expression";
      cleanup(numbers);
      return false;
   }
}

bool negation(NumStack &numbers)
{
   float number;

   try
   {
      number = numbers.top();
      numbers.pop();
      numbers.push(-1 * number);
      return true;
   }
   catch (NumStack::Underflow)
   {
      cout << "syntax error\n\n";
      cleanup(numbers);
      return false;
   }
}

void endExpression(NumStack &numbers)
{
   float solution;

   try
   {
      solution = numbers.top();
      numbers.pop();

      if (numbers.empty())
      {
         cout << "result: " << solution << "\n\n";
      }
      else
      {
         cout << "syntax error\n\n";
         cleanup(numbers);
      }
   }
   catch (NumStack::Underflow)
   {
      cout << "syntax error\n\n";
      cleanup(numbers);
   }
}

void endExpressionVar(NumStack &numbers, Table &table, Token &t)
{
   float solution;

   try
   {
      solution = numbers.top();
      numbers.pop();

      if (numbers.empty() && cin >> t &&
          t.isIdentifier())
      {
         string id = t.idValue();
         Variable v(id, solution);

         try
         {
            table.insert(v);
            cout << "\n";
         }
         catch(Table::Duplicate)
         {
            Variable * var = table.find(v);
            var->setValue(solution);
         }
      }
      else
      {
         cout << "syntax error\n\n" << numbers.top();
         cleanup(numbers);
      }
   }
   catch (NumStack::Underflow)
   {
      cout << "syntax error\n\n";
      cleanup(numbers);
   }
}

// deletes all elements in the number stack
void cleanup(NumStack &numbers)
{
   while (!numbers.empty())
   {
      numbers.pop();
   }
}

/*int main()
{
   NumStack numbers;
   Table table;
   Token t;
   bool valid = true;

   cout << "enter postfix expressions, end with ctrl D\n\n";

   while (cin >> t)
   {
      if (t.isNumber() && valid)
      {
         float num = t.numValue();

         try
         {
            numbers.push(num);
         }
         catch(NumStack::Overflow)
         {
            cout << "overflow, ignoring expression";
            cleanup(numbers);
            valid = false;
         }
      }
      else if (t.isIdentifier() && valid)
      {
         string id = t.idValue();
         Variable v(id);
         Variable * var = table.find(v);

         if (var)
         {
            float num = var->getValue();

            try
            {
               numbers.push(num);
            }
            catch(NumStack::Overflow)
            {
               cout << "overflow, ignoring expression";
               cleanup(numbers);
               valid = false;
            }
         }
         else
         {
            cout << "undefined variable ["
                 << id << "]\n\n";
            cleanup(numbers);
            valid = false;
         }
      }
      else if (t.isSymbol())
      {
         char sym = t.symValue();

         if (sym == add && valid)
         {
            float first, second;

            try
            {
               second = numbers.top();
               numbers.pop();
               first = numbers.top();
               numbers.pop();
               numbers.push(first + second);
            }
            catch (NumStack::Underflow)
            {
               cout << "syntax error\n\n";
               cleanup(numbers);
               valid = false;
            }
            catch(NumStack::Overflow)
            {
               cout << "overflow, ignoring expression";
               cleanup(numbers);
               valid = false;
            }
         }
         else if (sym == subtract && valid)
         {
            float first, second;

            try
            {
               second = numbers.top();
               numbers.pop();
               first = numbers.top();
               numbers.pop();
               numbers.push(first - second);
            }
            catch (NumStack::Underflow)
            {
               cout << "syntax error\n\n";
               cleanup(numbers);
               valid = false;
            }
            catch(NumStack::Overflow)
            {
               cout << "overflow, ignoring expression";
               cleanup(numbers);
               valid = false;
            }
         }
         else if (sym == multiply && valid)
         {
            float first, second;

            try
            {
               second = numbers.top();
               numbers.pop();
               first = numbers.top();
               numbers.pop();
               numbers.push(first * second);
            }
            catch (NumStack::Underflow)
            {
               cout << "syntax error\n\n";
               cleanup(numbers);
               valid = false;
            }
            catch(NumStack::Overflow)
            {
               cout << "overflow, ignoring expression";
               cleanup(numbers);
               valid = false;
            }
         }
         else if (sym == divide && valid)
         {
            float num, denom;

            try
            {
               denom = numbers.top();
               numbers.pop();

               if (denom == 0)
               {
                  cout << "cannot divide by zero\n\n";
                  cleanup(numbers);
                  valid = false;
               }
               else
               {
                  num = numbers.top();
                  numbers.pop();
                  numbers.push(num / denom);
               }
            }
            catch (NumStack::Underflow)
            {
               cout << "syntax error\n\n";
               cleanup(numbers);
               valid = false;
            }
            catch(NumStack::Overflow)
            {
               cout << "overflow, ignoring expression";
               cleanup(numbers);
               valid = false;
            }
         }
         else if (sym == exponent && valid)
         {
            float base, power;

            try
            {
               power = numbers.top();
               numbers.pop();
               base = numbers.top();
               numbers.pop();
               numbers.push(pow(base, power));
            }
            catch (NumStack::Underflow)
            {
               cout << "syntax error\n\n";
               cleanup(numbers);
               valid = false;
            }
            catch(NumStack::Overflow)
            {
               cout << "overflow, ignoring expression";
               cleanup(numbers);
               valid = false;
            }
         }
         else if (sym == negation_sign && valid)
         {
            float number;

            try
            {
               number = numbers.top();
               numbers.pop();
               numbers.push(-1 * number);
            }
            catch (NumStack::Underflow)
            {
               cout << "syntax error\n\n";
               cleanup(numbers);
               valid = false;
            }
         }
         else if (sym == end_exp)
         {
            if (valid)
            {
               float solution;

               try
               {
                  solution = numbers.top();
                  numbers.pop();

                  if (numbers.empty())
                  {
                     cout << "result: " << solution << "\n\n";
                  }
                  else
                  {
                     cout << "syntax error\n\n";
                     cleanup(numbers);
                  }
               }
               catch (NumStack::Underflow)
               {
                  cout << "syntax error\n\n";
                  cleanup(numbers);
               }
            }
            valid = true;
         }
         else if (sym == end_exp_var)
         {
            if (valid)
            {
               float solution;

               try
               {
                  solution = numbers.top();
                  numbers.pop();

                  if (numbers.empty() && cin >> t &&
                      t.isIdentifier())
                  {
                     string id = t.idValue();
                     Variable v(id, solution);

                     try
                     {
                        table.insert(v);
                        cout << "\n";
                     }
                     catch(Table::Duplicate)
                     {
                        Variable * var = table.find(v);
                        var->setValue(solution);
                     }
                  }
                  else
                  {
                     cout << "syntax error\n\n" << numbers.top();
                     cleanup(numbers);
                  }
               }
               catch (NumStack::Underflow)
               {
                  cout << "syntax error\n\n";
                  cleanup(numbers);
               }
            }
            else
            {
               cout << "syntax error\n\n";
               cleanup(numbers);
               valid = false;
            }
            valid = true;
         }
      }
   }

   cout << "variables:\n" << table << "\nexit\n";

   return 0;
}*/

