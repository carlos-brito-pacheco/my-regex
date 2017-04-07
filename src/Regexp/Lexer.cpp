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

#include <iostream>
#include "Lexer.h"
#include "TokenDecls.h"

namespace Regexp {

    Lexer::Lexer(std::string source)
            : source_(source),
              current_position_(0),
              lookahead_(source[0])
    {}

    Token Lexer::nextToken() {

        switch ( source_[current_position_] )
        {

            case ( '(' ): // LEFT PARENTHESES
            std::cout << "yay!" << std::endl;
                return LPAREN;

            case ( ')' ): // RIGHT PARENTHESES
                return RPAREN;

            case ( '*' ): // KLEENE STAR
                return KLEENE_STAR;

            case ( '|' ): // ALTERNATION
                return ALTER;

            case ( '&' ): // CONCATENATION
                return CONCAT;

            case ( '?' ): //
                return QMARK;

            case ( 'e' ):
                return T_EOF;

            default:
                // THROW ERROR
                break;
        }

        current_position_ += 1;

        return NONE;
    }



}