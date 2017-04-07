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
 * This is the header file of the class Regexp.
 * This contains all the definitions of its functions
 * and provides insight to its behaviour.
 *
 * TODO:
 * - Add support for testing equivalence between regexp
 * (this problem is known to be PSPACE-complete so it isn't trivial to implement)
 *
 * -
 *
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 */
//</editor-fold>

#ifndef MYREGEX_REGEXP_H
#define MYREGEX_REGEXP_H

#include <string>
#include <set>
#include "../Hashtable/Hashtable.h"
#include "RegexpOperator.h"

using namespace std;

class Regexp {
    static Hashtable<string> *operator_set_;
    string regexp_;
    string postfix_;

public:
    Regexp(string regexp);
    string toPostfix();
    string regexp();
private:
    bool isoperator(char op);

    friend ostream& operator<<(ostream& os, Regexp const& regexp);
};


#endif //MYREGEX_REGEXP_H
