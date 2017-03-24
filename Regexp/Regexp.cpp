//<editor-fold desc="License">
/*
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *  Copyright (C) 3/22/17 Carlos Brito
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.*
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 */
//</editor-fold>

//<editor-fold desc="Description">
/*
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Author: Carlos Brito (carlos.brito524@gmail.com)
 * Date: 3/22/17.
 *
 * Description:
 * This is the implementation of the class Regexp.
 *
 * TODO:
 * - Handle tokens as something else than chars
 *
 * - Instead of using the Shunting-Yard algorithm,
 * we should probably use a parser and determine if
 * the regular expression is syntactically valid and
 * convert to postfix during parsing
 *
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 */
//</editor-fold>

#include <stack>
#include <queue>
#include <cctype>
#include "Regexp.h"
#include "Errors.h"
#include "../Hashtable/PearsonHashtable8.h"


// Static variable initialization
static RegexpOperator REGEXP_KLEENE("Kleene Star", '*', 1);
static RegexpOperator REGEXP_CONCAT("Concatenation", '&', 2);
static RegexpOperator REGEXP_ALTERN("Alternation", '|', 3);
static RegexpOperator REGEXP_LPAREN("Left Parentheses", '(', 0); // parentheses can be regarded as "grouping" operators
static RegexpOperator REGEXP_RPAREN("Right Parentheses", ')', 0); // therefore we don't break cohesion

PearsonHashtable8<RegexpOperator> getOperatorTable() {
    PearsonHashtable8<RegexpOperator> table;

    table.add(""+ REGEXP_KLEENE.c_op(), REGEXP_KLEENE);
    table.add(""+ REGEXP_CONCAT.c_op(), REGEXP_CONCAT);
    table.add(""+ REGEXP_ALTERN.c_op(), REGEXP_ALTERN);
    table.add(""+ REGEXP_LPAREN.c_op(), REGEXP_LPAREN);
    table.add(""+ REGEXP_RPAREN.c_op(), REGEXP_RPAREN);

    return table;
}

Hashtable<RegexpOperator> *Regexp::operator_set_ = new PearsonHashtable8<RegexpOperator>( getOperatorTable() );


// - - - - - - - - - CLASS METHODS - - - - - - - - - //

Regexp::Regexp(string regexp)
        : regexp_(regexp) {

}

ostream& operator<<(ostream &os, Regexp const& obj) {
    return os << obj.regexp_;
}

// -------------------------
// converts the regexp string (infix) representation to postfix
string Regexp::toPostfix() {

    /*
     * Shunting yard algorithm
     * You can consult a nice explanation here:
     * https://en.wikipedia.org/wiki/Shunting-yard_algorithm
     */
    queue<char> output_queue;
    stack<RegexpOperator> operator_stack;

    const string infix_string = regexp_;
    for (string::iterator it = regexp_.begin(); it != regexp_.end(); it++)
    {
        char token = *it;
        if ( isalnum(token) )
            // if token is alphanumeric then push to queue
        {
            output_queue.push(token);
        }
        if ( token != '(' && token != ')' && isoperator(token) )
            // if token is operator then....
        {
            RegexpOperator op1 = operator_set_->get(""+token); // get operator from token
            while ( !operator_stack.empty() && operator_stack.top().c_op() != '(' )
            {
                RegexpOperator op2 = operator_stack.top(); // get operator from stack
                if (op1 <= op2)
                    // if op1 has less precedence than op2 then push to queue and pop from stack
                {
                    output_queue.push( op2.c_op() );
                    operator_stack.pop();
                } else {
                    break;
                }
            }
                operator_stack.push(op1); // at the end push op1 to stack
        }

        if (token == '(')
            // if token is left paren then push to stack
        {
            RegexpOperator lparen = operator_set_->get(""+'(');
            operator_stack.push(lparen);
        }

        if (token == ')')
            // if token is right paren then...
        {
            while(true)
                // Until the token at the top of the stack is a left parenthesis,
                // pop operators off the stack onto the output queue.
            {
                if (operator_stack.top().c_op() != '(')
                {
                    output_queue.push( operator_stack.top().c_op() );
                    operator_stack.pop();

                    if(operator_stack.empty())
                    {
                        throw RegexpMismatchedParentheses(regexp_); // parentheses mismatch
                    }
                } else {
                    operator_stack.pop(); // pop left paren
                    break;
                }
            }
        }
    } // no more tokens to read here

    while ( !operator_stack.empty() )
        // While there are still operator tokens in the stack
    {
        if ( operator_stack.top().c_op() == '(' )
            // If the operator token on the top of the stack is a parenthesis,
            // then there are mismatched parentheses.
        {
            throw RegexpMismatchedParentheses(regexp_);
        } else
            // Pop the operator onto the output queue.
        {
            output_queue.push( operator_stack.top().c_op() );
            operator_stack.pop();
        }
    }

    string postfix_expresion = "";
    while (!output_queue.empty())
    {
        postfix_expresion += output_queue.front();
        output_queue.pop();
    }

    return postfix_expresion;
}

// ---------------------
// returns true if operator, otherwise false
bool Regexp::isoperator(char op) {
    return operator_set_->containsKey(""+op);
}

string Regexp::regexp() {
    return regexp_;
}


