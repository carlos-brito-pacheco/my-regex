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
 * @file Lexer.h
 * @brief Header file for the Lexer class
 * @author Carlos Brito (carlos.brito524@gmail.com)
 * @date 3/22/17.
 *
 * TODO:
 * Nothing for the moment.
 * 
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 */
//</editor-fold>

#ifndef MYREGEX_LEXER_H
#define MYREGEX_LEXER_H

#include "../Hashtable/Hashtable.h"
#include "Token.h"
#include "../Automata/NFA.h"

#include <string>
#include <vector>
#include <functional>

namespace Regexp {

    /**
     *  # Description
     *
     * This lexer is meant to obtain tokens from a regular expression string.
     * The variable symbol set is a hashtable where all the reserved symbols
     * (like the alternation token "|") are stored.
     *
     * Strictly speaking, we should also keep an "alphabet" but we just take it
     * as everything we can type on a keyboard minus the symbol set.
     */
    class Lexer {

        typedef typename Automata::NFA automata_type;
        typedef typename std::pair<automata_type, Token::Tag> match_pair_type;

        /// String to parse
        std::string source_;

        /// List of automatas with associated tokens
        std::vector<match_pair_type> match_list;


    public:

        /**
         * @brief Default constructor
         *
         * Will initialize the string to parse as an empty string
         */
        Lexer();

        /**
         * @brief Constructor which takes a string as source
         * @param source String to parse
         */
        Lexer(std::string source);

        /**
         * @brief Returns the next token in the source
         *
         * # Description
         *
         * This method will consume the source input and return the next token
         * determined by the given patterns in the addAutomata() method.
         * @return Next token lexed
         */
        Token nextToken();

        /**
         * @brief Sets the string to parse
         * @param source String to parse
         */
        void setSource(std::string source);

    private:

        /**
         * @brief Returns a tag for the matching pattern
         *
         * # Description
         * This method will return a corresponding tag for a lexeme.
         *
         * @return Tag for token
         */
        Token::Tag match();

        /**
         * @brief Method to advance automatas
         *
         * # Description
         * This method basically advances all the automatas.
         * In other words, it makes all the automatas in the list "go forward".
         */
        void advance();

        /**
         * @brief Method which sets all the automata to be used
         *
         * # Description
         * In this method you should add to match_list all the automata that
         * will be used for detecting patterns. You should also notice that you
         * have to add a pair associating an automata with its token tag.
         */
        void addAutomata();
    };
}


#endif //MYREGEX_LEXER_H
