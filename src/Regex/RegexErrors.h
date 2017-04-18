/*
 * Author: Carlos Brito (carlos.brito524@gmail.com)
 * Date: 3/21/17.
 */

#ifndef MYREGEX_REGEXPERRORS_H
#define MYREGEX_REGEXPERRORS_H

#include <exception>
#include <string>
#include "Token.h"

namespace Regex {


    class ParserError : public std::exception {

    public:

        ParserError()
        {}

        ~ParserError() throw() {

        }

        virtual const char* what() const throw()
        {
            return std::string("Regex parser error" ).c_str();
        }
    };

    class InvalidRegexError : public std::exception {
    public:

        InvalidRegexError()
        {}

        ~InvalidRegexError() throw()
        {}

        virtual const char* what() const throw()
        {
            return std::string("Invalid regex detected! Aborting compilation of automata." ).c_str();
        }
    };

    class RegexpMismatchedParentheses : public std::exception {

        std::string mismatch_string_;

    public:
        RegexpMismatchedParentheses(std::string s) : mismatch_string_(s){
        }

        ~RegexpMismatchedParentheses() throw() {

        }

        virtual const char* what() const throw()
        {
            return ("Mismatched Parentheses in Regex: " + mismatch_string_).c_str();
        }
    };
}
#endif //MYREGEX_REGEXPERRORS_H
