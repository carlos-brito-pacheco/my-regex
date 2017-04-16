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
/**
 * @file Token.h
 * @brief Header file for the class Token
 * @author Carlos Brito (carlos.brito524@gmail.com)
 * @date: 3/22/17.
 *
 * TODO:
 * Nothing for the moment.
 *
 */
//</editor-fold>


#ifndef TOKEN_H
#define TOKEN_H

#include <string>

namespace Regex {

    /**
     * @brief Token class to represent a Token during lexing of the Regular Expression grammar
     *
     * # Description
     * This is a template class that manipulates "Token" types
     * during parsing. An object of type Token stores the lexeme
     * and has an attribute tag to indicate which "class" the token
     * belongs to. A representation could be this:
     *
     * Token < relop, "<=" >
     */
    class Token {
    public:
        // TAG CLASS
        /**
         * @brief Class to represent the different token classes
         */
        class Tag {
            /// Unique id to identify the which class a token belongs to (this is the id of the tag, not the token)
            int id_;

            /// Name of class (i.e. "RELOP")
            std::string name_;

        public:

            /**
             * @brief Empty constructor
             */
            Tag()
            {}

            /**
             * Constructor to instantiate a tag for a token
             * @param id Id of token class
             * @param name Name of class
             */
            Tag(int id, std::string name)
                    : id_(id),
                      name_(name)
            {}

            Tag(const Tag &tag) {
                id_ = tag.id_;
                name_ = tag.name_;
            }

            /**
             * @brief Returns the id of tag
             * @return Id of tag
             */
            int id() const{
                return id_;
            }

            /**
             * @brief Returns the name of the tag
             * @return Name of tag
             */
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

            /**
             * @brief Overloaded assignment operator
             *
             * @param rhs Right hand side
             * @return Reference to new Tag
             */
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
        /// Tag for token
        Tag tag_;

        /// Lexeme
        std::string lexeme_;

        /// Length of lexem
        size_t length_;

    public:


        /**
         * @brief Empty constructor for Token
         */
        Token()
        {}

        /**
         * Constructor to instatiate a Token with its tag and lexeme
         * @param tag Corresponding tag for the token
         * @param l Lexeme
         */
        Token(Tag tag, std::string l)
                : tag_(tag),
                  lexeme_(l),
                  length_(l.length())
        {}

        /**
         * @brief Returns tag of token
         * @return Token tag
         */
        Tag tag() const {
            return tag_;
        }

        /**
         * @brief Returns associated lexeme of token
         * @return Lexeme
         */
        std::string lexeme() {
            return lexeme_;
        }

        /**
         * @brief Returns length of lexeme
         * @return Length of lexeme
         */
        size_t length() {
            return length_;
        }

        friend std::ostream& operator<<(std::ostream& os, Token const& obj) {
            return os <<  std::string("Token<") << obj.tag() << std::string(", ") << obj.lexeme_ << std::string(">");
        }

        /**
         * @brief Overloaded assignment operator
         * @param rhs Right hand side
         * @return Reference to new token
         */
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