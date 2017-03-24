//<editor-fold desc="Preamble">
/*
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *  Copyright (C) 3/23/17 Carlos Brito
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
 * 
 * 
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 */
//</editor-fold>

#ifndef MYREGEX_TOKENTAG_H
#define MYREGEX_TOKENTAG_H

#include <iostream>
#include <string>
using namespace std;

class TokenTag {
    const int id_;
    const string name_;

public:
    TokenTag(int id, string name);

    int id();
    string name();

    bool operator==(TokenTag const& rhs);
    bool operator!=(TokenTag const& rhs);
    friend ostream& operator<<(ostream& os, TokenTag const& obj);
};

TokenTag::TokenTag(int id, string name)
        : id_(id),
          name_(name)
{
}

int TokenTag::id() {
    return id_;
}

string TokenTag::name() {
    return name_;
}

ostream &operator<<(ostream& os, TokenTag const &obj) {
    return os << obj.name_;
}

bool TokenTag::operator==(TokenTag const& rhs) {
    return this->id_ == rhs.id_;
}

bool TokenTag::operator!=(TokenTag const &rhs) {
    return !(*this == rhs);
}

#endif //MYREGEX_TOKENTAG_H
