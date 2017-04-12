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
    public:
        // TAG CLASS
        class Tag {
            int id_; // unique id to identify the which class a token belongs to (this is the id of the tag, not the token)
            std::string name_;

        public:

            Tag()
            {}

            Tag(int id, std::string name)
                    : id_(id),
                      name_(name)
            {}

            int id() const{
                return id_;
            }

            std::string name() const {
                return name_;
            }

            inline bool operator==(Tag const& rhs) {
                return id_ == rhs.id_;
            }

            inline const bool operator==(Tag const& rhs) const {
                return id_ == rhs.id_;
            }

            inline bool operator!=(Tag const& rhs) {
                return !(*this == rhs);
            }

            inline const bool operator!=(Tag const& rhs) const {
                return id_ != rhs.id_;
            }

            friend std::ostream& operator<<(std::ostream& os, Tag const& obj) {
                return os << obj.name();
            }

            Tag& operator=(Tag const& rhs) {
                if (this != &rhs)
                {
                    id_ = rhs.id_;
                    name_ = rhs.name_;
                }
                return *this;
            }
        };

    private:
        Tag tag_;
        std::string lexeme_;
        size_t length_;

    public:

        Token()
        {}

        Token(Tag tag, std::string l)
                : tag_(tag),
                  lexeme_(l),
                  length_(l.length())
        {}

        // Returns tag of token
        Tag tag() const {
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

        char first() {
            return lexeme_[0];
        }

        friend std::ostream& operator<<(std::ostream& os, Token const& obj) {
            return os <<  "Token<" << obj.tag() << ", " << obj.lexeme_ << ">";
        }

        Token& operator=(Token const& rhs) {
            if (this != &rhs)
            {
                tag_ = rhs.tag_;
                lexeme_ = rhs.lexeme_;
                length_ = rhs.length_;
            }
            return *this;
        }

    };
}

#endif //TOKEN_H