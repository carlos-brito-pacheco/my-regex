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
 * @file Parser.h
 * @author Carlos Brito (carlos.brito524@gmail.com)
 * @date 4/13/17.
 * 
 * @brief dasads
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
#include <stack>
#include <queue>
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
        typedef typename std::stack <Automata::NFA > automata_stack;

        Lexer lexer_;
        Token lookahead_;
        Automata::NFA nfa_;
        token_list tokenList_;
        automata_stack automataStack_;

    public:
        Parser();
        ~Parser();

        bool parse(std::string regex);

        token_list tokenList();

        Automata::NFA getBuiltNFA();

    private:
        void consume();
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
