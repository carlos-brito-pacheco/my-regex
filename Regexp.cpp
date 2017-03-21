/*
 * Author: Carlos Brito (carlos.brito524@gmail.com)
 * Date: 3/17/17.
 */

#include <stack>
#include <queue>

#include "Regexp.h"


ostream &Regexp::operator<<(ostream &os) {
    return os << regexp_;
}

string Regexp::toPostfix() {
    // Shunting yard algorithm
    
    return std::__cxx11::string();
}
