/*
 * Author: Carlos Brito (carlos.brito524@gmail.com)
 * Date: 3/21/17.
 */

#ifndef MYREGEX_REGEXPERRORS_H
#define MYREGEX_REGEXPERRORS_H

#include <exception>
#include <string>

using namespace std;

class RegexpMismatchedParentheses : public exception {

    string mismatch_string_;

public:
    RegexpMismatchedParentheses(string s) : mismatch_string_(s){
    }

    ~RegexpMismatchedParentheses() throw() {

    }

    virtual const char* what() const throw()
    {
        return ("Mismatched Parentheses in Regexp: " + mismatch_string_).c_str();
    }
};

#endif //MYREGEX_REGEXPERRORS_H
