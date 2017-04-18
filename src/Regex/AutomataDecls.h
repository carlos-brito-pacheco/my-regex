//<editor-fold desc="Preamble">
/*
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *  Copyright (C) 4/11/17 Carlos Brito
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
 * @file AutomataDecls.h
 * @author Carlos Brito (carlos.brito524@gmail.com)
 * @date 4/11/17.
 * 
 * @brief Header file containing useful automatas
 *
 * # Description
 * This header file was created with the intention of providing useful automatas to
 * lex a regular expression string input in the Lexer class. It contains automatas
 * which parse expressions such as escape sequences and operators.
 * 
 * # TODO
 * Nothing for the moment.
 *
 */
//</editor-fold>
#ifndef MYREGEX_AUTOMATADECLS_H
#define MYREGEX_AUTOMATADECLS_H

#include "../Automata/NFA.h"

/**
 * @brief Get an automata which parses a kleene star operator
 * @return NFA parsing kleene star
 */
Automata::NFA getKleeneStarNFA() {
    Automata::NFA kleene("0");
    kleene.addState("1", true);

    kleene.addTransition("0", "1", '*');

    return kleene;
}

/**
 * @brief Get an automata which parses an alternation
 * @return NFA parsing alternation
 */
Automata::NFA getAlternationNFA() {
    Automata::NFA alt("0");
    alt.addState("1", true);

    alt.addTransition("0", "1", '|');

    return alt;
}

/**
 * @brief Get an automata which parses a question mark
 * @return NFA parsing question mark
 */
Automata::NFA getQMarkNFA() {
    Automata::NFA qmark("0");
    qmark.addState("1", true);

    qmark.addTransition("0", "1", '?');

    return qmark;
}

/**
 * @brief Get an automata which parses a left parentheses
 * @return NFA parsing left parentheses
 */
Automata::NFA getLParenNFA() {
    Automata::NFA lparen("0");
    lparen.addState("1", true);

    lparen.addTransition("0", "1", '(');

    return lparen;
}

/**
 * @brief Get an automata which parses a right parentheses
 * @return NFA parsing right parentheses
 */
Automata::NFA getRParenNFA() {
    Automata::NFA rparen("0");
    rparen.addState("1", true);

    rparen.addTransition("0", "1", ')');

    return rparen;
}

/**
 * @brief Get an automata which parses a right parentheses
 * @return NFA parsing right parentheses
 */
Automata::NFA getKleenePlusNFA() {
    Automata::NFA kleene_plus("0");
    kleene_plus.addState("1", true);

    kleene_plus.addTransition("0", "1", '+');

    return kleene_plus;
}

/**
 * @brief Get an automata which parses an alphanumeric character
 * @return NFA parsing an alphanumeric character
 */
Automata::NFA getAlphaCharNFA() {
    Automata::NFA char_nfa("0");
    char_nfa.addState("1", true);

    for(char c = 'a'; c != 'z' + 1; c++)
        char_nfa.addTransition("0", "1", c);

    return char_nfa;
}

/**
 * @brief Get an automata which parses an ascii character
 *
 * The range is inclusive on both sides
 * @param from Starting ascii character
 * @param to Ending ascii character
 * @return NFA parsing an ascii character
 */
Automata::NFA getAsciiNFA(char from, char to) {
    Automata::NFA ascii_nfa("0");
    ascii_nfa.addState("1", true);

    for(char c = from; c != to + 1; c++)
        ascii_nfa.addTransition("0", "1", c);

    return ascii_nfa;
}

/**
 * @brief Get an automata which parses whitespace
 * @return  NFA parsing a whitespace
 */
Automata::NFA getWhiteSpaceNFA() {
    Automata::NFA white_space_nfa("0");
    white_space_nfa.addState("1", true);

    white_space_nfa.addTransition("0", "1", ' ');

    return white_space_nfa;
}

/// Accepts Kleene Stars
const Automata::NFA KLEENE_NFA = getKleeneStarNFA();

/// Accepts Alternation operator
const Automata::NFA ALTERNATION_NFA = getAlternationNFA();

/// Accepts Question Mark operator
const Automata::NFA QMARK_NFA = getQMarkNFA();

/// Accepts Left Parentheses
const Automata::NFA LPAREN_NFA = getLParenNFA();

/// Accepts Right Parentheses
const Automata::NFA RPAREN_NFA = getRParenNFA();

/// Accepts alphanumeric characters
const Automata::NFA ALPHA_CHAR_NFA = getAlphaCharNFA();

/// Accepts ascii characters in the range 33 ('!') to 126 ('~') inclusive
const Automata::NFA ASCII_NFA = getAsciiNFA(33, 126);

/// Accepts whitespace
const Automata::NFA SPACE_NFA = getWhiteSpaceNFA();

const Automata::NFA KLEENE_PLUS_NFA = getKleenePlusNFA();



#endif //MYREGEX_AUTOMATADECLS_H
