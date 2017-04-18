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
 * @file Parser.cpp
 * @author Carlos Brito (carlos.brito524@gmail.com)
 * @date 4/13/17.
 *
 * @brief File containing the implementation of the class Parser
 *
 * # TODO
 *
 * - Add the prediction table to the doc
 */
//</editor-fold>
#include <iostream>
#include "Parser.h"
#include "TokenDecls.h"
#include "RegexErrors.h"


namespace Regex {
    Parser::Parser() {
    }

    Parser::~Parser() {

    }

    bool Parser::parse(std::string regex) {
        lexer_.setSource(regex);
        consume();

        E();

        return true;
    }


    void Parser::consume() {
        if (lookahead_.tag() == TAG_EOF)
            throw ParserError();
        do
        {
            lookahead_ = lexer_.nextToken();
        } while (lookahead_.tag() == TAG_SPACE); // ignore whitespace

        tokenList_.push_back(lookahead_);
    }

    void Parser::E() {
        if (lookahead_.tag() == TAG_LPAREN ||
            lookahead_.tag() == TAG_CHAR)
        {
            T();
            E_p();
        }
        else throw ParserError();

    }

    void Parser::E_p() {
        if (lookahead_.tag() == TAG_ALTER)
        {
            consume();
            E();

            // ***** Handle alternation ******** //
            Automata::NFA nfa_1 = automataStack_.top();
            automataStack_.pop();

            Automata::NFA nfa_2 = automataStack_.top();
            automataStack_.pop();

            Automata::NFA alt = nfa_1.alternate(nfa_2);

            automataStack_.push(alt);
            // ********************************* //

        }
        else if (lookahead_.tag() == TAG_EOF ||
                lookahead_.tag() == TAG_RPAREN)
        {
            // do nothing
        }
        else throw ParserError();
    }

    void Parser::T() {
        if (lookahead_.tag() == TAG_LPAREN ||
            lookahead_.tag() == TAG_CHAR)
        {
            F();
            T_p();
        }
        else throw ParserError();
    }

    void Parser::T_p() {
        if (lookahead_.tag() == TAG_LPAREN ||
            lookahead_.tag() == TAG_CHAR)
        {
            T();

            // ***** Handle concatenation ******** //
            Automata::NFA nfa_1 = automataStack_.top();
            automataStack_.pop();

            Automata::NFA nfa_2 = automataStack_.top();
            automataStack_.pop();

            Automata::NFA concat = nfa_2.concatenate(nfa_1);

            automataStack_.push(concat);
            // ********************************* //
        }
        else if(lookahead_.tag() == TAG_ALTER ||
                lookahead_.tag() == TAG_EOF ||
                lookahead_.tag() == TAG_RPAREN)
        {
            // do nothing
        }
        else throw ParserError();
    }

    void Parser::F() {
        if (lookahead_.tag() == TAG_LPAREN || lookahead_.tag() == TAG_CHAR)
        {
            P();
            F_p();
        }
        else throw ParserError();
    }

    void Parser::F_p() {
        if (lookahead_.tag() == TAG_KLEENE_STAR)
        {
            // ***** Handle kleene ******** //
            Automata::NFA nfa = automataStack_.top();
            automataStack_.pop();

            Automata::NFA kleene = nfa.kleene();

            automataStack_.push(kleene);
            // ********************************* //

            consume();
        }
        else if (lookahead_.tag() == TAG_QMARK)
        {
            // ***** Handle optional ******** //
//            std::cout << "HANDLE OPT" << std::endl;
            Automata::NFA nfa = automataStack_.top();
            automataStack_.pop();

            Automata::NFA optional = nfa.optional();

            automataStack_.push(optional);
            // ********************************* //
            consume();
        }
        else if (lookahead_.tag() == TAG_PLUS)
        {
            // ***** Handle kleene plus ******** //
            Automata::NFA nfa = automataStack_.top();
            automataStack_.pop();

            Automata::NFA kleene_plus = nfa.kleene_plus();

            automataStack_.push(kleene_plus);
            // ********************************* //

            consume();
        }
        else if (lookahead_.tag() == TAG_LPAREN ||
                lookahead_.tag() == TAG_CHAR ||
                lookahead_.tag() == TAG_ALTER ||
                lookahead_.tag() == TAG_EOF ||
                lookahead_.tag() == TAG_RPAREN)
        {
            // do nothing
        }
        else throw ParserError();
    }

    void Parser::P() {
        if (lookahead_.tag() == TAG_LPAREN)
        {
            consume(); // consume l paren
            E();
            consume(); // consume r paren
        } else if (lookahead_.tag() == TAG_CHAR)
        {
            // Create NFA and push to stack
            Automata::NFA nfa("0");
            nfa.addState("1", true);

            char symbol = lookahead_.lexeme()[0]; // we access the only element

            nfa.addTransition("0", "1", symbol);

            automataStack_.push(nfa);

            consume();
        }
        else throw ParserError();
    }

    std::vector<Token> Parser::tokenList() {
        return tokenList_;
    }

    Automata::NFA Parser::getBuiltNFA() {
        return automataStack_.top();
    }
}



