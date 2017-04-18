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
 * @brief Header file for the Parser class of the Regex
 *
 * # Description
 *
 * This file contains the class which parses the regex in order to build the automata and check for syntactic
 * correctness.
 *
 * # TODO
 * Nothing for the moment.
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
     * @brief Class which parses the regex string
     *
     * # Description
     *
     * This class parses the regex specification string in order to check for syntactic correctness and also
     * builds an equivalent automata while it descends down the parse tree.
     *
     * # Grammar
     *
     * The grammar the parser uses is the following:
     *
     *  * # Description
     *
     * Grammar for regex:
     * ````
     *  regex = exp $
     *  exp      = term '|' exp
     *           | term
     *
     *  term     = factor term
     *           | factor
     *
     *  factor   = primary '*'
     *           | primary '+'
     *           | primary '?'
     *           | primary
     *
     *  primary  = '(' exp ')'
     *           | char
     *
     * ````
     * ## Left factored grammar
     *
     * In order to parse efficiently, we left factor the grammar to be able to use the first and follow sets to
     * create a prediction table.
     *
     * ````
     * E = T E'
     *
     * ' = '|' E       { alternation }
     *      | epsilon
     *
     * T = F T'
     *
     * T' = T           { concatenation }
     *      | epsilon
     *
     * F = P F'
     *
     * F' = '*'         { kleene }
     *      | '+'       { positive kleene }
     *      | '?'       { optional }
     *      | epsilon   { nothing }
     *
     * P = '(' E ')'
     *      | char
     *
     * ````
     *
     * # Prediction table
     * The prediction table is not listed here but can easily be calculated using the following online tool:
     * http://hackingoff.com/compilers/ll-1-parser-generator
     *
     * Anyone reading this (ha! i wish) will find that the methods in the cpp file make use of this table.
     *
     * # TODO
     * - Add escape sequence parsing
     * - Add class parsing
     *
     */
    class Parser {

        typedef typename std::vector<Token> token_list;
        typedef typename std::stack <Automata::NFA > automata_stack;

        /// Lexer to get the tokens
        Lexer lexer_;

        /// Lookahead token
        Token lookahead_;

        /// Automata which will be built
        Automata::NFA nfa_;

        /// List of tokens parsed
        token_list tokenList_;

        /// Stack of automatas which aids in applying the operations
        automata_stack automataStack_;

    public:
        /**
         * @brief Constructor for the parser
         */
        Parser();

        /**
         * @brief Destructor for the parser
         */
        ~Parser();

        /**
         * @brief Method to parse the regex. Returns true if succesful, otherwise false.
         * This method parses a regex specification string. If it returns true, then the parse completed succesfully.
         * @param regex Regular expression specification pattern
         * @return True if parse is succesful, false otherwise
         */
        bool parse(std::string regex);

        /**
         * @brief Returns a list of tokens identified by the parser
         * This method returns the list of tokens after they have been identified by the parser. These follow the order
         * of the original string.
         *
         * @return List of tokens
         */
        token_list tokenList();

        /**
         * Gets the associated NFA that accepts the same language as the regex pattern
         * @return Associated NFA
         */
        Automata::NFA getBuiltNFA();

    private:
        /**
         * @brief Consumes a token
         * This method consumes the next token identified by the lexer and sets the lookahead
         */
        void consume();

        /// Grammar rule
        void E();

        /// Grammar rule
        void E_p();

        /// Grammar rule
        void T();

        /// Grammar rule
        void T_p();

        /// Grammar rule
        void F();

        /// Grammar rule
        void F_p();

        /// Grammar rule
        void P();
    };
}




#endif //MYREGEX_PARSER_H
