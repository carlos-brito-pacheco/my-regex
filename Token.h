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
 * Token<TokenTag> token(relop, "<=");
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

using namespace std;

template <class TTokenTag>
class Token {
private:
    const TTokenTag tag_;
    const string lexeme_;

public:
    Token(TTokenTag tag, string l);

    TTokenTag tag();
    string lexeme();

};

template <class TagType>
Token<TagType>::Token(TagType tag, string l)
        : tag_(tag),
          lexeme_(l)
{
}

template <class TagType>
string Token<TagType>::lexeme()
{
    return lexeme_;
}

template <class TagType>
TagType Token<TagType>::tag()
{
    return tag_;
}


#endif //TOKEN_H
