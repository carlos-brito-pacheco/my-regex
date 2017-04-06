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
 * This is a template class that manipulates "Token" types
 * during parsing. An object of type Token stores the lexeme
 * and has an attribute tag to indicate which "class" the token
 * belongs to. A representation could be this:
 *
 * Token token(relop, "<=");
 *
 * TODO:
 *
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 */
//</editor-fold>


#ifndef TOKEN_H
#define TOKEN_H

#include <string>

namespace Regexp {

    class Token {
        // Tag is a class of Token
        class Tag;

    private:
        const Tag tag_;
        const std::string lexeme_;
        const size_t length_;

    public:
        Token(Tag tag, std::string l)
                : tag_(tag),
                  lexeme_(l),
                  length_(l.length())
        {}

        // Returns tag of token
        Tag tag() {
            return tag_;
        }

        // Returns lexeme of token
        std::string lexeme() {
            return lexeme_;
        }

        // Returns length of token
        size_t length() {
            return length_;
        }

    };

    class Token::Tag {
        const int id_; // unique id to identify the which class a token belongs to (this is the id of the tag, not the token)
        const std::string name_;

    public:
        Tag(int id, std::string name)
                : id_(id),
                  name_(name)
        {}

        int id() {
            return id_;
        }

        std::string name() {
            return name_;
        }

        bool operator==(Tag const& rhs) {
            return id_ == rhs.id_;
        }

        bool operator!=(Tag const& rhs) {
            return !(*this == rhs);
        }
    };
}

friend std::ostream& operator<<(std::ostream& os, Regexp::Token::Tag const& obj) {
    return os << obj.name();
}

#endif //TOKEN_H