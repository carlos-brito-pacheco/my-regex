//<editor-fold desc="Preamble">
/*
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *  Copyright (C) 4/13/17 Carlos Brito
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
 * @file
 * @author Carlos Brito (carlos.brito524@gmail.com)
 * @date 4/13/17.
 * 
 * @brief
 *
 * # Description
 * 
 * # TODO
 * 
 *
 */
//</editor-fold>
#ifndef MYREGEX_PARSER_H
#define MYREGEX_PARSER_H

#include <string>
#include <vector>
#include "Lexer.h"

namespace Regex {

    /**
     * @class
     * @author Carlos Brito (carlos.brito524@gmail.com)
     * @date 4/13/17.
     *
     * @brief
     *
     * # Description
     *
     * # TODO
     *
     *
     */
    class Parser {

        typedef typename std::vector<Token> token_list;

        Lexer lexer_;
        Token lookahead_;
        Automata::NFA nfa_;

    public:
        Parser();

        ~Parser();

        bool parse(std::string regex);
        void consume();
        void getBuiltNFA();

    private:
        void E();
        void E_p();
        void T();
        void T_p();
        void F();
        void F_p();
        void P();
    };
}




#endif //MYREGEX_PARSER_H
