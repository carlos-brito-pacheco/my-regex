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
 * This lexer is meant to obtain tokens from a regular expression string.
 * The variable symbol set is a hashtable where all the reserved symbols
 * (like the alternation token "|") are stored.
 *
 * Strictly speaking, we should also keep an "alphabet" but we just take it
 * as everything we can type on a keyboard minus the symbol set.
 *
 * TODO:
 *
 * 
 * 
 * 
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 */
//</editor-fold>

#ifndef MYREGEX_LEXER_H
#define MYREGEX_LEXER_H

#include "../Hashtable/Hashtable.h"
#include "Token.h"

#include <string>

namespace Regexp {

    class Lexer {
        std::string source_;
        size_t current_position_;
        char lookahead_;

    public:
        Lexer(std::string source);

        Token nextToken();
    private:
        Token match();
        char nextChar();

    private:

    };
}


#endif //MYREGEX_LEXER_H
