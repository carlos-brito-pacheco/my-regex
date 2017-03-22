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
 * Handle tokens as something else than chars
 *
 *
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 */
//</editor-fold>

#include <stack>
#include <queue>
#include <cctype>
#include "Regexp.h"
#include "PearsonHashtable8.h"


// Static variable initialization
static RegexpPostfixOperator REGEXP_KLEENE("Kleene Star", '*', 1, true);
static RegexpInfixOperator REGEXP_CONCAT("Concatenation", '&', true, 2);
static RegexpInfixOperator REGEXP_ALTERN("Alternation", '|', true, 3);

PearsonHashtable8<RegexpOperator> getOperatorTable() {
    PearsonHashtable8<RegexpOperator> table;

    table.add(""+REGEXP_KLEENE.op(), REGEXP_KLEENE);
    table.add(""+REGEXP_CONCAT.op(), REGEXP_CONCAT);
    table.add(""+REGEXP_ALTERN.op(), REGEXP_ALTERN);

    return table;
}

Hashtable<RegexpOperator> *Regexp::operator_table_ = new PearsonHashtable8<RegexpOperator>( getOperatorTable() );



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
            while( isoperator( operator_stack.top() ) )
            {

            }
        }

    }

    return std::__cxx11::string();
}

// ---------------------
// returns true if operator, otherwise false
bool Regexp::isoperator(char op) {
    return operator_table_->containsKey(""+op);
}


