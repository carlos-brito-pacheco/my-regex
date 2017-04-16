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
#include <vector>
#include "Lexer.h"
#include "TokenDecls.h"
#include "AutomataDecls.h"

namespace Regex {

    Lexer::Lexer() {
        source_ = "";
        addAutomata();
    }

    Lexer::Lexer(std::string source)
            : source_(source)
    {
        addAutomata();
    }

    Token Lexer::nextToken() {

        if (source_.empty()) // if source is empty then return no token
            return Token(TAG_EOF, "");

        // set
        for (typename std::vector<match_pair_type>::iterator it = match_list.begin(); it != match_list.end(); it++)
            it->first.setString(source_);


        if (source_.length() == 1) // if there is only one char then advance and return the tag
        {
            advance();
            std::string lexeme = source_; // the biggest lexeme is the source itself
            source_ = ""; // consume final char
            return Token( match(), lexeme );
        } else
        {
            Token::Tag tag; // tag to inspect
            Token token;
            Token::Tag token_tag = TAG_NONE; // tag of token

            // This do-while cycle iterates until it can't find a matching pattern
            // When it ends, it has memorized the last matching pattern (different from class NONE) in token
            // This means we find the next largest lexeme in the source
            size_t chars_lexed = 0;
            do
            {
                advance(); // advance all automatas
                chars_lexed++;

                tag = match(); // get matching tag

                if (tag != TAG_NONE)
                {
                    std::string lexeme = source_.substr(0, chars_lexed);
                    token = Token(tag, lexeme);
                }

            } while (canAdvance() && chars_lexed < source_.length());

            source_ = source_.erase(0, token.length()); // consume input

            return token;
        }
    }

    Token::Tag Lexer::match() {
        for (typename std::vector<match_pair_type>::iterator it = match_list.begin(); it != match_list.end(); it++)
        {
            if ( it->first.accepts() ) // if the automata is at an accepting state
            {
                return it->second; // return its associated token tag
            }
        }
        return TAG_NONE;
    }

    void Lexer::advance() {
        for (typename std::vector<match_pair_type>::iterator it = match_list.begin(); it != match_list.end(); it++)
            it->first.advance();
    }

    // edit this function to add more automata
    void Lexer::addAutomata() {
        match_list.push_back( std::make_pair( SPACE_NFA, TAG_SPACE ) );
        match_list.push_back( std::make_pair( KLEENE_NFA, TAG_KLEENE_STAR ) );
        match_list.push_back( std::make_pair( ALTERNATION_NFA, TAG_ALTER ) );
        match_list.push_back( std::make_pair( LPAREN_NFA, TAG_LPAREN ) );
        match_list.push_back( std::make_pair( RPAREN_NFA, TAG_RPAREN ) );
        match_list.push_back( std::make_pair( QMARK_NFA, TAG_QMARK ) );
        match_list.push_back( std::make_pair( ASCII_NFA, TAG_CHAR ) );
    }

    void Lexer::setSource(std::string source) {
        source_ = source;
    }

    bool Lexer::canAdvance() {
        for (typename std::vector<match_pair_type>::iterator it = match_list.begin(); it != match_list.end(); it++)
            if (!it->first.getCurrentStates().empty())
                return true;

        return false;
    }

}