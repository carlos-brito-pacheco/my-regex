/*
 * Author: Carlos Brito (carlos.brito524@gmail.com)
 * Date: 3/21/17.
 */

#include "RegexpOperator.h"

RegexpOperator::RegexpOperator(string name, char op, int precedence)
        : op_(op),
          precedence_(precedence),
          name_(name)
{
}

const int RegexpOperator::precedence() {
    return precedence_;
}

const string RegexpOperator::name() {
    return name_;
}

const char RegexpOperator::c_op() {
    return op_;
}

bool RegexpOperator::operator<(RegexpOperator const& rhs) {
    return this->precedence_ < rhs.precedence_;
}

bool RegexpOperator::operator>(RegexpOperator const &rhs) {
    return this->precedence_ > rhs.precedence_;
}

bool RegexpOperator::operator>=(RegexpOperator const &rhs) {
    return this->precedence_ >= rhs.precedence_;
}

bool RegexpOperator::operator<=(RegexpOperator const &rhs) {
    return this->precedence_ <= rhs.precedence_;
}

ostream& operator<<(ostream& os,  RegexpOperator const& obj) {
    return os << "RegexOperator( "<< obj.name_ << ", " << obj.op_ << " )";
}

RegexpInfixOperator::RegexpInfixOperator(string name, char op, bool left_assoc, int precedence)
        : RegexpOperator(name, op, precedence),
          left_assoc_(left_assoc) {
}

const bool RegexpInfixOperator::isLeftAssociative() {
    return left_assoc_;
}

RegexpPostfixOperator::RegexpPostfixOperator(string name, char op, int precedence, bool assoc)
        : RegexpOperator(name, op, precedence),
          assoc_(assoc) {
}

const bool RegexpPostfixOperator::isAssociative() {
    return assoc_;
}
