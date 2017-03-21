/*
 * Author: Carlos Brito (carlos.brito524@gmail.com)
 * Date: 3/17/17.
 */

#ifndef MYREGEX_REGEXP_H
#define MYREGEX_REGEXP_H

#include <string>
#include <set>
using namespace std;

class Regexp {
private:
    string regexp_;
    string postfix_;

    string toPostfix();

    ostream& operator<<(ostream& os);

};


#endif //MYREGEX_REGEXP_H
