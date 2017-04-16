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
' *
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
 *
 * Left factored grammar:
 * E = T E'
 *
 * E' = '|' E
 *      | epsilon
 *
 * T = F T'         { concatenation }
 *
 * T' = T
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
 * # TODO
 * 
 */
//</editor-fold>
#include <iostream>
#include "Parser.h"
#include "TokenDecls.h"
#include "ParserErrors.h"

using namespace std;

namespace Regex {
    Parser::Parser() {
    }

    Parser::~Parser() {

    }

    bool Parser::parse(std::string regex) {
        lexer_.setSource(regex);
        consume();

        try {
            E();
        } catch (ParserError e)
        {
            return false;
        }

        return true;
    }


    void Parser::consume() {
        do
        {
            lookahead_ = lexer_.nextToken();
        } while (lookahead_.tag() == TAG_SPACE);

        cout << lookahead_ << endl;
    }

    void Parser::E() {
        cout << "E" << endl;
        if (lookahead_.tag() == TAG_LPAREN ||
            lookahead_.tag() == TAG_CHAR)
        {
            T();
            E_p();
        }
        else throw ParserError();

    }

    void Parser::E_p() {
        cout << "E_p" << endl;
        if (lookahead_.tag() == TAG_ALTER)
        {
            // push alt
            consume();
            E();
        }
        else if (lookahead_.tag() == TAG_EOF ||
                lookahead_.tag() == TAG_RPAREN)
        {
            // do nothing
        }
        else throw ParserError();
    }

    void Parser::T() {
        cout << "T" << endl;
        if (lookahead_.tag() == TAG_LPAREN ||
            lookahead_.tag() == TAG_CHAR)
        {
            F();
            T_p();
        }
        else throw ParserError();
    }

    void Parser::T_p() {
        cout << "T_p" << endl;
        if (lookahead_.tag() == TAG_LPAREN ||
            lookahead_.tag() == TAG_CHAR)
        {
            T();
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
        cout << "F" << endl;
        if (lookahead_.tag() == TAG_LPAREN || lookahead_.tag() == TAG_CHAR)
        {
            P();
            F_p();
        }
        else throw ParserError();
    }

    void Parser::F_p() {
        cout << "F_p" << endl;
        if (lookahead_.tag() == TAG_KLEENE_STAR)
        {
            //push kleene
            consume();
        }
        else if (lookahead_.tag() == TAG_QMARK)
        {
            // push q mark
            consume();
        }
//        else if (lookahead_.tag() == TAG_PLUS)
//        {
//            push plus
//        }
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
        cout << "P" << endl;
        if (lookahead_.tag() == TAG_LPAREN)
        {
            // push lparen
            consume();
            E();
            consume();
            // push rparen
        } else if (lookahead_.tag() == TAG_CHAR)
        {
            // push char
            consume();
        }
        else throw ParserError();
    }
}



