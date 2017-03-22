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
 *
 * TODO:
 *
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
*/
//</editor-fold>

#ifndef MYREGEX_REGEXPOPERATOR_H
#define MYREGEX_REGEXPOPERATOR_H

#include <string>
#include <iostream>
using namespace std;

class RegexpOperator {
    const char op_;
    const string name_;
    const int precedence_;

public:
    RegexpOperator(string name, char op, int precedence);

    const int precedence();
    const string name();
    const char c_op();

    bool operator<(RegexpOperator const& rhs);
    bool operator>(RegexpOperator const& rhs);
    bool operator>=(RegexpOperator const& rhs);
    bool operator<=(RegexpOperator const& rhs);

    friend ostream& operator<<(ostream& os, RegexpOperator const& obj);
};

class RegexpInfixOperator : public RegexpOperator {
    const bool left_assoc_; // defines if operator is left associative

public:
    RegexpInfixOperator(string name, char op, bool left_assoc, int precedence);

    const bool isLeftAssociative();
};

class RegexpPostfixOperator : public RegexpOperator {
    const bool assoc_;
public:
    RegexpPostfixOperator(string name, char op, int precedence, bool assoc);

    const bool isAssociative();
};


#endif //MYREGEX_REGEXPOPERATOR_H
