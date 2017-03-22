/*
 * Author: Carlos Brito (carlos.brito524@gmail.com)
 * Date: 3/17/17.
 */

#include <stack>
#include <queue>
#include <cctype>
#include "Regexp.h"


ostream &Regexp::operator<<(ostream &os) {
    return os << regexp_;
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
    stack<char> operator_stack;

    const string infix_string = regexp_;
    for (string::iterator it = regexp_.begin(); it != regexp_.end(); it++)
    {
        char token;
        if ( isalnum(token) ) // if token is alphanumeric then push to queue
        {
            output_queue.push(token);
        }
        if ( isoperator(token) )
        {

        }

    }

    return std::__cxx11::string();
}

// ---------------------
// returns true if operator, otherwise false
bool Regexp::isoperator(char op) {
    switch (op)
    {
        case '+':
            return true;
        case '*':
            return true;
        case '?':
            return true;
        default:
            return false;


    }
    return false;
}
